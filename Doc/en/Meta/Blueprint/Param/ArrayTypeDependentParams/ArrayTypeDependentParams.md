# ArrayTypeDependentParams

- **Function description:** Specifies which array parameter types should be updated when a function, designated by ArryParam, has two or more array parameters.
- **Use location:** UFUNCTION
- **Metadata type:** string="abc"
- **Related items:** [ArrayParm](../ArrayParm/ArrayParm.md)

When a function specified by ArryParam has two or more array parameters, the types of the specified array parameters should also be updated accordingly.

Indicates the type of a parameter, used to determine the value type of ArrayParam

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyFunction_Param :public UBlueprintFunctionLibrary
{
public:
	GENERATED_BODY()
public:
//Array

	UFUNCTION(BlueprintPure, CustomThunk, meta = (ArrayParm = "ArrayA,ArrayB", ArrayTypeDependentParams = "ArrayB"))
	static int32 MyArray_CompareSize(const TArray<int32>& ArrayA, const TArray<int32>& ArrayB);
	static int32 GenericMyArray_CompareSize(void* ArrayA, const FArrayProperty* ArrayAProp, void* ArrayB, const FArrayProperty* ArrayBProp);
	DECLARE_FUNCTION(execMyArray_CompareSize);
};
```

If there are no ArrayTypeDependentParams, the type of ArrayB remains undetermined after connecting ArrayA, even if it is connected. This is a limitation of the engine's implementation, and compilation will result in errors.

![Untitled](Untitled.png)

Therefore, ArrayTypeDependentParams can specify an additional array parameter, whose type will be determined by the type of the other (first) array actual parameter, i.e., typeof(ArrayB)=typeof(ArrayA). As demonstrated in the sample code, by adding ArrayB as ArrayTypeDependentParams, MyArrayB can trigger a change to a consistent array type, whether it is connected to ArrayA or ArrayB first. This is because ArrayA, as the first parameter, has already implemented dynamic type changes in real-time within the engine. Thus, adding ArrayB is sufficient.

## Principle:

The engine has already implemented real-time dynamic type changes for the first parameter:

```cpp
void UK2Node_CallArrayFunction::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();

	UEdGraphPin* TargetArrayPin = GetTargetArrayPin();
	if (ensureMsgf(TargetArrayPin, TEXT("%s"), *GetFullName()))
	{
		TargetArrayPin->PinType.ContainerType = EPinContainerType::Array;
		TargetArrayPin->PinType.bIsReference = true;
		TargetArrayPin->PinType.PinCategory = UEdGraphSchema_K2::PC_Wildcard;
		TargetArrayPin->PinType.PinSubCategory = NAME_None;
		TargetArrayPin->PinType.PinSubCategoryObject = nullptr;
	}

	TArray< FArrayPropertyPinCombo > ArrayPins;
	GetArrayPins(ArrayPins);
	for(auto Iter = ArrayPins.CreateConstIterator(); Iter; ++Iter)
	{
		if(Iter->ArrayPropPin)
		{
			Iter->ArrayPropPin->bHidden = true;
			Iter->ArrayPropPin->bNotConnectable = true;
			Iter->ArrayPropPin->bDefaultValueIsReadOnly = true;
		}
	}

	PropagateArrayTypeInfo(TargetArrayPin);
}
```

For the mechanism of ArrayDependentParam, you can refer to the implementation of the functions NotifyPinConnectionListChanged and PropagateArrayTypeInfo in UK2Node_CallArrayFunction. It can be observed that the types of other array parameter pins are dynamically changed to match the type of the SourcePin.