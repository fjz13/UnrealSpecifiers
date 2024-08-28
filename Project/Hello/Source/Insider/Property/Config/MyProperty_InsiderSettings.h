// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"

#include "MyProperty_InsiderSettings.generated.h"

UCLASS(config = InsiderSettings, defaultconfig)
class UMyProperty_InsiderSettings :public UDeveloperSettings
{
	GENERATED_BODY()
public:
	/** Gets the settings container name for the settings, either Project or Editor */
	virtual FName GetContainerName() const override { return TEXT("Project"); }
	/** Gets the category for the settings, some high level grouping like, Editor, Engine, Game...etc. */
	virtual FName GetCategoryName() const override { return TEXT("Insider"); }
	/** The unique name for your section of settings, uses the class's FName. */
	virtual FName GetSectionName() const override { return TEXT("Insider"); }
public:

	UFUNCTION(BlueprintPure, DisplayName = "MyProperty_InsiderSettings")
	static UMyProperty_InsiderSettings* Get() { return GetMutableDefault<UMyProperty_InsiderSettings>(); }
public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = ConfigHierarchy)
	FString MyString;

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = ConfigHierarchy, meta = (ConfigHierarchyEditable))
	FString MyString_ConfigHierarchyEditable;

public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = Console, meta = (ConsoleVariable = "i.Insider.MyStringConsole"))
	FString MyString_ConsoleVariable;
public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = ConfigRestartRequired, meta = (ConfigRestartRequired="true"))
	FString MyString_ConfigRestartRequired;
public:
	virtual void PostInitProperties() override;
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};