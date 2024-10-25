# GetAllowedClasses

- **Function description:** Used in class or object selectors to specify, through a function, that the selected objects must belong to certain base class types.
- **Usage location:** UPROPERTY
- **Engine module:** TypePicker
- **Metadata type:** string = "abc"
- **Restricted types:** TSubClassOf, UClass*, UObject*, FSoftObjectPath
Code: TArray<UClass*> FuncName() const;
- **Associated items:** [AllowedClasses](../AllowedClasses/AllowedClasses.md)
- **Commonly used:** ★★

AllowedClass specifies the base class by directly referencing the class name as a string. GetAllowedClasses takes it a step further by allowing a function to return the filtered base classes, offering greater flexibility for dynamic and custom selections.

Of course, GetAllowedClasses does not support as many attribute types as AllowedClass, limited to: TSubClassOf, UClass*, UObject*, FSoftObjectPath

## Test Code:

```cpp
public:
	UFUNCTION()
	TArray<UClass*> MyGetAllowedClassesFunc()
	{
			TArray<UClass*> classes;
			classes.Add(UMyCommonObject::StaticClass());
			classes.Add(UTexture2D::StaticClass());
			classes.Add(UMyPrimaryDataAsset::StaticClass());

			return classes;
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GetAllowedClassesTest|TSubclassOf")
	TSubclassOf<UObject> MyClass_NoGetAllowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GetAllowedClassesTest|TSubclassOf", meta = (GetAllowedClasses = "MyGetAllowedClassesFunc"))
	TSubclassOf<UObject> MyClass_GetAllowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GetAllowedClassesTest|UClass*")
	UClass* MyClassPtr_NoGetAllowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GetAllowedClassesTest|UClass*", meta = (GetAllowedClasses = "MyGetAllowedClassesFunc"))
	UClass* MyClassPtr_GetAllowedClasses;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GetAllowedClassesTest|FSoftObjectPath")
	UObject* MyObject_NoGetAllowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GetAllowedClassesTest|FSoftObjectPath", meta = (GetAllowedClasses = "MyGetAllowedClassesFunc"))
	UObject* MyObject_GetAllowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GetAllowedClassesTest|FSoftObjectPath")
	FSoftObjectPath MySoftObject_NoGetAllowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GetAllowedClassesTest|FSoftObjectPath", meta = (GetAllowedClasses = "MyGetAllowedClassesFunc"))
	FSoftObjectPath MySoftObject_GetAllowedClasses;
```

## Test Results:

It is evident that the Class selector restricts the selection to the three specified base classes, and similarly, the Object selector limits the objects to these same three base classes.

![GetAllowClasses](GetAllowClasses.jpg)

## Principle:

Investigating the source code reveals that only SPropertyEditorClass and SPropertyEditorAsset properties can be applied, which correspond to the Class type (not FSoftClassPath) and the UObject's Asset type (FSoftObjectPath corresponds to SPropertyEditorAsset), respectively

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