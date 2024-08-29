// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCommonObjectCustomization.h"
#include "Common/CommonTypes.h"
#include "DetailWidgetRow.h"
#include "IDetailChildrenBuilder.h"
#include "DetailLayoutBuilder.h"

TSharedRef<IPropertyTypeCustomization> FMyCommonObjectCustomization::MakeInstance()
{
	return MakeShareable(new FMyCommonObjectCustomization());
}

void FMyCommonObjectCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
	HeaderRow.NameContent()[SNew(STextBlock).Text(INVTEXT("This is MyCommonObject"))];
	//for ForceInlineRow
	HeaderRow.ValueContent()[SNew(STextBlock).Text(INVTEXT("This is MyCommonObject"))];

}

void FMyCommonObjectCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
	TSharedPtr<IPropertyHandle> IntPropertyHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(UMyCommonObject, MyInt));
	TSharedPtr<IPropertyHandle> StringPropertyHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(UMyCommonObject, MyString));

	if (!IntPropertyHandle.IsValid() || !StringPropertyHandle.IsValid())
	{
		return;
	}

	ChildBuilder.AddCustomRow(FText())
		[
			SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.Padding(5.0f, 0.0f).AutoWidth()
				[
					IntPropertyHandle->CreatePropertyNameWidget()
				]
				+ SHorizontalBox::Slot()
				.Padding(5.0f, 0.0f).AutoWidth()
				[
					IntPropertyHandle->CreatePropertyValueWidget()
				]
				+ SHorizontalBox::Slot()
				.Padding(5.0f, 0.0f).AutoWidth()
				[
					StringPropertyHandle->CreatePropertyNameWidget()
				]
				+ SHorizontalBox::Slot()
				.Padding(5.0f, 0.0f).AutoWidth()
				[
					StringPropertyHandle->CreatePropertyValueWidget()
				]
		];
}

TSharedRef<IDetailCustomization> FMyCommonObjectDetailsCustomization::MakeInstance()
{
	return MakeShareable(new FMyCommonObjectDetailsCustomization());
}

void FMyCommonObjectDetailsCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	//TSharedRef<IPropertyHandle> RootPropertyHandle = DetailBuilder.GetProperty(UMyCommonObject::StaticClass()->GetFName(), UMyCommonObject::StaticClass());
	TSharedRef<IPropertyHandle> IntPropertyHandle = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UMyCommonObject, MyInt), UMyCommonObject::StaticClass());
	TSharedRef<IPropertyHandle> StringPropertyHandle = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UMyCommonObject, MyString), UMyCommonObject::StaticClass());

	DetailBuilder.HideProperty(UMyCommonObject::StaticClass()->GetFName(), UMyCommonObject::StaticClass());

	DetailBuilder.HideCategory("MyCommonObject");

	IDetailCategoryBuilder& SectionCategory = DetailBuilder.EditCategory("Common");
	SectionCategory.AddCustomRow(FText())
		.NameContent()
		[
			SNew(STextBlock).Text(INVTEXT("This is MyCommonObject"))
		]
		.ValueContent()
		[
			SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.Padding(5.0f, 0.0f).AutoWidth()
				[
					IntPropertyHandle->CreatePropertyNameWidget()
				]
				+ SHorizontalBox::Slot()
				.Padding(5.0f, 0.0f).AutoWidth()
				[
					IntPropertyHandle->CreatePropertyValueWidget()
				]
				+ SHorizontalBox::Slot()
				.Padding(5.0f, 0.0f).AutoWidth()
				[
					StringPropertyHandle->CreatePropertyNameWidget()
				]
				+ SHorizontalBox::Slot()
				.Padding(5.0f, 0.0f).AutoWidth()
				[
					StringPropertyHandle->CreatePropertyValueWidget()
				]
		];
}
