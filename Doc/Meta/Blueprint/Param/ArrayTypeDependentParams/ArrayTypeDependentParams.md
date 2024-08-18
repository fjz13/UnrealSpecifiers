# ArrayTypeDependentParams

功能描述: 当ArryParam指定的函数拥有两个或以上Array参数的时候，指定哪些数组参数的类型也应该相应的被更新改变。
使用位置: UFUNCTION
Feature: Blueprint
元数据类型: string="abc"
Example: ArrayTypeDependentParams="Parameter”
Status: Done
Parent item: ArrayParm (ArrayParm.md)

当ArryParam指定的函数拥有两个或以上Array参数的时候，指定哪些数组参数的类型也应该相应的被更新改变。

指明一个参数的类型，用于确定ArrayParam的值类型

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

如果没有ArrayTypeDependentParams，在连接ArrayA后，ArrayB的类型依然没有确定，即使连接上了也是如此，这应该是引擎的实现所限制。编译会造成编译错误。

![Untitled](ArrayTypeDependentParams/Untitled.png)

因此ArrayTypeDependentParams可以指定另外的数组参数，其类型会由别的（第一个）数组实际参数所决定，即typeof(ArrayB)=typeof(ArrayA)。在示例代码里所示加上ArrayB作为ArrayTypeDependentParams 之后，MyArrayB无论是先连接到ArrayA还是ArrayB都可以触发二者改变为一致的数组类型。这是因为ArrayA作为第一个参数，天生在引擎内已经实现了第一个参数的动态类型实时变化。因此我们只要再加上ArrayB就好了。

![Untitled](ArrayParm/Untitled.png)

原理：

引擎内已经实现了第一个参数的动态类型实时变化：

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

关于ArrayDependentParam的作用机制，可以参照UK2Node_CallArrayFunction里的NotifyPinConnectionListChanged和PropagateArrayTypeInfo这两个函数的实现，可以看到其他的数组参数Pin类型被动态的修改为SourcePin的类型。