# KismetHideOverrides

Description: 不允许被覆盖的蓝图事件的列表。
Usage: UCLASS
Feature: Blueprint
Group: Blueprint
Type: strings="a，b，c"
Example: KismetHideOverrides="Event1, Event2, ..”
Status: NotWorked

在源码中发现ALevelScriptActor上面定义了很多，用来阻止被覆盖。

样例：

```cpp
UCLASS(notplaceable, meta=(ChildCanTick, KismetHideOverrides = "ReceiveAnyDamage,ReceivePointDamage,ReceiveRadialDamage,ReceiveActorBeginOverlap,ReceiveActorEndOverlap,ReceiveHit,ReceiveDestroyed,ReceiveActorBeginCursorOver,ReceiveActorEndCursorOver,ReceiveActorOnClicked,ReceiveActorOnReleased,ReceiveActorOnInputTouchBegin,ReceiveActorOnInputTouchEnd,ReceiveActorOnInputTouchEnter,ReceiveActorOnInputTouchLeave"), HideCategories=(Collision,Rendering,Transformation), MinimalAPI)
class ALevelScriptActor : public AActor
{}
```

但是实际在LevelScriptActor的子类中依然可以覆盖该事件。有一些被隐藏的Event是其实通过HideCategories来做到的。因此该Meta其实并没有实现，如果要达到该效果，还是要通过HideFunctions或HideCategories来达成。

![Untitled](KismetHideOverrides/Untitled.png)

原理：

可以看到这里面的判断，并没有用到该Meta

```cpp
void SMyBlueprint::CollectAllActions(FGraphActionListBuilderBase& OutAllActions)
{
// Cache potentially overridable functions
UClass* ParentClass = BlueprintObj->SkeletonGeneratedClass ? BlueprintObj->SkeletonGeneratedClass->GetSuperClass() : *BlueprintObj->ParentClass;
for ( TFieldIterator<UFunction> FunctionIt(ParentClass, EFieldIteratorFlags::IncludeSuper); FunctionIt; ++FunctionIt )
{
	const UFunction* Function = *FunctionIt;
	const FName FunctionName = Function->GetFName();

	UClass *OuterClass = CastChecked<UClass>(Function->GetOuter());
	// ignore skeleton classes and convert them into their "authoritative" types so they
	// can be found in the graph
	if(UBlueprintGeneratedClass *GeneratedOuterClass = Cast<UBlueprintGeneratedClass>(OuterClass))
	{
		OuterClass = GeneratedOuterClass->GetAuthoritativeClass();
	}

	if (    UEdGraphSchema_K2::CanKismetOverrideFunction(Function) 
		 && !OverridableFunctionNames.Contains(FunctionName) 
		 && !ImplementedFunctionCache.Contains(FunctionName) 
		 && !FObjectEditorUtils::IsFunctionHiddenFromClass(Function, ParentClass)
		 && !FBlueprintEditorUtils::FindOverrideForFunction(BlueprintObj, OuterClass, Function->GetFName())
		 && Blueprint->AllowFunctionOverride(Function)
	   )
	{
		FText FunctionTooltip = FText::FromString(UK2Node_CallFunction::GetDefaultTooltipForFunction(Function));
		FText FunctionDesc = K2Schema->GetFriendlySignatureName(Function);
		if ( FunctionDesc.IsEmpty() )
		{
			FunctionDesc = FText::FromString(Function->GetName());
		}

		if (Function->HasMetaData(FBlueprintMetadata::MD_DeprecatedFunction))
		{
			FunctionDesc = FBlueprintEditorUtils::GetDeprecatedMemberMenuItemName(FunctionDesc);
		}

		FText FunctionCategory = FObjectEditorUtils::GetCategoryText(Function);

		TSharedPtr<FEdGraphSchemaAction_K2Graph> NewFuncAction = MakeShareable(new FEdGraphSchemaAction_K2Graph(EEdGraphSchemaAction_K2Graph::Function, FunctionCategory, FunctionDesc, FunctionTooltip, 1, NodeSectionID::FUNCTION_OVERRIDABLE));
		NewFuncAction->FuncName = FunctionName;

		OverridableFunctionActions.Add(NewFuncAction);
		OverridableFunctionNames.Add(FunctionName);
	}
}
}
```