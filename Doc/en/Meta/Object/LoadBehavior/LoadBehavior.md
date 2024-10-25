# LoadBehavior

- **Function Description:** Used on UCLASS to denote the loading behavior of this class, enabling the corresponding TObjectPtr attribute to support lazy loading. The default loading behavior is Eager, which can be changed to LazyOnDemand.
- **Usage Location:** UCLASS
- **Engine Module:** Object Property
- **Metadata Type:** string="abc"
- **Restriction Type:** TObjectPtr
- **Commonality:** ★

Applied to UCLASS to mark the class's loading behavior, allowing the associated TObjectPtr property to support delayed loading. The optional loading behavior defaults to Eager and can be set to LazyOnDemand.

- The default Eager behavior is similar to the common resource hard reference logic, meaning if A has a hard reference to B, B will be loaded recursively when A is loaded.
- The LazyOnDemand behavior means the resource will only be loaded when it is actually required (when Get is triggered). This is also a hard reference but is loaded lazily. Similarly, if A has a hard reference to B, B will not be loaded immediately when A is loaded; instead, the reference information (B's ObjectPath) is recorded first. When A needs to access B, B can be loaded at that time because the location of B has already been recorded in advance. If the loading is fast enough, it will be transparent to the user. LazyOnDemand is only effective in the editor, which allows for quicker editor startup without waiting for all resources to be loaded, as not all resources need to be loaded and parsed immediately for access.
- The difference from FSoftObjectPtr is that it represents a soft reference that requires manual judgment for loading时机. LazyOnDemand, on the other hand, is an automatic delayed loading mechanism that is transparent to the user, requiring no additional actions.
- LoadBehavior only affects TObjectPtr properties; UObject* properties are always loaded directly. This is because only TObjectPtr has implemented the reference path information encoding for UObject*, which allows for delayed loading.
- LoadBehavior is also only supported in the editor environment. At runtime, TObjectPtr is downgraded to UObject*, resulting in direct loading of all instances.
- LoadBehavior is typically marked on asset type classes. Classes marked in the source code include DataAsset, DataTable, CurveTable, SoundCue, SoundWave, DialogueWave, and AnimMontage. Therefore, if you define a custom asset class that contains a lot of data, you can use LazyOnDemand to optimize the loading speed in the editor.
- To test LoadBehavior, enable the engine's LazyLoadImports feature, which is disabled by default. This can be done by adding the setting LazyLoadImports=True under the Core.System.Experimental section in DefaultEngine.ini. For source code reference, see the IsImportLazyLoadEnabled method.
- When testing, be cautious if you open a DataAsset asset by double-clicking, as the property details panel needs to display the property values, which triggers GetObjectPropertyValue_InContainer and leads to ObjectHandleResolve, causing the resolution of TObjectPtr.

## Test Code:

Here, two DataAsset types, UMyDataAsset_Eager and UMyDataAsset_LazyOnDemand, are specifically defined for comparison with different LoadBehavior settings.

```cpp
//(BlueprintType = true, IncludePath = Property/MyProperty_Asset.h, IsBlueprintBase = true, LoadBehavior = Eager, ModuleRelativePath = Property/MyProperty_Asset.h)
UCLASS(Blueprintable, Blueprintable, meta = (LoadBehavior = "Eager"))
class INSIDER_API UMyDataAsset_Eager :public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Score;
};

//(BlueprintType = true, IncludePath = Property/MyProperty_Asset.h, IsBlueprintBase = true, LoadBehavior = LazyOnDemand, ModuleRelativePath = Property/MyProperty_Asset.h)
UCLASS(Blueprintable, Blueprintable, meta = (LoadBehavior = "LazyOnDemand"))
class INSIDER_API UMyDataAsset_LazyOnDemand :public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Score;
};

UCLASS(BlueprintType)
class INSIDER_API UMyClass_LoadBehaviorTest :public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UMyDataAsset_LazyOnDemand> MyLazyOnDemand_AssetPtr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UMyDataAsset_Eager> MyEager_AssetPtr;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere,meta = (LoadBehavior = "Eager"))
	TObjectPtr<UMyDataAsset_LazyOnDemand> MyLazyOnDemand_AssetPtr_EagerOnProperty;

	UPROPERTY(BlueprintReadWrite, EditAnywhere,meta = (LoadBehavior = "LazyOnDemand"))
	TObjectPtr<UMyDataAsset_Eager> MyEager_AssetPtr_LazyOnDemandOnProperty;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UMyDataAsset_LazyOnDemand* MyLazyOnDemand_Asset;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UMyDataAsset_Eager* MyEager_Asset;

public:
	UFUNCTION(BlueprintCallable)
	static void LoadBehaviorTest();
};

void UMyClass_LoadBehaviorTest::LoadBehaviorTest()
{
	UPackage* pk = LoadPackage(nullptr, TEXT("/Game/Class/Behavior/LoadBehavior/DA_LoadBehaviorTest"), 0);
	UMyClass_LoadBehaviorTest* obj = LoadObject<UMyClass_LoadBehaviorTest>(pk, TEXT("DA_LoadBehaviorTest"));
}

//Enable feature
DefaultEngine.ini
[Core.System.Experimental]
LazyLoadImports=True
```

## Test Results:

After the editor is running, manually call LoadBehaviorTest to load the DataAsset of UMyClass_LoadBehaviorTest. Check the object values for different property types. You will find:

- Among them, the ObjectPtr values for MyLazyOnDemand_AssetPtr and MyLazyOnDemand_AssetPtr_EagerOnProperty are not yet resolved, while others show the values of the direct objects.
- The conclusion is that only marking LazyOnDemand on UCLASS will make delayed loading effective. Marking LoadBehavior on properties does not take effect. Properties of type UObject* are always loaded directly.

![Untitled](Untitled.png)

## Principle:

In LinkerLoadImportBehavior.cpp, the FindLoadBehavior method is used to determine LoadBehavior, indicating that it only acts on UCLASS.

Also, in the TObjectPtr Get function, the call to ResolveObjectHandle is found, which is where resolution is triggered.

Note that the UE_WITH_OBJECT_HANDLE_LATE_RESOLVE definition is WITH_EDITORONLY_DATA, meaning it is effective only in the editor environment.

```cpp
//D:\github\UnrealEngine\Engine\Source\Runtime\CoreUObject\Private\UObject\LinkerLoadImportBehavior.cpp
enum class EImportBehavior : uint8
{
	Eager = 0,
	// @TODO: OBJPTR: we want to permit lazy background loading in the future
	//LazyBackground,
	LazyOnDemand,
};

EImportBehavior FindLoadBehavior(const UClass& Class)
{
	//Package class can't have meta data because of UHT
	if (&Class == UPackage::StaticClass())
	{
		return EImportBehavior::LazyOnDemand;
	}

	static const FName Name_LoadBehavior(TEXT("LoadBehavior"));
	if (const FString* LoadBehaviorMeta = Class.FindMetaData(Name_LoadBehavior))
	{
		if (*LoadBehaviorMeta == TEXT("LazyOnDemand"))
		{
			return EImportBehavior::LazyOnDemand;
		}
		return EImportBehavior::Eager;
	}
	else
	{
		//look in super class to see if it has lazy load on
		const UClass* Super = Class.GetSuperClass();
		if (Super != nullptr)
		{
			return FindLoadBehavior(*Super);
		}
		return EImportBehavior::Eager;
	}
}

	#define UE_WITH_OBJECT_HANDLE_LATE_RESOLVE WITH_EDITORONLY_DATA

	inline UObject* ResolveObjectHandle(FObjectHandle& Handle)
	{
#if UE_WITH_OBJECT_HANDLE_LATE_RESOLVE || UE_WITH_OBJECT_HANDLE_TRACKING
		UObject* ResolvedObject = ResolveObjectHandleNoRead(Handle);
		UE::CoreUObject::Private::OnHandleRead(ResolvedObject);
		return ResolvedObject;
#else
		return ReadObjectHandlePointerNoCheck(Handle);
#endif
	}
```