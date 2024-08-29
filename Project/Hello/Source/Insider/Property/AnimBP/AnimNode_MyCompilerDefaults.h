// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNodeBase.h"
#include "AnimNode_MyCompilerDefaults.generated.h"

USTRUCT(BlueprintInternalUseOnly)
struct INSIDER_API FAnimNode_MyCompilerDefaults : public FAnimNode_Base
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Links)
	FPoseLink Source;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CompilerDefaultsTest)
	FString MyString;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CompilerDefaultsTest, meta = (BlueprintCompilerGeneratedDefaults))
	FString MyString_CompilerDefaults;
public:
	// FAnimNode_Base interface
	virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;
	virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;
	virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;
	virtual void Evaluate_AnyThread(FPoseContext& Output) override;
	virtual void GatherDebugData(FNodeDebugData& DebugData) override;
	virtual int32 GetLODThreshold() const override { return 3; }
	// End of FAnimNode_Base interface
};


