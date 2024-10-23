// Fill out your copyright notice in the Description page of Project Settings.

#include "MyComponent_SkipUCSModifiedProperties.h"
#include "EngineUtils.h"

void AMyProperty_SkipUCSModifiedProperties_TestActor::CreateActor()
{
	UWorld* editorWorld = this->GetWorld();
	FActorSpawnParameters params;
	params.Template = (AActor*)ActorClass->GetDefaultObject();
	params.OverrideLevel=GetLevel();
	params.SpawnCollisionHandlingOverride=ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	params.bDeferConstruction=true;
	FTransform t;

	AMyProperty_SkipUCSModifiedProperties_BaseActor* newActor =Cast<AMyProperty_SkipUCSModifiedProperties_BaseActor>(editorWorld->SpawnActor(ActorClass,&t, params));//cannot call user construction script in BP actor
	newActor->CanCallConstruction=true;
	newActor->FinishSpawning(t);
}

void AMyProperty_SkipUCSModifiedProperties_TestActor::CleanupActor()
{
	UWorld* editorWorld = this->GetWorld();

	for (TActorIterator<AActor> It(editorWorld, ActorClass); It; ++It)
	{
		AActor* Actor = *It;
		editorWorld->DestroyActor(Actor);
	}
}
