# BlueprintBaseOnly

- **Function Description:** Used for class attributes to specify whether only base classes that can generate Blueprint subclasses are accepted
- **Usage Location:** UPROPERTY
- **Engine Module:** TypePicker
- **Metadata Type:** bool
- **Restricted Types:** TSubClassOf, FSoftClassPath, UClass*
- **Commonality:** ★★

This attribute is particularly useful when you want to restrict the class to those that can serve as Blueprint base classes.

## Test Code:

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyCommonObject :public UObject
{
	GENERATED_BODY()
};

UCLASS(BlueprintType)
class INSIDER_API UMyCommonObjectChild :public UMyCommonObject
{
	GENERATED_BODY()
};

UCLASS(BlueprintType, NotBlueprintable)
class INSIDER_API UMyCommonObjectChild_NotBlueprintable :public UMyCommonObject
{
	GENERATED_BODY()
public:
};

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlueprintBaseOnlyTest")
	TSubclassOf<UMyCommonObject> MyClass_NotBlueprintBaseOnly;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlueprintBaseOnlyTest", meta = (BlueprintBaseOnly))
	TSubclassOf<UMyCommonObject> MyClass_BlueprintBaseOnly;
```

## Testing Code:

With the BlueprintBaseOnly restriction added, the class UMyCommonObjectChild_NotBlueprintable cannot be selected due to its NotBlueprintable attribute.

![BlueprintBaseOnly](BlueprintBaseOnly.jpg)

## 测试效果:

If bBlueprintBaseOnly is true, further checks are required to determine if CanCreateBlueprintOfClass is valid, which assesses whether a class can be used to create Blueprint subclasses.

Typically, if a C++ class does not have the Blueprintable attribute defined, it cannot generate Blueprint subclasses and will not be selected by this property.

Classes that are already Blueprints can always be used to create additional Blueprint subclasses.

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