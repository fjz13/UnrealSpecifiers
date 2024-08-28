// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "LearnGameEngine.generated.h"

UCLASS()
class LEARN_API ULearnGameEngine : public UGameEngine
{
	GENERATED_BODY()

public:
	virtual void Start()override;
	virtual void PreExit() override;

};

//edit DefaultEngine.ini
/*
[/Script/Engine.Engine]
GameEngine=/Script/YourModuleName.YourGameEngine
EditorEngine=/Script/UnrealEd.EditorEngine
UnrealEdEngine=/Script/YourModuleName.YourGameEditorEngine
*/

//like:
/*
[/Script/Engine.Engine]
GameEngine=/Script/Engine/Learn.LearnGameEngine
EditorEngine=/Script/UnrealEd.EditorEngine
UnrealEdEngine=/Script/Learn.LearnEditorEngine
*/