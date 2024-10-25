# AllowAnyActor

- **Function Description:** Used on the ComponentReference attribute, this allows the component selector to include components from other Actors within the scene when UseComponentPicker is enabled.
- **Usage Location:** UPROPERTY
- **Engine Module:** Component Property
- **Metadata Type:** bool
- **Restricted Types:** FComponentReference, FSoftComponentReference
- **Associated Items:** [UseComponentPicker](UseComponentPicker/UseComponentPicker.md)
- **Commonality:** ★★

Applied to the ComponentReference attribute, this enables the component selector to include components from other Actors within the scene when UseComponentPicker is in use.

- Note that AllowAnyActor only affects the component selection in the UI. A ComponentReference can still reference another Actor via ReferencedActor, even without AllowAnyActor, and manually input the name of its child components. This allows the correct component object to be retrieved using GetComponent in C++. Thus, AllowAnyActor is unrelated to the logic.

For test code and results, refer to UseComponentPicker.

## Principle:

Primarily involves FComponentReferenceCustomization. As indicated by the source code, bAllowAnyActor is only active when bUseComponentPicker is already enabled and is used to filter the list of Actors.

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

bool FComponentReferenceCustomization::IsFilteredActor(const AActor* const Actor) const
{
	return bAllowAnyActor || Actor == CachedFirstOuterActor.Get();
}

```