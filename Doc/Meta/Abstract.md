# Abstract

Description: 标识该FRigUnit为抽象类，不用实现Execute。
Usage: USTRUCT
Feature: RigVM
Group: RigVMStruct
Type: bool
LimitedType: FRigUnit类型上
Status: Done

标识该FRigUnit为抽象类，不用实现Execute，常常用作别的FRigUnit类的基类使用。

但如果还是实现了Execute，其实也还是可以在蓝图中调用的。

测试代码：

```cpp
USTRUCT(meta = (DisplayName = "MyRigAbstract",Abstract))
struct INSIDER_API FRigUnit_MyRigAbstract: public FRigUnit
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (Input))
	float MyFloat_Input = 123.f;

	UPROPERTY(meta = (Output))
	float MyFloat_Output = 123.f;
};
```

测试效果：

![Untitled](Abstract/Untitled.png)

原理：

在一些内部处理的时候，当然会略过这种抽象基类。

```cpp
void FRigVMBlueprintUtils::ForAllRigVMStructs(TFunction<void(UScriptStruct*)> InFunction)
{
	// Run over all unit types
	for(TObjectIterator<UStruct> StructIt; StructIt; ++StructIt)
	{
		if (*StructIt)
		{
			if(StructIt->IsChildOf(FRigVMStruct::StaticStruct()) && !StructIt->HasMetaData(FRigVMStruct::AbstractMetaName))
			{
				if (UScriptStruct* ScriptStruct = Cast<UScriptStruct>(*StructIt))
				{
					InFunction(ScriptStruct);
				}
			}
		}
	}
}
```