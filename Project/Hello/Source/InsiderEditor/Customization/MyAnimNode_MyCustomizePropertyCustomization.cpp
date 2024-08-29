// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAnimNode_MyCustomizePropertyCustomization.h"
#include "DetailWidgetRow.h"
#include "IDetailChildrenBuilder.h"
#include "DetailLayoutBuilder.h"
#include "Widgets/Input/STextComboBox.h"

TSharedRef<IDetailCustomization> FMyAnimNode_MyCustomizePropertyCustomization::MakeInstance()
{
	return MakeShareable(new FMyAnimNode_MyCustomizePropertyCustomization());
}

void FMyAnimNode_MyCustomizePropertyCustomization::CustomizeDetails(class IDetailLayoutBuilder& DetailBuilder)
{
	TSharedPtr<IPropertyHandle> PropertyHandle = DetailBuilder.GetProperty(TEXT("Node.MyString_CustomizeProperty"));

	//hide original property
	//DetailBuilder.HideProperty(PropertyHandle);

	//Just for test
	ComboListItems.Empty();
	ComboListItems.Add(MakeShareable(new FString(TEXT("First"))));
	ComboListItems.Add(MakeShareable(new FString(TEXT("Second"))));
	ComboListItems.Add(MakeShareable(new FString(TEXT("Third"))));
	const TSharedPtr<FString> ComboBoxSelectedItem = ComboListItems[0];

	IDetailCategoryBuilder& Group = DetailBuilder.EditCategory(TEXT("CustomProperty"));
	Group.AddCustomRow(INVTEXT("CustomProperty"))
		.NameContent()
		[
			PropertyHandle->CreatePropertyNameWidget()
		]
		.ValueContent()
		[
			SNew(STextComboBox)
				.OptionsSource(&ComboListItems)
				.InitiallySelectedItem(ComboBoxSelectedItem)
				.ContentPadding(2.f)
				.ToolTipText(FText::FromString(*ComboBoxSelectedItem))
		];
}
