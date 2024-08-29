// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProperty_BindWidget.h"
#include "Blueprint/WidgetTree.h"

UMyProperty_BindWidget::UMyProperty_BindWidget(const FObjectInitializer& initializer)
	:UUserWidget(initializer)
{

}

void UMyProperty_BindWidget::RunTest()
{
	UWidget* bindWidget= WidgetTree->FindWidget(TEXT("MyTextBlock_Bind"));
	check(bindWidget==(UWidget*)MyTextBlock_Bind);
}
