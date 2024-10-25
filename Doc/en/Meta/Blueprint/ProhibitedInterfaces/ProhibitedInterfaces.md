# ProhibitedInterfaces

- **Function Description:** Lists interfaces incompatible with blueprint classes, thereby preventing their implementation
- **Usage Location:** UCLASS
- **Engine Module:** Blueprint
- **Metadata Type:** strings = "a, b, c"
- **Commonality:** ★★

## Test Code:

```cpp
UINTERFACE(Blueprintable,MinimalAPI)
class UMyInterface_First:public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class INSIDER_API IMyInterface_First
{
	GENERATED_IINTERFACE_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void FirstFunc() const;
};

UINTERFACE(Blueprintable,MinimalAPI)
class UMyInterface_Second:public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class INSIDER_API IMyInterface_Second
{
	GENERATED_IINTERFACE_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SecondFunc() const;
};

UCLASS(Blueprintable,meta=(ProhibitedInterfaces="UMyInterface_Second"))
class INSIDER_API UMyClass_ProhibitedInterfaces :public UObject
{
	GENERATED_BODY()
public:
};
```

## Test Results:

Discovered that UMyInterface_Second is prevented from being implemented, while UMyInterface_First remains implementable

![Untitled](Untitled.png)

## Principle Code:

As seen in the construction of the list, filtering is applied. Additionally, the use of .RightChop(1) is noted; hence, the interface name provided must include the 'U' prefix. If UMyInterface_Second

```cpp
TSharedRef<SWidget> FBlueprintEditorUtils::ConstructBlueprintInterfaceClassPicker( const TArray< UBlueprint* >& Blueprints, const FOnClassPicked& OnPicked)
{
	//...

		UClass const* const ParentClass = Blueprint->ParentClass;
		// see if the parent class has any prohibited interfaces
		if ((ParentClass != nullptr) && ParentClass->HasMetaData(FBlueprintMetadata::MD_ProhibitedInterfaces))
		{
			FString const& ProhibitedList = Blueprint->ParentClass->GetMetaData(FBlueprintMetadata::MD_ProhibitedInterfaces);

			TArray<FString> ProhibitedInterfaceNames;
			ProhibitedList.ParseIntoArray(ProhibitedInterfaceNames, TEXT(","), true);

			// loop over all the prohibited interfaces
			for (int32 ExclusionIndex = 0; ExclusionIndex < ProhibitedInterfaceNames.Num(); ++ExclusionIndex)
			{
				ProhibitedInterfaceNames[ExclusionIndex].TrimStartInline();
				FString const& ProhibitedInterfaceName = ProhibitedInterfaceNames[ExclusionIndex].RightChop(1);
				UClass* ProhibitedInterface = UClass::TryFindTypeSlow<UClass>(ProhibitedInterfaceName);
				if(ProhibitedInterface)
				{
					Filter->DisallowedClasses.Add(ProhibitedInterface);
					Filter->DisallowedChildrenOfClasses.Add(ProhibitedInterface);
				}
			}
		}

		// Do not allow adding interfaces that are already added to the Blueprint
		TArray<UClass*> InterfaceClasses;
		FindImplementedInterfaces(Blueprint, true, InterfaceClasses);
		for(UClass* InterfaceClass : InterfaceClasses)
		{
			Filter->DisallowedClasses.Add(InterfaceClass);
		}

		// Include a class viewer filter for imported namespaces if the class picker is being hosted in an editor context
		TSharedPtr<IToolkit> AssetEditor = FToolkitManager::Get().FindEditorForAsset(Blueprint);
		if (AssetEditor.IsValid() && AssetEditor->IsBlueprintEditor())
		{
			TSharedPtr<IBlueprintEditor> BlueprintEditor = StaticCastSharedPtr<IBlueprintEditor>(AssetEditor);
			TSharedPtr<IClassViewerFilter> ImportedClassViewerFilter = BlueprintEditor->GetImportedClassViewerFilter();
			if (ImportedClassViewerFilter.IsValid())
			{
				Options.ClassFilters.AddUnique(ImportedClassViewerFilter.ToSharedRef());
			}
		}
	}

	// never allow parenting to children of itself
	for (UClass*  BPClass : BlueprintClasses)
	{
		Filter->DisallowedChildrenOfClasses.Add(BPClass);
	}

	return FModuleManager::LoadModuleChecked<FClassViewerModule>("ClassViewer").CreateClassViewer(Options, OnPicked);
}
```