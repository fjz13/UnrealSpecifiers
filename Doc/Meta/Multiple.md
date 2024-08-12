# Multiple

Description: Used for numeric properties. Stipulates that the value must be a multiple of the metadata value.
Usage: UPROPERTY
Feature: Behavior
Group: Numeric Property
Type: int32
LimitedType: int32
Example:  meta = (Multiple = 5)
Status: Done

指定数字的值必须是Mutliple提供的值的整数倍。

测试代码：

```cpp
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MultipleTest)
	int32 MyInt_NoMultiple = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MultipleTest, meta = (Multiple = 5))
	int32 MyInt_HasMultiple = 100;
```

蓝图效果：

可以看到，拥有Multiple 的只能按照5的倍数来增长。

![Multiple.gif](Multiple/Multiple.gif)

原理：

```cpp
template <typename Type>
static Type ClampIntegerValueFromMetaData(Type InValue, FPropertyHandleBase& InPropertyHandle, FPropertyNode& InPropertyNode)
{
	Type RetVal = ClampValueFromMetaData<Type>(InValue, InPropertyHandle);

	//if there is "Multiple" meta data, the selected number is a multiple
	const FString& MultipleString = InPropertyHandle.GetMetaData(TEXT("Multiple"));
	if (MultipleString.Len())
	{
		check(MultipleString.IsNumeric());
		Type MultipleValue;
		TTypeFromString<Type>::FromString(MultipleValue, *MultipleString);
		if (MultipleValue != 0)
		{
			RetVal -= Type(RetVal) % MultipleValue;
		}
	}

	return RetVal;
}
```