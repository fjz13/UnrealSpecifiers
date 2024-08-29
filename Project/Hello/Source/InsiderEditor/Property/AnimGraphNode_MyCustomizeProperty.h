// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Property/AnimBP/AnimNode_MyCustomizeProperty.h"
#include "AnimGraphNode_Base.h"
#include "AnimGraphNode_MyCustomizeProperty.generated.h"

UCLASS()
class INSIDEREDITOR_API UAnimGraphNode_MyCustomizeProperty : public UAnimGraphNode_Base
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, Category = Settings)
	FAnimNode_MyCustomizeProperty Node;

	// UEdGraphNode interface
	FText GetTooltipText() const override { return INVTEXT("AnimGraphNode_MyCustomizeProperty"); }
	FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return INVTEXT("AnimGraphNode_MyCustomizeProperty"); }
	FLinearColor GetNodeTitleColor() const override { return FLinearColor(0.75f, 0.75f, 0.75f); }
	//void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
	// End of UEdGraphNode interface

	// UAnimGraphNode_Base interface
	FString GetNodeCategory() const override { return TEXT("Animation|MyTest"); }
	//void CustomizePinData(UEdGraphPin* Pin, FName SourcePropertyName, int32 ArrayIndex) const override;
	//void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;
	//void ValidateAnimNodeDuringCompilation(class USkeleton* ForSkeleton, class FCompilerResultsLog& MessageLog) override;
	// End of UAnimGraphNode_Base interface
};
