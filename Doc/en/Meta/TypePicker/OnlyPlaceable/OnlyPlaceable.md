# OnlyPlaceable

- **Function Description:** Used on class properties to indicate whether only Actors that can be placed within a scene are accepted
- **Usage Location:** UPROPERTY
- **Engine Module:** TypePicker
- **Metadata Type:** bool
- **Restricted Types:** TSubClassOf, FSoftClassPath, UClass*
- **Commonality:** ★★

Ability to exclude certain Actor classes, such as AInfo, which cannot be placed in a scene.

## Test Code:

```cpp

UCLASS(Blueprintable,BlueprintType)
class INSIDER_API AMyActor :public AActor
{
	GENERATED_BODY()
};

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyActorChild_Placeable :public AMyActor
{
	GENERATED_BODY()
};

UCLASS(Blueprintable, BlueprintType,NotPlaceable)
class INSIDER_API AMyActorChild_NotPlaceable :public AMyActor
{
	GENERATED_BODY()
};

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OnlyPlaceableTest")
	TSubclassOf<AMyActor> MyActor_NotOnlyPlaceable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OnlyPlaceableTest", meta = (OnlyPlaceable))
	TSubclassOf<AMyActor> MyActor_OnlyPlaceable;
```

## Test Effects:

Visible AMyActorChild_NotPlaceable class cannot be selected by the MyActor_OnlyPlaceable property due to the NotPlaceable tag.

![OnlyPlaceable](OnlyPlaceable.jpg)

## Principle:

```cpp
bool FPropertyHandleBase::GeneratePossibleValues(TArray<FString>& OutOptionStrings, TArray< FText >& OutToolTips, TArray<bool>& OutRestrictedItems, TArray<FText>* OutDisplayNames)
{
	 if( Property->IsA(FClassProperty::StaticClass()) || Property->IsA(FSoftClassProperty::StaticClass()) )
	{
		UClass* MetaClass = Property->IsA(FClassProperty::StaticClass())
			? CastFieldChecked<FClassProperty>(Property)->MetaClass
			: CastFieldChecked<FSoftClassProperty>(Property)->MetaClass;

		FString NoneStr( TEXT("None") );
		OutOptionStrings.Add( NoneStr );
		if (OutDisplayNames)
		{
			OutDisplayNames->Add(FText::FromString(NoneStr));
		}

		const bool bAllowAbstract = Property->GetOwnerProperty()->HasMetaData(TEXT("AllowAbstract"));
		const bool bBlueprintBaseOnly = Property->GetOwnerProperty()->HasMetaData(TEXT("BlueprintBaseOnly"));
		const bool bAllowOnlyPlaceable = Property->GetOwnerProperty()->HasMetaData(TEXT("OnlyPlaceable"));
		UClass* InterfaceThatMustBeImplemented = Property->GetOwnerProperty()->GetClassMetaData(TEXT("MustImplement"));

		if (!bAllowOnlyPlaceable || MetaClass->IsChildOf<AActor>())
		{
			for (TObjectIterator<UClass> It; It; ++It)
			{
				if (It->IsChildOf(MetaClass)
					&& PropertyEditorHelpers::IsEditInlineClassAllowed(*It, bAllowAbstract)
					&& (!bBlueprintBaseOnly || FKismetEditorUtilities::CanCreateBlueprintOfClass(*It))
					&& (!InterfaceThatMustBeImplemented || It->ImplementsInterface(InterfaceThatMustBeImplemented))
					&& (!bAllowOnlyPlaceable || !It->HasAnyClassFlags(CLASS_Abstract | CLASS_NotPlaceable)))
				{
					OutOptionStrings.Add(It->GetName());
					if (OutDisplayNames)
					{
						OutDisplayNames->Add(FText::FromString(It->GetName()));
					}
				}
			}
		}
	}
}
```