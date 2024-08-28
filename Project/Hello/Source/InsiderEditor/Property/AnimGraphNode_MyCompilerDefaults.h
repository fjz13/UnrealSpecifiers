// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Property/AnimBP/AnimNode_MyCompilerDefaults.h"
#include "AnimGraphNode_Base.h"
#include "AnimGraphNode_MyCompilerDefaults.generated.h"

UCLASS()
class INSIDEREDITOR_API UAnimGraphNode_MyCompilerDefaults : public UAnimGraphNode_Base
{
	GENERATED_UCLASS_BODY()
public:
	~UAnimGraphNode_MyCompilerDefaults();

	UPROPERTY(EditAnywhere, Category = Settings)
	FAnimNode_MyCompilerDefaults Node;

	// UEdGraphNode interface
	FText GetTooltipText() const override { return INVTEXT("AnimGraphNode_MyCompilerDefaults"); }
	FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return INVTEXT("AnimGraphNode_MyCompilerDefaults"); }
	FLinearColor GetNodeTitleColor() const override { return FLinearColor(0.75f, 0.75f, 0.75f); }
	//void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
	// End of UEdGraphNode interface

	// UAnimGraphNode_Base interface
	FString GetNodeCategory() const override { return TEXT("Animation|MyTest"); }
	//void CustomizePinData(UEdGraphPin* Pin, FName SourcePropertyName, int32 ArrayIndex) const override;
	//void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;
	//void ValidateAnimNodeDuringCompilation(class USkeleton* ForSkeleton, class FCompilerResultsLog& MessageLog) override;
	// End of UAnimGraphNode_Base interface

protected:
	virtual void OnProcessDuringCompilation(IAnimBlueprintCompilationContext& InCompilationContext, IAnimBlueprintGeneratedClassCompiledData& OutCompiledData);

};
