// Fill out your copyright notice in the Description page of Project Settings.

#include "MyConfigActor.h"

AMyConfigActor::AMyConfigActor()
{
	
}

void AMyConfigActor::WriteConfig(FString sectionName,FString keyName,FString valueName,FString fileName)
{
	FString path = FPaths::ProjectDir()/ fileName;
	GConfig->SetString(*sectionName, *keyName, *valueName, path);
	GConfig->Flush(false);
}

FString AMyConfigActor::ReadConfig(FString sectionName, FString keyName, FString fileName)
{
	FString path = FPaths::ProjectDir() / fileName;

	FString result;
	GConfig->GetString(*sectionName, *keyName, result, path);
	return result;
}
