# ConversionRoot

- **Function Description:** Allows Actors within the scene editor to transform between themselves and their subclasses
- **Engine Module:** Scene
- **Metadata Type:** bool
- **Action Mechanism:** Adds [IsConversionRoot](../../../../Meta/Blueprint/IsConversionRoot.md) to the Meta data
- **Usage Frequency:** ★

Generally used on Actors to restrict the level of transformation during an Actor's conversion, such as ASkeletalMeshActor, AStaticMeshActor, etc.

Often appears together with ComponentWrapperClass.

According to the code, the IsConversionRoot in the meta data will restrict the propagation to this level only, without searching further up the hierarchy.

Only Actors with a ConversionRoot set are allowed to perform the Convert Actor action; otherwise, it is disabled.

## Sample Code:

```cpp
//(BlueprintType = true, IncludePath = Class/Trait/MyClass_ConversionRoot.h, IsBlueprintBase = true, IsConversionRoot = true, ModuleRelativePath = Class/Trait/MyClass_ConversionRoot.h)
UCLASS(Blueprintable,BlueprintType, ConversionRoot)
class INSIDER_API AMyActor_ConversionRoot :public AActor
{
	GENERATED_BODY()
};

```

## Example Effect:

Create subclasses BP_ConversionRoot_Child1 and BP_ConversionRoot_Child2 in the Blueprint. Then, drag and drop BP_ConversionRoot_Child1 into the scene to create an Actor, and also create a standard Blueprint Actor for comparison.

![Untitled](Untitled.png)

Selecting Child1 in the level will enable the ConvertActor function, allowing transformations between itself and all subclasses of the ConversionRoot.

![Untitled](Untitled%201.png)

If it is a standard Actor, no transformation can occur because ConversionRoot is not defined.

![Untitled](Untitled%202.png)

## Fundamental Principle:

In the level, when an Actor is selected, the DetailsPanel will display the ConverActor property bar, where another Actor can be selected for transformation.
TSharedRef<SWidget> FActorDetails::MakeConvertMenu( const FSelectedActorInfo& SelectedActorInfo )
This function is used to create the menu for the Select Type Combo Button. Internally, it calls CreateClassPickerConvertActorFilter:

```cpp
UClass* FActorDetails::GetConversionRoot( UClass* InCurrentClass ) const
{
	UClass* ParentClass = InCurrentClass;

	while(ParentClass)
	{
		if( ParentClass->GetBoolMetaData(FName(TEXT("IsConversionRoot"))) )
		{
			break;
		}
		ParentClass = ParentClass->GetSuperClass();
	}

	return ParentClass;
}

void FActorDetails::CreateClassPickerConvertActorFilter(const TWeakObjectPtr<AActor> ConvertActor, class FClassViewerInitializationOptions* ClassPickerOptions)
Filter->AllowedChildOfRelationship.Add(RootConversionClass);//Limits the selection to subclasses below this base class

```