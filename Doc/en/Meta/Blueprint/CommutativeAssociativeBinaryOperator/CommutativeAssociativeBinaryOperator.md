# CommutativeAssociativeBinaryOperator

- **Function Description:** Indicates that a binary operation function adheres to the commutative and associative laws, adding a "+" pin to the blueprint node that enables dynamic addition of multiple input values.
- **Usage Location:** UFUNCTION
- **Engine Module:** Blueprint
- **Metadata Type:** bool
- **Commonality:** ★★★★

Marking a binary operation function with this indicates support for the commutative and associative laws. A "+" pin is added to the blueprint node, allowing for the dynamic direct addition of multiple input values without the need to manually create several function nodes for computation. This is one of the convenient features provided by blueprints.

The restrictions of CommutativeAssociativeBinaryOperator are that the function must be BlueprintPure and have two parameters; otherwise, compilation errors or functional failures may occur.

## Test Code:

```cpp
	UFUNCTION(BlueprintCallable, meta = (CommutativeAssociativeBinaryOperator))
	static float My_CallableAdd_WithBinaryOperator(float A, float B) { return A + B; }

	UFUNCTION(BlueprintPure, meta = (CommutativeAssociativeBinaryOperator))
	static float My_PureAdd_WithBinaryOperator(float A, float B) { return A + B; }

	UFUNCTION(BlueprintPure, meta = ())
	static float My_Add_NoBinaryOperator(float A, float B) { return A + B; }

	// error : Commutative associative binary operators must have exactly 2 parameters of the same type and a return value.
	//UFUNCTION(BlueprintPure, meta = (CommutativeAssociativeBinaryOperator))
//	static float My_PureAdd3_WithBinaryOperator(float A, float B,float C) { return A + B+C; }
```

## Blueprint Effect:

![Untitled](Untitled.png)

## Principle:

Functions marked with CommutativeAssociativeBinaryOperator are generated using UK2Node_CommutativeAssociativeBinaryOperator nodes. This binary operation satisfies the commutative and associative laws, allowing for the computation of multiple input values through multiple invocations of the function. When UK2Node_CommutativeAssociativeBinaryOperator is expanded, several intermediate UK2Node_CommutativeAssociativeBinaryOperator nodes are created to form a calling sequence.

Applications in the source code include various binary operations, with extensive use in UKismetMathLibrary, such as operations involving FVector.

```cpp
void UK2Node_CommutativeAssociativeBinaryOperator::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	Super::ExpandNode(CompilerContext, SourceGraph);

	if (NumAdditionalInputs > 0)
	{
		const UEdGraphSchema_K2* Schema = CompilerContext.GetSchema();

		UEdGraphPin* LastOutPin = NULL;
		const UFunction* const Function = GetTargetFunction();

		const UEdGraphPin* SrcOutPin = FindOutPin();
		const UEdGraphPin* SrcSelfPin = FindSelfPin();
		UEdGraphPin* SrcFirstInput = GetInputPin(0);
		check(SrcFirstInput);

		for(int32 PinIndex = 0; PinIndex < Pins.Num(); PinIndex++)
		{
			UEdGraphPin* CurrentPin = Pins[PinIndex];
			if( (CurrentPin == SrcFirstInput) || (CurrentPin == SrcOutPin) || (SrcSelfPin == CurrentPin) )
			{
				continue;
			}

			UK2Node_CommutativeAssociativeBinaryOperator* NewOperator = SourceGraph->CreateIntermediateNode<UK2Node_CommutativeAssociativeBinaryOperator>();
			NewOperator->SetFromFunction(Function);
			NewOperator->AllocateDefaultPins();
			CompilerContext.MessageLog.NotifyIntermediateObjectCreation(NewOperator, this);

			UEdGraphPin* NewOperatorInputA = NewOperator->GetInputPin(0);
			check(NewOperatorInputA);
			if(LastOutPin)
			{
				Schema->TryCreateConnection(LastOutPin, NewOperatorInputA);
			}
			else
			{
				// handle first created node (SrcFirstInput is skipped, and has no own node).
				CompilerContext.MovePinLinksToIntermediate(*SrcFirstInput, *NewOperatorInputA);
			}

			UEdGraphPin* NewOperatorInputB = NewOperator->GetInputPin(1);
			check(NewOperatorInputB);
			CompilerContext.MovePinLinksToIntermediate(*CurrentPin, *NewOperatorInputB);

			LastOutPin = NewOperator->FindOutPin();
		}

		check(LastOutPin);

		UEdGraphPin* TrueOutPin = FindOutPin();
		check(TrueOutPin);
		CompilerContext.MovePinLinksToIntermediate(*TrueOutPin, *LastOutPin);

		BreakAllNodeLinks();
	}
}

```