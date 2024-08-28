// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyClass_DefaultConfig.generated.h"

//ClassFlags:	CLASS_DefaultConfig | CLASS_Config | CLASS_MatchedSerializers | CLASS_Native | CLASS_RequiredAPI | CLASS_TokenStreamAssembled | CLASS_Intrinsic | CLASS_Constructed 
//ClassConfigName:	MyGame
UCLASS(Config = MyGame,DefaultConfig)
class INSIDER_API UMyClass_DefaultConfig :public UDeveloperSettings
{
	GENERATED_BODY()
public:
	/** Gets the settings container name for the settings, either Project or Editor */
	virtual FName GetContainerName() const override { return TEXT("Project"); }
	/** Gets the category for the settings, some high level grouping like, Editor, Engine, Game...etc. */
	virtual FName GetCategoryName() const override { return TEXT("MyGame"); }
	/** The unique name for your section of settings, uses the class's FName. */
	virtual FName GetSectionName() const override { return TEXT("MyGame"); }
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Config)
		int32 MyPropertyWithConfig = 123;
};


UCLASS()
class INSIDER_API UMyClass_DefaultConfig_Test :public UObject
{
	GENERATED_BODY()
public:

public:

	static void TestDefaultConfigSave();
	static void TestDefaultConfigLoad();

	static void RunTest();
};