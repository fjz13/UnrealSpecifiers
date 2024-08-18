# CommutativeAssociativeBinaryOperator

功能描述: 标记一个二元运算函数的运算支持交换律和结合律，在蓝图节点上增加一个“+”引脚，允许动态的直接添加多个输入值。
使用位置: UFUNCTION
Feature: Blueprint
引擎模块: Blueprint
元数据类型: bool
Example: CommutativeAssociativeBinaryOperator=“true”
Status: Done
常用程度: 4

标记一个二元运算函数的运算支持交换律和结合律，在蓝图节点上增加一个“+”引脚，允许动态的直接添加多个输入值。而不需要自己手动创建多个本函数节点来运算，这是蓝图提供的便利功能之一。

CommutativeAssociativeBinaryOperator的限制是函数必须是BlueprintPure并且有两个参数。否则会产生编译报错或功能失效。

测试代码：

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

蓝图效果：

![Untitled](CommutativeAssociativeBinaryOperator/Untitled.png)

## 原理：

标记CommutativeAssociativeBinaryOperator的函数会采用UK2Node_CommutativeAssociativeBinaryOperator来生成节点。这个二元运算满足交换率和结合律，因此可以通过多次的调用本函数来支持多个输入值的运算。在UK2Node_CommutativeAssociativeBinaryOperator展开的时候，会创建中间的多个UK2Node_CommutativeAssociativeBinaryOperator来形成调用序列。

在源码中的应用是一些二元运算，在UKismetMathLibrary中有大量的运用，典型的比如FVector的互相运算。

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