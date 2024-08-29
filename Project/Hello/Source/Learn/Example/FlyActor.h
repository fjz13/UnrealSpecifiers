#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlyActor.generated.h"

UCLASS(Blueprintable, BlueprintType)
class AFlyActor :public AActor
{
	enum class FlyingState
	{
		Flying,
		Waiting,
	};

	GENERATED_BODY()
		AFlyActor();
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Move")
		float SpeedMin;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Move")
		float SpeedMax;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Move")
		float WaitTimeMin;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Move")
		float WaitTimeMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move", meta = (ExposeOnSpawn))
		FVector PositionMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move", meta = (ExposeOnSpawn))
		FVector PositionMax;
public:
	virtual void BeginPlay()override;
	virtual void Tick(float DeltaSeconds)override;

protected:
	FVector ChooseRandTargetPosition()const;
	float GetRandomSpeed()const;
	float GetRandomWaitTime()const;

	void ChooseTarget();

protected:
	FlyingState mState;
	float mSpeed;
	float mWaitTime;
	FVector mVelocity;
	float mFlyingTime;

};
