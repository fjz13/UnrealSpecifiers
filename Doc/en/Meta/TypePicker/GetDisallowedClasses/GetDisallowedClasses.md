# GetDisallowedClasses

- **Function Description:** Used on class selectors to specify, via a function, certain base class types to be excluded from the list of selected types.
- **Usage Location:** UPROPERTY
- **Engine Module:** TypePicker
- **Metadata Type:** string="abc"
- **Restricted Types:** TSubClassOf, UClass*
Code: TArray<UClass*> FuncName() const;
- **Associated Items:** [AllowedClasses](../AllowedClasses/AllowedClasses.md)
- **Commonliness:** ★★

Its functionality is similar to GetAllowedClasses, but with the opposite effect.

However, its attribute type is similar to DisallowedClasses, and it can only be applied to class selectors. As such, after testing, it is found to only work with TSubClassOf and UClass*.

## Test Code:

```cpp
UFUNCTION()
TArray<UClass*> MyGetDisallowedClassesFunc()
{
	TArray<UClass*> classes;
	classes.Add(UAbilityAsync::StaticClass());
	classes.Add(UTexture2D::StaticClass());
	return classes;
}


UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GetDisallowedClassesTest|TSubclassOf")
TSubclassOf<UObject> MyClass_NoGetDisallowedClasses;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GetDisallowedClassesTest|TSubclassOf", meta = (GetDisallowedClasses = "MyGetDisallowedClassesFunc"))
TSubclassOf<UObject> MyClass_GetDisallowedClasses;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GetDisallowedClassesTest|UClass*")
UClass* MyClassPtr_NoGetDisallowedClasses;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GetDisallowedClassesTest|UClass*", meta = (GetDisallowedClasses = "MyGetDisallowedClassesFunc"))
UClass* MyClassPtr_GetDisallowedClasses;
```

## Test Effects:

You can observe that after adding GetDisallowedClasses, some types are missing from the selection list.

![GetDisallowedClasses](GetDisallowedClasses.jpg)

## Principle:

While both SPropertyEditorClass and SPropertyEditorAsset utilize GetAllowedAndDisallowedClasses, allowing the use of GetDisallowedClasses, SPropertyEditorAsset subsequently employs SAssetPicker, which does not make use of DisallowedClasses. Therefore, SPropertyEditorAsset does not support GetDisallowedClasses, and as a result, attributes of type UObject* do not support GetDisallowedClasses.

```cpp
void SPropertyEditorAsset::InitializeClassFilters(const FProperty* Property)
{
		PropertyEditorUtils::GetAllowedAndDisallowedClasses(ObjectList, *MetadataProperty, AllowedClassFilters, DisallowedClassFilters, bExactClass, ObjectClass);
}

void SPropertyEditorClass::Construct(const FArguments& InArgs, const TSharedPtr< FPropertyEditor >& InPropertyEditor)
{
		PropertyEditorUtils::GetAllowedAndDisallowedClasses(ObjectList, *Property, AllowedClassFilters, DisallowedClassFilters, false);
}

TSharedRef<SWidget> SPropertyEditorEditInline::GenerateClassPicker()
{
		PropertyEditorUtils::GetAllowedAndDisallowedClasses(ObjectList, *Property, AllowedClassFilters, DisallowedClassFilters, false);
}

void PropertyEditorUtils::GetAllowedAndDisallowedClasses(const TArray<UObject*>& ObjectList, const FProperty& MetadataProperty, TArray<const UClass*>& AllowedClasses, TArray<const UClass*>& DisallowedClasses, bool bExactClass, const UClass* ObjectClass)
{
	AllowedClasses = PropertyCustomizationHelpers::GetClassesFromMetadataString(MetadataProperty.GetOwnerProperty()->GetMetaData("AllowedClasses"));
	DisallowedClasses = PropertyCustomizationHelpers::GetClassesFromMetadataString(MetadataProperty.GetOwnerProperty()->GetMetaData("DisallowedClasses"));

	bool bMergeAllowedClasses = !AllowedClasses.IsEmpty();

	if (MetadataProperty.GetOwnerProperty()->HasMetaData("GetAllowedClasses"))
	{
		const FString GetAllowedClassesFunctionName = MetadataProperty.GetOwnerProperty()->GetMetaData("GetAllowedClasses");
	}

	if (MetadataProperty.GetOwnerProperty()->HasMetaData("GetDisallowedClasses"))
	{
		const FString GetDisallowedClassesFunctionName = MetadataProperty.GetOwnerProperty()->GetMetaData("GetDisallowedClasses");
		if (!GetDisallowedClassesFunctionName.IsEmpty())
		{
			for (UObject* Object : ObjectList)
			{
				const UFunction* GetDisallowedClassesFunction = Object ? Object->FindFunction(*GetDisallowedClassesFunctionName) : nullptr;
				if (GetDisallowedClassesFunction)
				{
					DECLARE_DELEGATE_RetVal(TArray<UClass*>, FGetDisallowedClasses);
					DisallowedClasses.Append(FGetDisallowedClasses::CreateUFunction(Object, GetDisallowedClassesFunction->GetFName()).Execute());
				}
			}
		}
	}
}
```