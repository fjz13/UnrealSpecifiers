# AllowAnyActor

Description: 用在ComponentReference属性上，在UseComponentPicker的情况下使得组件选取器扩大到场景里其他Actor下的其他组件。
Usage: UPROPERTY
Feature: Editor
Group: Component Property
Type: bool
LimitedType: FComponentReference，FSoftComponentReference
Status: Done
Parent item: UseComponentPicker (UseComponentPicker.md)

用在ComponentReference属性上，在UseComponentPicker的情况下使得组件选取器扩大到场景里其他Actor下的其他组件。

- 也要注意到，这个AllowAnyActor影响的只是UI上的组件选择。一个ComponentReference即使不加AllowAnyActor，也可以通过ReferencedActor引用到别的Actor，然后手填其属下的组件名字。然后可以正常的在C++里GetComponent里出来正确的组件对象。因此AllowAnyActor跟逻辑无关。

测试代码和效果见UseComponentPicker。

原理：

主要是FComponentReferenceCustomization。根据源码查看，bAllowAnyActor 只在已经有bUseComponentPicker的情况下生效，且用来对Actor列表进行过滤。

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