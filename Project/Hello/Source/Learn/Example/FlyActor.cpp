#include "FlyActor.h"

AFlyActor::AFlyActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AFlyActor::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(ChooseRandTargetPosition());
	ChooseTarget();
	mState = AFlyActor::FlyingState::Flying;
}

void AFlyActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	switch (mState)
	{
	case AFlyActor::FlyingState::Flying:
	{
		FVector delta = mVelocity*DeltaSeconds;
		this->AddActorWorldOffset(delta);
		mFlyingTime -= DeltaSeconds;
		if (mFlyingTime<=0.f)
		{
			mState = AFlyActor::FlyingState::Waiting;
			mWaitTime = GetRandomWaitTime();
		}
		else
		{
			break;
		}
	}
	case AFlyActor::FlyingState::Waiting:
	{
		mWaitTime -= DeltaSeconds;
		if (mWaitTime <= 0.f)
		{
			ChooseTarget();
			mState = AFlyActor::FlyingState::Flying;
		}
	}
		break;
	default:
		break;
	}
}

void AFlyActor::ChooseTarget()
{
	mSpeed = GetRandomSpeed();
	FVector targetLocation = ChooseRandTargetPosition();
	FVector currrentLocation = GetActorLocation();

	FVector distance = targetLocation - currrentLocation;
	mVelocity = distance.GetSafeNormal()*mSpeed;
	mFlyingTime = distance.Size() / mSpeed;
}

FVector AFlyActor::ChooseRandTargetPosition() const
{
	FVector targetLocation;
	targetLocation.X = FMath::RandRange(PositionMin.X, PositionMax.X);
	targetLocation.Y = FMath::RandRange(PositionMin.Y, PositionMax.Y);
	targetLocation.Z = FMath::RandRange(PositionMin.Z, PositionMax.Z);
	return targetLocation;
}

float AFlyActor::GetRandomSpeed() const
{
	return FMath::RandRange(SpeedMin, SpeedMax);
}

float AFlyActor::GetRandomWaitTime() const
{
	return FMath::RandRange(WaitTimeMin, WaitTimeMax);
}
