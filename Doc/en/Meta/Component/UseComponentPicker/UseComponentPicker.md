# UseComponentPicker

- **Function description:**  When used on the ComponentReference attribute, it displays the components under the Actor in the selector list for selection.
- **Use location:** UPROPERTY
- **Engine module:** Component Property
- **Metadata type:** bool
- **Limit type:** FComponentReference, FSoftComponentReference
- **Related items:** [AllowAnyActor](../AllowAnyActor.md)
- **Frequency of use:** ★★

When used on the ComponentReference property, it displays the components under the Actor in the selector list for easy selection.

- By default, the selector list expanded by the Referenced Actor property of FComponentReference allows you to select Actors in the scene, but it does not display all the components under those Actors. The ComponentName attribute under ComponentReference requires manual input from the player. This method is relatively basic and prone to errors.
- Adding UseComponentPicker will display a list of components for selection. However, by default, it is limited to all components under the current Actor, excluding components from other Actors in the scene.
- To further list all components under all Actors in the scene, you need to additionally add AllowAnyActor to expand the filtering scope.
- There are two property types for ComponentReference: FComponentReference and FSoftComponentReference, both of which correspond to FComponentReferenceCustomization. The test code omits FSoftComponentReference for brevity.

## Test Code:

```cpp
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "UseComponentPickerTest")
	FComponentReference MyComponentReference_NoUseComponentPicker;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "UseComponentPickerTest", meta = (UseComponentPicker))
	FComponentReference MyComponentReference_UseComponentPicker;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "UseComponentPicker_AllowAnyActor_Test", meta = (UseComponentPicker,AllowAnyActor))
	FComponentReference MyComponentReference_UseComponentPicker_AllowAnyActor;
```

## Test Results:

- The default setting lists all Actors, but ComponentName needs to be manually entered.
- After adding UseComponentPicker, the second setting lists all components under the current Actor, but components from other Actors cannot be selected.
- The third setting, with AllowAnyActor added, lists all components of all Actors.

![UseComponentPicker](UseComponentPicker.jpg)

## Principle:

Both FComponentReference and FSoftComponentReference correspond to FComponentReferenceCustomization. Examining the source code reveals that using bUseComponentPicker creates ClassFilters and ComboBox, employing different type filters and UIs for component selection. Otherwise, the else branch uses a very basic structural attribute expansion and editing approach.

```cpp
void FComponentReferenceCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
	PropertyHandle = InPropertyHandle;

	CachedComponent.Reset();
	CachedFirstOuterActor.Reset();
	CachedPropertyAccess = FPropertyAccess::Fail;

	bAllowClear = false;
	bAllowAnyActor = false;
	bUseComponentPicker = PropertyHandle->HasMetaData(NAME_UseComponentPicker);
	bIsSoftReference = false;

	if (bUseComponentPicker)
	{
		FProperty* Property = InPropertyHandle->GetProperty();
		check(CastField<FStructProperty>(Property) &&
				(FComponentReference::StaticStruct() == CastFieldChecked<const FStructProperty>(Property)->Struct ||
				FSoftComponentReference::StaticStruct() == CastFieldChecked<const FStructProperty>(Property)->Struct));

		bAllowClear = !(InPropertyHandle->GetMetaDataProperty()->PropertyFlags & CPF_NoClear);
		bAllowAnyActor = InPropertyHandle->HasMetaData(NAME_AllowAnyActor);
		bIsSoftReference = FSoftComponentReference::StaticStruct() == CastFieldChecked<const FStructProperty>(Property)->Struct;

		BuildClassFilters();
		BuildComboBox();

		InPropertyHandle->SetOnPropertyValueChanged(FSimpleDelegate::CreateSP(this, &FComponentReferenceCustomization::OnPropertyValueChanged));

		// set cached values
		{
			CachedComponent.Reset();
			CachedFirstOuterActor = GetFirstOuterActor();

			FComponentReference TmpComponentReference;
			CachedPropertyAccess = GetValue(TmpComponentReference);
			if (CachedPropertyAccess == FPropertyAccess::Success)
			{
				CachedComponent = TmpComponentReference.GetComponent(CachedFirstOuterActor.Get());
				if (!IsComponentReferenceValid(TmpComponentReference))
				{
					CachedComponent.Reset();
				}
			}
		}

		HeaderRow.NameContent()
		[
			InPropertyHandle->CreatePropertyNameWidget()
		]
		.ValueContent()
		[
			ComponentComboButton.ToSharedRef()
		]
		.IsEnabled(MakeAttributeSP(this, &FComponentReferenceCustomization::CanEdit));
	}
	else
	{
		HeaderRow.NameContent()
		[
			InPropertyHandle->CreatePropertyNameWidget()
		]
		.ValueContent()
		[
			InPropertyHandle->CreatePropertyValueWidget()
		]
		.IsEnabled(MakeAttributeSP(this, &FComponentReferenceCustomization::CanEdit));
	}
}
```