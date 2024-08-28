#include "WaveCellActor.h"
#include "WaveActor.h"

AWaveCellActor::AWaveCellActor()
{
	Size = FVector2D(50.f, 50.f);
}

void AWaveCellActor::BeginPlay()
{
	Super::BeginPlay();

}

void AWaveCellActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AWaveCellActor::InitializePosition(AWaveActor* parentActor)
{
	mLocation = FVector::ZeroVector;
	mLocation.X = Row*Size.X;
	mLocation.Y = Column*Size.Y;
	SetActorRelativeLocation(mLocation);

	AWaveCellActor* actor;

	actor = parentActor->GetCell(Row + 1, Column);
	if (actor != nullptr)
	{
		mNearActors.Add(actor);
	}

	actor = parentActor->GetCell(Row - 1, Column);
	if (actor != nullptr)
	{
		mNearActors.Add(actor);
	}
	actor = parentActor->GetCell(Row, Column + 1);
	if (actor != nullptr)
	{
		mNearActors.Add(actor);
	}
	actor = parentActor->GetCell(Row, Column - 1);
	if (actor != nullptr)
	{
		mNearActors.Add(actor);
	}

	actor = parentActor->GetCell(Row + 1, Column + 1);
	if (actor != nullptr)
	{
		mCornerNearActors.Add(actor);
	}

	actor = parentActor->GetCell(Row + 1, Column - 1);
	if (actor != nullptr)
	{
		mCornerNearActors.Add(actor);
	}
	actor = parentActor->GetCell(Row - 1, Column + 1);
	if (actor != nullptr)
	{
		mCornerNearActors.Add(actor);
	}
	actor = parentActor->GetCell(Row - 1, Column - 1);
	if (actor != nullptr)
	{
		mCornerNearActors.Add(actor);
	}
}

void AWaveCellActor::UpdatePosition(float DeltaSeconds)
{
	float delta = 0.f;
	float nearDelta = 0.f;
	for (auto* actor : mNearActors)
	{
		nearDelta += actor->Delta;
	}

	float cornerNearDelta = 0.f;
	for (auto* actor : mCornerNearActors)
	{
		cornerNearDelta += actor->Delta;
	}

	Delta = mNearFactor*nearDelta + mCornerNearFactor*cornerNearDelta + mSelfFactor*Delta;
	//Delta *= mDamping;
	
	mLocation.Z = Delta;
	SetActorRelativeLocation(mLocation);
}

void AWaveCellActor::ApplyImpluse(float delta)
{
	Delta = delta;
	mLocation.Z = delta;
	SetActorRelativeLocation(mLocation);
}
