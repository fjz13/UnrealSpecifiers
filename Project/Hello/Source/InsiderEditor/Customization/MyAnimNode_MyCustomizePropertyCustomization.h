// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

class FMyAnimNode_MyCustomizePropertyCustomization : public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();
	virtual void CustomizeDetails(class IDetailLayoutBuilder& DetailBuilder) override;
protected:
	TArray< TSharedPtr< FString > > ComboListItems;
};

