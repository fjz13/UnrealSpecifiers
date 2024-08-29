// Fill out your copyright notice in the Description page of Project Settings.

#include "MyMaterialExpression.h"
#include "MaterialCompiler.h"

UMyMaterialExpression_NotPrivate::UMyMaterialExpression_NotPrivate(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
#if WITH_EDITORONLY_DATA
	MenuCategories.Add(INVTEXT("Insider"));
#endif
}

#if WITH_EDITOR
int32 UMyMaterialExpression_NotPrivate::Compile(class FMaterialCompiler* Compiler, int32 OutputIndex)
{
	return 0;
}

void UMyMaterialExpression_NotPrivate::GetCaption(TArray<FString>& OutCaptions) const
{
	OutCaptions.Add(TEXT("Insider Material Expression Test"));
}

bool UMyMaterialExpression_NotPrivate::GenerateHLSLExpression(FMaterialHLSLGenerator& Generator, UE::HLSLTree::FScope& Scope, int32 OutputIndex, UE::HLSLTree::FExpression const*& OutExpression) const
{
	return true;
}

#endif // WITH_EDITOR




UMyMaterialExpression_Private::UMyMaterialExpression_Private(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
#if WITH_EDITORONLY_DATA
	MenuCategories.Add(INVTEXT("Insider"));
#endif
}

#if WITH_EDITOR
int32 UMyMaterialExpression_Private::Compile(class FMaterialCompiler* Compiler, int32 OutputIndex)
{
	return 0;
}

void UMyMaterialExpression_Private::GetCaption(TArray<FString>& OutCaptions) const
{
	OutCaptions.Add(TEXT("Insider Material Expression Test"));
}

bool UMyMaterialExpression_Private::GenerateHLSLExpression(FMaterialHLSLGenerator& Generator, UE::HLSLTree::FScope& Scope, int32 OutputIndex, UE::HLSLTree::FExpression const*& OutExpression) const
{
	return true;
}

#endif // WITH_EDITOR