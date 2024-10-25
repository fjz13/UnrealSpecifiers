#ExactClass

- **Function Description:** When both AllowedClasses and GetAllowedClasses are set, ExactClass specifies that only the intersection of types that are exactly the same in both collections will be selected; otherwise, the intersection plus its subclasses will be selected.
- **Usage Location:** UPROPERTY
- **Engine Module:** TypePicker
- **Metadata Type:** bool
- **Restricted Types:** FSoftObjectPath, UObject*
- **Associated Items:** [AllowedClasses](../AllowedClasses/AllowedClasses.md)
- **Commonality:** ★

When both AllowedClasses and GetAllowedClasses are set, ExactClass specifies that only the intersection of types that are exactly the same in both collections will be selected; otherwise, the intersection plus its subclasses will be selected.

- Only applies to FSoftObjectPath and UObject*, as currently only SPropertyEditorAsset utilizes this Meta.
- The distinction between the two is not easily understood, because if the consistent type happens to be the base class of other types, it does not matter whether its subclasses are included.
- In the test code, an example is constructed where Texture2D and TextureCube are selected from AllowedClasses, and TextureLightProfile and TextureCube are selected from GetAllowedClasses. We know that TextureLightProfile inherits from Texture2D. Therefore, if ExactClass is true, the final filtered type is TextureCube, as the types must be completely identical. If ExactClass is false, the final filtered types are TextureCube and TextureLightProfile, because TextureLightProfile is a subclass of Texture2D, and thus will be selected.

## Test Code:

```cpp
	UFUNCTION()
	TArray<UClass*> MyGetAllowedClassesFunc()
	{
		TArray<UClass*> classes;
		classes.Add(UTextureLightProfile::StaticClass());
		classes.Add(UTextureCube::StaticClass());
		return classes;
	}


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ExactClassTest|UObject*", meta = (AllowedClasses = "/Script/Engine.Texture2D,/Script/Engine.TextureCube",GetAllowedClasses = "MyGetAllowedClassesFunc"))
	UObject* MyObject_NoExactClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ExactClassTest|UObject*", meta = (ExactClass, AllowedClasses = "/Script/Engine.Texture2D,/Script/Engine.TextureCube",GetAllowedClasses = "MyGetAllowedClassesFunc"))
	UObject* MyObject_ExactClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ExactClassTest|FSoftObjectPath", meta = (AllowedClasses = "/Script/Engine.Texture2D,/Script/Engine.TextureCube",GetAllowedClasses = "MyGetAllowedClassesFunc"))
	FSoftObjectPath MySoftObject_NoExactClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ExactClassTest|FSoftObjectPath", meta = (ExactClass, AllowedClasses = "/Script/Engine.Texture2D,/Script/Engine.TextureCube",GetAllowedClasses = "MyGetAllowedClassesFunc"))
	FSoftObjectPath MySoftObject_ExactClass;
```

## Test Results:

- It can be observed that without ExactClass, the filtered types are TextureCube and TextureLightProfile, with a total of 18 items.
- With ExactClass, the filtered type is only TextureCube, with a total of 12 items.

![ExactClass](ExactClass.jpg)

## Principle:

After testing and reviewing the source code logic, it has been confirmed that ExactClass must be used in conjunction with GetAllowedClasses, and both must be present in AllowedClasses. The "ExactClass" attribute is passed to GetAllowedAndDisallowedClasses. This is the only place in the entire source code where it is used. Following the logic within GetAllowedAndDisallowedClasses, when both AllowedClasses and GetAllowedClasses have values, the bExactClass condition is evaluated.

- If bExactClass is false, the values in AllowedClasses and GetAllowedClasses must be equal or one must be a subclass of the other, meaning they must belong to the same inheritance hierarchy, and the final selection will include subclasses rather than base classes.
- If bExactClass is true, only types that are exactly the same in both AllowedClasses and GetAllowedClasses will be selected.

```cpp
void SPropertyEditorClass::Construct(const FArguments& InArgs, const TSharedPtr< FPropertyEditor >& InPropertyEditor)
{
	//The default value is false, hence ExactClass is not utilized
	PropertyEditorUtils::GetAllowedAndDisallowedClasses(ObjectList, *Property, AllowedClassFilters, DisallowedClassFilters, false);
}
void SPropertyEditorAsset::InitializeClassFilters(const FProperty* Property)
{
	if (Property == nullptr)
	{
		AllowedClassFilters.Add(ObjectClass);
		return;
	}

	// Account for the allowed classes specified in the property metadata
	const FProperty* MetadataProperty = GetActualMetadataProperty(Property);

	bExactClass = GetTagOrBoolMetadata(MetadataProperty, "ExactClass", false);

	TArray<UObject*> ObjectList;
	if (PropertyEditor && PropertyEditor->GetPropertyHandle()->IsValidHandle())
	{
		PropertyEditor->GetPropertyHandle()->GetOuterObjects(ObjectList);
	}
	else if (PropertyHandle.IsValid())
	{
		PropertyHandle->GetOuterObjects(ObjectList);
	}

	PropertyEditorUtils::GetAllowedAndDisallowedClasses(ObjectList, *MetadataProperty, AllowedClassFilters, DisallowedClassFilters, bExactClass, ObjectClass);

	if (AllowedClassFilters.Num() == 0)
	{
		// always add the object class to the filters
		AllowedClassFilters.Add(ObjectClass);
	}
}

void GetAllowedAndDisallowedClasses(const TArray<UObject*>& ObjectList, const FProperty& MetadataProperty, TArray<const UClass*>& AllowedClasses, TArray<const UClass*>& DisallowedClasses, bool bExactClass, const UClass* ObjectClass)
{
		TArray<const UClass*> CurrentAllowedClassFilters = MoveTemp(AllowedClasses);
			ensure(AllowedClasses.IsEmpty());
			for (const UClass* MergedClass : MergedClasses)
			{
				// Keep classes that match both allow list
				for (const UClass* CurrentClass : CurrentAllowedClassFilters)
				{
					if (CurrentClass == MergedClass || (!bExactClass && CurrentClass->IsChildOf(MergedClass)))
					{
						AllowedClasses.Add(CurrentClass);
						break;
					}
					if (!bExactClass && MergedClass->IsChildOf(CurrentClass))
					{
						AllowedClasses.Add(MergedClass);
						break;
					}
				}

}

```