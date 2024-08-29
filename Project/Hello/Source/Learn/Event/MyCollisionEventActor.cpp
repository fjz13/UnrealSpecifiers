// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCollisionEventActor.h"
#include "LearnTypes.h"

AMyCollisionEventActor::AMyCollisionEventActor()
{
	mBoxComponent = CreateDefaultSubobject<UBoxComponent>(L"BoxCollision");
	RootComponent = mBoxComponent;
	mBoxComponent->SetGenerateOverlapEvents(true);
}

void AMyCollisionEventActor::BeginPlay()
{
	Super::BeginPlay();
	mBoxComponent->SetSimulatePhysics(true);

	FActorBeginOverlapSignature::FDelegate del;
	del.BindUFunction(this, "OnMyBeginOverlap");
	OnActorBeginOverlap.Add(del);

	mBoxComponent->OnComponentBeginOverlap.Add(del);

}

void AMyCollisionEventActor::OnMyBeginOverlap(AActor* overlapAcor, AActor* otherActor)
{
	FString name = otherActor->GetFName().ToString();
	FString str = FString::Printf(L"BeginOverlap");
	GEngine->AddOnScreenDebugMessage(-1, LearnTypes::ScreenMessageDuration, FColor::Red, str);
}
