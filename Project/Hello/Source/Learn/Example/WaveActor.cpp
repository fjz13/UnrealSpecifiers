#include "WaveActor.h"
#include "WaveCellActor.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"

AWaveActor::AWaveActor()
{
	PrimaryActorTick.bCanEverTick = true;
	CellRowCount = 10;
	CellColumnCount = 10;

	static ConstructorHelpers::FClassFinder<AWaveCellActor> actorClass(L"/Script/Learn.WaveCellActor");
	if (actorClass.Class != nullptr)
	{
		CellActorClass = actorClass.Class;
	}
	
}

void AWaveActor::BeginPlay()
{
	Super::BeginPlay();
	UWorld* world = GetWorld();
	FTransform transform = FTransform::Identity;
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;

	for (uint32 i = 0; i < CellRowCount; ++i)
	{
		for (uint32 j = 0; j< CellColumnCount; ++j)
		{
			AWaveCellActor* actor = (AWaveCellActor*)world->SpawnActor(CellActorClass.Get(), &transform, spawnParams);
			mCellActors.Add(actor);
			actor->Row = i;
			actor->Column = j;
		}
	}

	//init near actors
	for (auto* actor:mCellActors)
	{
		actor->InitializePosition(this);
	}

}

void AWaveActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	for (auto* actor : mCellActors)
	{
		actor->UpdatePosition(DeltaSeconds);
	}
}

class AWaveCellActor* AWaveActor::GetCell(int32 row, int32 column) const
{
	uint32 index = row*CellColumnCount + column;
	if (mCellActors.IsValidIndex(index))
	{
		return mCellActors[index];
	}
	return nullptr;
}
