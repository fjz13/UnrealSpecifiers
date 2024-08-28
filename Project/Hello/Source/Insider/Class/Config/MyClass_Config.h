// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyClass_Config.generated.h"



//op(Engine) \
//op(Game) \
//op(Input) \
//op(DeviceProfiles) \
//op(GameUserSettings) \
//op(Scalability) \
//op(RuntimeOptions) \
//op(InstallBundle) \
//op(Hardware) \
//op(GameplayTags)

//ClassFlags:	CLASS_Config | CLASS_MatchedSerializers | CLASS_Native | CLASS_RequiredAPI | CLASS_TokenStreamAssembled | CLASS_Intrinsic | CLASS_Constructed 
//ClassConfigName:	Game
UCLASS(Config = Game)
class INSIDER_API UMyClass_Config :public UObject
{
	GENERATED_BODY()
public:
	UMyClass_Config(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyProperty = 123;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Config)
		int32 MyPropertyWithConfig = 123;
};

//ClassFlags:	CLASS_Config | CLASS_MatchedSerializers | CLASS_Native | CLASS_PerObjectConfig | CLASS_RequiredAPI | CLASS_TokenStreamAssembled | CLASS_Intrinsic | CLASS_Constructed 
//ClassConfigName:	Game
UCLASS(Config = Game,PerObjectConfig)
class INSIDER_API UMyClass_PerObjectConfig :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyProperty = 123;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Config)
		int32 MyPropertyWithConfig = 123;
};

//ClassFlags:	CLASS_Config | CLASS_MatchedSerializers | CLASS_Native | CLASS_RequiredAPI | CLASS_TokenStreamAssembled | CLASS_Intrinsic | CLASS_Constructed | CLASS_ConfigDoNotCheckDefaults 
//ClassConfigName:	Game
UCLASS(Config = Game,configdonotcheckdefaults)
class INSIDER_API UMyClass_ConfigDoNotCheckDefaults :public UMyClass_Config
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Config)
		int32 MyPropertyWithConfigSub = 123;
};

UCLASS(Config = Game)
class INSIDER_API UMyClass_ConfigDefaultChild :public UMyClass_Config
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Config)
		int32 MyPropertyWithConfigSub = 123;
};



UCLASS()
class INSIDER_API UMyClass_Config_Test :public UObject
{
	GENERATED_BODY()
public:

public:
	static void TestConfigSave();
	static void TestConfigLoad();

	static void TestPerObjectConfigSave();
	static void TestPerObjectConfigLoad();


	static void TestConfigCheckDefaultSave();
	static void TestConfigCheckDefaultLoad();


	static void TestGlobalConfig();

	static void RunTest();
};