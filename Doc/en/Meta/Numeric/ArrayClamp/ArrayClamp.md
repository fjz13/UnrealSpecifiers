# ArrayClamp

- **Function description:** Ensures that the value of an integer attribute is within the valid index range of a specified array, [0, ArrayClamp.Size() - 1]
- **Usage location:** UPROPERTY
- **Engine module:** Numeric Property
- **Metadata type:** int32
- **Restriction type:** int32
- **Commonly used:** ★★★

Ensures that the value of the integer attribute is within the valid index range of the specified array, [0, ArrayClamp.Size() - 1]

## Test code:

```cpp
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ArrayClampTest)
	int32 MyInt_NoArrayClamp = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ArrayClampTest, meta = (ArrayClamp = "MyIntArray"))
	int32 MyInt_HasArrayClamp = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ArrayClampTest)
	TArray<int32> MyIntArray;
```

## Test results:

It is evident that the integer value with ArrayClamp is constrained within the array's index range.

![ArrayClamp](ArrayClamp.gif)

## Principle:

Locates the Array attribute within the class based on the specified array name and then clamps the value of the integer attribute to the index range of the array.

```cpp
template <typename Type>
static Type ClampIntegerValueFromMetaData(Type InValue, FPropertyHandleBase& InPropertyHandle, FPropertyNode& InPropertyNode)
{
	Type RetVal = ClampValueFromMetaData<Type>(InValue, InPropertyHandle);

	//enforce array bounds
	const FString& ArrayClampString = InPropertyHandle.GetMetaData(TEXT("ArrayClamp"));
	if (ArrayClampString.Len())
	{
		FObjectPropertyNode* ObjectPropertyNode = InPropertyNode.FindObjectItemParent();
		if (ObjectPropertyNode && ObjectPropertyNode->GetNumObjects() == 1)
		{
			Type LastValidIndex = static_cast<Type>(GetArrayPropertyLastValidIndex(ObjectPropertyNode, ArrayClampString));
			RetVal = FMath::Clamp<Type>(RetVal, 0, LastValidIndex);
		}
		else
		{
			UE_LOG(LogPropertyNode, Warning, TEXT("Array Clamping isn't supported in multi-select (Param Name: %s)"), *InPropertyHandle.GetProperty()->GetName());
		}
	}

	return RetVal;
}
```