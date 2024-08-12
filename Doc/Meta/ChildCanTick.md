# ChildCanTick

Description: 用于Actor或ActorComponent子类，标记允许其蓝图子类可以接受响应Tick事件
Usage: UCLASS
Feature: Behavior
Group: Actor
Type: bool
LimitedType: Actor类
Status: Done
Sub-item: ChildCannotTick (ChildCannotTick.md)

要在蓝图中重载Tick事件函数并才会在编译的时候触发判断。

```cpp
//(BlueprintType = true, ChildCannotTick = , IncludePath = Class/Blueprint/MyActor_ChildTick.h, IsBlueprintBase = true, ModuleRelativePath = Class/Blueprint/MyActor_ChildTick.h)
UCLASS(Blueprintable,meta=(ChildCanTick))
class INSIDER_API AMyActor_ChildCanTick : public AActor
{
	GENERATED_BODY()
public:
	AMyActor_ChildCanTick()
	{
		PrimaryActorTick.bCanEverTick = false;
	}
};

//(BlueprintType = true, ChildCanTick = , IncludePath = Class/Blueprint/MyActor_ChildTick.h, IsBlueprintBase = true, ModuleRelativePath = Class/Blueprint/MyActor_ChildTick.h)
UCLASS(Blueprintable,meta=(ChildCanTick))
class INSIDER_API UMyActorComponent_ChildCanTick : public UActorComponent
{
	GENERATED_BODY()
public:
};

//(BlueprintType = true, ChildCannotTick = , IncludePath = Class/Blueprint/MyActor_ChildTick.h, IsBlueprintBase = true, ModuleRelativePath = Class/Blueprint/MyActor_ChildTick.h)
UCLASS(Blueprintable,meta=(ChildCannotTick))
class INSIDER_API AMyActor_ChildCannotTick : public AActor
{
	GENERATED_BODY()
public:
};

//(BlueprintType = true, ChildCannotTick = , IncludePath = Class/Blueprint/MyActor_ChildTick.h, IsBlueprintBase = true, ModuleRelativePath = Class/Blueprint/MyActor_ChildTick.h)
UCLASS(Blueprintable,meta=(ChildCannotTick))
class INSIDER_API UMyActorComponent_ChildCannotTick : public UActorComponent
{
	GENERATED_BODY()
public:
};
```

蓝图Actor或ActorComponent里测试：

也注意到这个判断跟蓝图中是否开启Tick并没有关系。

![Untitled](ChildCanTick/Untitled.png)

![Untitled](ChildCanTick/Untitled%201.png)

而AMyActor_ChildCanTick类里虽然已经手动关闭了PrimaryActorTick.bCanEverTick，但是在子类里依然可以正常的Tick（在编译的时候内部可以正常的再重新开启bCanEverTick）。

![Untitled](ChildCanTick/Untitled%202.png)

源码里判断的逻辑：

开启bCanEverTick=true的条件有3，一是EngineSettings->bCanBlueprintsTickByDefault，二是父类是AActor或UActorComponent本身，三是C++基类上有ChildCanTick的标记。

```cpp
void FKismetCompilerContext::SetCanEverTick() const
{
// RECEIVE TICK
if (!TickFunction->bCanEverTick)
{
	// Make sure that both AActor and UActorComponent have the same name for their tick method
	static FName ReceiveTickName(GET_FUNCTION_NAME_CHECKED(AActor, ReceiveTick));
	static FName ComponentReceiveTickName(GET_FUNCTION_NAME_CHECKED(UActorComponent, ReceiveTick));

	if (const UFunction* ReceiveTickEvent = FKismetCompilerUtilities::FindOverriddenImplementableEvent(ReceiveTickName, NewClass))
	{
		// We have a tick node, but are we allowed to?

		const UEngine* EngineSettings = GetDefault<UEngine>();
		const bool bAllowTickingByDefault = EngineSettings->bCanBlueprintsTickByDefault;

		const UClass* FirstNativeClass = FBlueprintEditorUtils::FindFirstNativeClass(NewClass);
		const bool bHasCanTickMetadata = (FirstNativeClass != nullptr) && FirstNativeClass->HasMetaData(FBlueprintMetadata::MD_ChildCanTick);
		const bool bHasCannotTickMetadata = (FirstNativeClass != nullptr) && FirstNativeClass->HasMetaData(FBlueprintMetadata::MD_ChildCannotTick);
		const bool bHasUniversalParent = (FirstNativeClass != nullptr) && ((AActor::StaticClass() == FirstNativeClass) || (UActorComponent::StaticClass() == FirstNativeClass));

		if (bHasCanTickMetadata && bHasCannotTickMetadata)
		{
			// User error: The C++ class has conflicting metadata
			const FString ConlictingMetadataWarning = FText::Format(
				LOCTEXT("HasBothCanAndCannotMetadataFmt", "Native class %s has both '{0}' and '{1}' metadata specified, they are mutually exclusive and '{1}' will win."),
				FText::FromString(FirstNativeClass->GetPathName()),
				FText::FromName(FBlueprintMetadata::MD_ChildCanTick),
				FText::FromName(FBlueprintMetadata::MD_ChildCannotTick)
			).ToString();
			MessageLog.Warning(*ConlictingMetadataWarning);
		}

		if (bHasCannotTickMetadata)
		{
			// This could only happen if someone adds bad metadata to AActor or UActorComponent directly
			check(!bHasUniversalParent);

			// Parent class has forbidden us to tick
			const FString NativeClassSaidNo = FText::Format(
				LOCTEXT("NativeClassProhibitsTickingFmt", "@@ is not allowed as the C++ parent class {0} has disallowed Blueprint subclasses from ticking.  Please consider using a Timer instead of Tick."),
				FText::FromString(FirstNativeClass->GetPathName())
			).ToString();
			MessageLog.Warning(*NativeClassSaidNo, FindLocalEntryPoint(ReceiveTickEvent));
		}
		else
		{
			if (bAllowTickingByDefault || bHasUniversalParent || bHasCanTickMetadata)
			{
				// We're allowed to tick for one reason or another
				TickFunction->bCanEverTick = true;
			}
			else
			{
				// Nothing allowing us to tick
				const FString ReceiveTickEventWarning = FText::Format(
					LOCTEXT("ReceiveTick_CanNeverTickFmt", "@@ is not allowed for Blueprints based on the C++ parent class {0}, so it will never Tick!"),
					FText::FromString(FirstNativeClass ? *FirstNativeClass->GetPathName() : TEXT("<null>"))
				).ToString();
				MessageLog.Warning(*ReceiveTickEventWarning, FindLocalEntryPoint(ReceiveTickEvent));

				const FString ReceiveTickEventRemedies = FText::Format(
					LOCTEXT("ReceiveTick_CanNeverTickRemediesFmt", "You can solve this in several ways:\n  1) Consider using a Timer instead of Tick.\n  2) Add meta=({0}) to the parent C++ class\n  3) Reparent the Blueprint to AActor or UActorComponent, which can always tick."),
					FText::FromName(FBlueprintMetadata::MD_ChildCanTick)
				).ToString();
				MessageLog.Warning(*ReceiveTickEventRemedies);
			}
		}
	}
}
}
```