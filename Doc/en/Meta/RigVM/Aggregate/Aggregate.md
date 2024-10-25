# Aggregate

- **Function Description:** Specifies that an attribute pin within an FRigUnit can serve as an operand for an extensible continuous binary operator.
- **Usage Location:** UPROPERTY
- **Engine Module:** RigVMStruct
- **Metadata Type:** bool
- **Restriction Type:** Attributes under FRigUnit
- **Commonly Used:** ★★★

Specifies that the attribute pin in an FRigUnit is to be used as an operand for an extensible continuous binary operator.

Remember to add Aggregate to both the Input and Output.

## Test Code:

```cpp
USTRUCT(meta = (DisplayName = "MyRigAggregate"))
struct INSIDER_API FRigUnit_MyRigAggregate : public FRigUnit
{
	GENERATED_BODY()

	RIGVM_METHOD()
		virtual void Execute() override;
public:
	UPROPERTY(meta = (Input,Aggregate))
	float A = 0.f;

	UPROPERTY(meta = (Input,Aggregate))
	float B= 0.f;

	UPROPERTY(meta = (Output,Aggregate))
	float Result = 0.f;
};
```

## Test Results:

It is apparent that after adding Aggregate, dynamic AddPin can be continued on the blueprint node. Additionally, a MyRigAggregate node is created in the Graph on the left. Upon opening it, you can observe that it essentially continues to assemble the original binary operations to achieve the effect of further AddPin.

![Untitled](Untitled.png)

## Principle:

Identify the Meta and then add the pins to AggregateInputs and AggregateOutputs.

```cpp
TArray<URigVMPin*> URigVMUnitNode::GetAggregateInputs() const
{
	TArray<URigVMPin*> AggregateInputs;
#if UE_RIGVM_AGGREGATE_NODES_ENABLED
	if (const UScriptStruct* Struct = GetScriptStruct())
	{
		for (URigVMPin* Pin : GetPins())
		{
			if (Pin->GetDirection() == ERigVMPinDirection::Input)
			{
				if (const FProperty* Property = Struct->FindPropertyByName(Pin->GetFName()))
				{
					if (Property->HasMetaData(FRigVMStruct::AggregateMetaName))
					{
						AggregateInputs.Add(Pin);
					}
				}
			}
		}
	}
	else
	{
		return Super::GetAggregateInputs();
	}
#endif
	return AggregateInputs;
}
```