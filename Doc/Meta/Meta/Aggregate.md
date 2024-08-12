# Aggregate

Usage: UPROPERTY
Feature: RigVM Pin
Type: bool
Description: 指定FRigUnit里的属性引脚为可扩展连续二元运算符的运算数。
LimitedType: FRigUnit下的属性
Status: Done
Group: RigVMStruct

指定FRigUnit里的属性引脚为可扩展连续二元运算符的运算数。

记得在Input和Output上都加上Aggregate。

测试代码：

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

测试效果：

可见加了Aggregate之后，在蓝图节点上就可以继续动态AddPin。在左侧的Graph上也会创建中间MyRigAggregate节点。点开后，可以看见，其实就是继续组装原始的二元运算来达成继续AddPin的效果。

![Untitled](Aggregate/Untitled.png)

原理：

识别该Meta然后然后把引脚加到AggregateInputs和AggregateOutputs里。

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