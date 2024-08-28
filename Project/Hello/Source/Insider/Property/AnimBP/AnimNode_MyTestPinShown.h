// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNodeBase.h"
#include "AnimNode_MyTestPinShown.generated.h"

USTRUCT(BlueprintInternalUseOnly)
struct INSIDER_API FAnimNode_MyTestPinShown : public FAnimNode_Base
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PinShownByDefaultTest)
	int32 MyInt_NotShown = 123;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PinShownByDefaultTest, meta = (PinShownByDefault))
	int32 MyInt_PinShownByDefault = 123;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PinShownByDefaultTest, meta = (AlwaysAsPin))
	int32 MyInt_AlwaysAsPin = 123;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PinShownByDefaultTest, meta = (NeverAsPin))
	int32 MyInt_NeverAsPin = 123;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FoldPropertyTest, meta = (FoldProperty))
	int32 MyInt_FoldProperty = 123;
public:
	// FAnimNode_Base interface
	virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override {}
	virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override {}
	virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override {}
	virtual void Evaluate_AnyThread(FPoseContext& Output) override {}
	virtual void GatherDebugData(FNodeDebugData& DebugData) override {}
	virtual int32 GetLODThreshold() const override { return 3; }
	// End of FAnimNode_Base interface
};


