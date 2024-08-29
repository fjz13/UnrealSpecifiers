// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorConfigBase.h"
#include "MyClass_EditorConfig.generated.h"


//(EditorConfig = MyEditorGame, IncludePath = Class/Config/MyClass_EditorConfig.h, ModuleRelativePath = Class/Config/MyClass_EditorConfig.h)
//ClassFlags:	CLASS_MatchedSerializers | CLASS_Native | CLASS_RequiredAPI | CLASS_TokenStreamAssembled | CLASS_Intrinsic | CLASS_Constructed 
//ClassConfigName:	Engine
UCLASS(EditorConfig = "MyEditorGame")
class INSIDEREDITOR_API UMyClass_EditorConfig : public UEditorConfigBase
{
public:
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditorConfig))
	int32 MyPropertyWithConfig = 123;
};


UCLASS()
class INSIDEREDITOR_API UMyClass_EditorConfig_Test :public UObject
{
	GENERATED_BODY()
public:

public:
	
	static void TestConfigSave();
	static void TestConfigLoad();

	UFUNCTION(BlueprintCallable,CallInEditor)
	static void RunTest();
};