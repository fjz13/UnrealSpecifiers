// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProperty_Material.h"
#include "MaterialCompiler.h"

UMyProperty_MyMaterialExpression::UMyProperty_MyMaterialExpression(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
#if WITH_EDITORONLY_DATA
	MenuCategories.Add(INVTEXT("Insider"));
#endif
}

#if WITH_EDITOR
int32 UMyProperty_MyMaterialExpression::Compile(class FMaterialCompiler* Compiler, int32 OutputIndex)
{
	int32 IndexAlpha = MyAlpha.GetTracedInput().Expression ? MyAlpha.Compile(Compiler) : Compiler->Constant(ConstAlpha);

	return 0;
}

void UMyProperty_MyMaterialExpression::GetCaption(TArray<FString>& OutCaptions) const
{
	OutCaptions.Add(TEXT("Insider Material Expression Test"));
}

bool UMyProperty_MyMaterialExpression::GenerateHLSLExpression(FMaterialHLSLGenerator& Generator, UE::HLSLTree::FScope& Scope, int32 OutputIndex, UE::HLSLTree::FExpression const*& OutExpression) const
{
	return true;
}

#endif // WITH_EDITOR
