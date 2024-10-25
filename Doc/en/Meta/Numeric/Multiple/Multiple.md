# Multiple

- **Function Description:** Specifies that the value of a number must be an integer multiple of the value provided by Multiple.
- **Usage Location:** UPROPERTY
- **Engine Module:** Numeric Property
- **Metadata Type:** int32
- **Restriction Type:** int32
- **Commonality:** ★★★

The value of the specified number must be an integer multiple of the value provided by Multiple.

## Test Code:

```cpp
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MultipleTest)
	int32 MyInt_NoMultiple = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MultipleTest, meta = (Multiple = 5))
	int32 MyInt_HasMultiple = 100;
```

## Blueprint Effect:

It can be observed that values with Multiple can only increase in increments that are multiples of 5.

![Multiple](Multiple.gif)

## Principle:

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