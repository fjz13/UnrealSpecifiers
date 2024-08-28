#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaveActor.generated.h"

UCLASS(Blueprintable, BlueprintType)
class AWaveActor :public AActor
{
	GENERATED_BODY()
		AWaveActor();
public:
	virtual void BeginPlay()override;
	virtual void Tick(float DeltaSeconds)override;
	UFUNCTION(BlueprintCallable,BlueprintPure)
	class AWaveCellActor* GetCell(int32 row, int32 column)const;
public:
	UPROPERTY(EditAnywhere)
	uint32 CellRowCount;

	UPROPERTY(EditAnywhere)
		uint32 CellColumnCount;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AWaveCellActor> CellActorClass;
protected:
	TArray<class AWaveCellActor*> mCellActors;


};
