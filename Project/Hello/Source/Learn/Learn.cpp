// Fill out your copyright notice in the Description page of Project Settings.

#include "Learn.h"
#include "Modules/ModuleManager.h"
#include "Log/LogTypes.h"

#include "Subsystems/UMyGameInstanceSubsystemBase.h"

void FLearnModule::StartupModule()
{
	//UE_LOG(LogLearn, Warning, TEXT("%s"), L"StartupModule");
	

	//UObject* bpAsset = LoadObject<UObject>(NULL, TEXT("/Game/BP_MyGameInstanceSubsystem.BP_MyGameInstanceSubsystem_C"));

	//TArray<UClass*> childClasses;
	//GetDerivedClasses(UMyGameInstanceSubsystemBase::StaticClass(), childClasses);
}

void FLearnModule::ShutdownModule()
{
	//UE_LOG(LogLearn, Warning, TEXT("%s"), L"StartupModule");

}

IMPLEMENT_MODULE(FLearnModule, Learn);

//IMPLEMENT_PRIMARY_GAME_MODULE(FDefaultGameModuleImpl, Learn, "Learn");
