# ArrayParm

Description: 指定一个函数为使用Array<*>的函数，数组元素类型为通配符的泛型。
Usage: UFUNCTION
Feature: Blueprint
Group: Blueprint
Type: strings="a，b，c"
Example: ArrayParm="ArrayA, ArrayB, ..”
Status: Done
Sub-item: ArrayTypeDependentParams (ArrayTypeDependentParams.md)

指定一个函数为使用Array<*>的函数，数组元素类型为通配符的泛型。

在内部逻辑上的处理区别是有ArrayParm的会采用UK2Node_CallArrayFunction来生成节点，而不是UK2Node_CallFunction。

ArrayParam可以指定多个，用逗号分隔开。

在源码里只在UKismetArrayLibrary里使用，但如果自己也想顶一个数组的操作，则也可以加上ArrayParam。

因为数组元素类型为通配符的泛型，因此在C++中实现的时候，要配合CustomThunk来自己写一些蓝图逻辑胶水代码才好正确处理不同的数组类型。这部分可以参照源码里UKismetArrayLibrary的样例模仿。

测试代码：

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyFunction_Param :public UBlueprintFunctionLibrary
{
public:
	GENERATED_BODY()
public:
//Array
	UFUNCTION(BlueprintPure, CustomThunk, meta = (ArrayParm = "TargetArray"))
	static int32 MyArray_Count(const TArray<int32>& TargetArray);
	static int32 GenericMyArray_Count(const void* TargetArray, const FArrayProperty* ArrayProp);
	DECLARE_FUNCTION(execMyArray_Count);

	UFUNCTION(BlueprintPure, CustomThunk, meta = (ArrayParm = "ArrayA,ArrayB", ArrayTypeDependentParams = "ArrayB"))
	static int32 MyArray_CompareSize(const TArray<int32>& ArrayA, const TArray<int32>& ArrayB);
	static int32 GenericMyArray_CompareSize(void* ArrayA, const FArrayProperty* ArrayAProp, void* ArrayB, const FArrayProperty* ArrayBProp);
	DECLARE_FUNCTION(execMyArray_CompareSize);
};
```

蓝图效果：

![Untitled](ArrayParm/Untitled.png)

可以看到，在没有连接具体数组类型的时候，Array是灰色的通配符类型。而连接上不同的数组类型，Array参数引脚就会自动变成相应的类型，这些逻辑是在UK2Node_CallArrayFunction中实现的，有兴趣的去自行翻阅。