// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNodeBase.h"
#include "AnimNode_MyCustomizeProperty.generated.h"

USTRUCT(BlueprintInternalUseOnly)
struct INSIDER_API FAnimNode_MyCustomizeProperty : public FAnimNode_Base
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CustomProperty)
	FString MyString_Default;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CustomProperty, meta = (CustomizeProperty))
	FString MyString_CustomizeProperty;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CustomProperty, meta = (CustomizeProperty))
	FString MyString_CustomizeProperty_Other;
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


