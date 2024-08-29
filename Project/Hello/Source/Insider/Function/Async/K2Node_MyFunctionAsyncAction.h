// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "K2Node_AsyncAction.h"
#include "UObject/ObjectMacros.h"

#include "K2Node_MyFunctionAsyncAction.generated.h"

class FBlueprintActionDatabaseRegistrar;


UCLASS()
class INSIDER_API UK2Node_MyFunctionAsyncAction : public UK2Node_AsyncAction
{
	GENERATED_BODY()

	// UK2Node interface
	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
	virtual void AllocateDefaultPins() override;
	// End of UK2Node interface

protected:
	virtual bool HandleDelegates(
		const TArray<FBaseAsyncTaskHelper::FOutputPinAndLocalVariable>& VariableOutputs, UEdGraphPin* ProxyObjectPin,
		UEdGraphPin*& InOutLastThenPin, UEdGraph* SourceGraph, FKismetCompilerContext& CompilerContext) override;
};
