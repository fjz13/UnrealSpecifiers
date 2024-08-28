#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaveCellActor.generated.h"

UCLASS(Blueprintable, BlueprintType)
class AWaveCellActor :public AActor
{
	GENERATED_BODY()
		AWaveCellActor();
public:
	UPROPERTY(EditDefaultsOnly)
	FVector2D Size;
public:
	virtual void BeginPlay()override;
	virtual void Tick(float DeltaSeconds)override;

	UFUNCTION(BlueprintCallable)
	void ApplyImpluse(float delta);
public:
	void InitializePosition(class AWaveActor* parentActor);
	void UpdatePosition(float DeltaSeconds);
	uint32 Row;
	uint32 Column;
private:
	//4a+4b+c=1
	//ȡa=0.3,b=0.2,c=-1
	float mNearFactor = 1.2f;
	float mCornerNearFactor = 0.8f;
	float mSelfFactor = -1.f;
	//f1=f0*damping
	float mDamping = 0.8f;
private:
	TArray<AWaveCellActor*> mNearActors;	//4
	TArray<AWaveCellActor*> mCornerNearActors;	//4
	float Delta;
	FVector mLocation;
};
