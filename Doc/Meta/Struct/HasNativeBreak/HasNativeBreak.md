# HasNativeBreak

功能描述: 为该结构指定一个C++内的UFunction函数作为Break节点的实现
使用位置: USTRUCT
Feature: Blueprint
引擎模块: Struct
元数据类型: string="abc"
Example: HasNativeBreak="Module.Class.Function”
Status: Done
Sub-item: HasNativeMake (HasNativeMake.md)
常用程度: 5

为该结构指定一个C++内的UFunction函数作为Break节点的实现

指定一个static *UFunction函数的完整路径值，一般是”/*Script/*Module.Class.Function”*

这个函数一般是BlueprintThreadSafe，因为这种纯Make和Break函数一般不带副作用，因此可以随便的多线程调用。

测试代码：

```cpp
//(BlueprintType = true, HasNativeBreak = /Script/Insider.MyHasNativeStructHelperLibrary.BreakMyHasNativeStruct, HasNativeMake = /Script/Insider.MyHasNativeStructHelperLibrary.MakeMyHasNativeStruct, ModuleRelativePath = Struct/MyStruct_NativeMakeBreak.h)
USTRUCT(BlueprintType, meta = (HasNativeBreak = "/Script/Insider.MyHasNativeStructHelperLibrary.BreakMyHasNativeStruct", HasNativeMake = "/Script/Insider.MyHasNativeStructHelperLibrary.MakeMyHasNativeStruct"))
struct INSIDER_API FMyStruct_HasNative
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MyReadWrite;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float MyReadOnly;
	UPROPERTY(EditAnywhere)
	float MyNotBlueprint;
};

USTRUCT(BlueprintType)
struct INSIDER_API FMyStruct_HasDefaultMakeBreak
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MyReadWrite;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float MyReadOnly;
	UPROPERTY(EditAnywhere)
	float MyNotBlueprint;
};

UCLASS()
class UMyHasNativeStructHelperLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	static void BreakMyHasNativeStruct(const FMyStruct_HasNative& myStruct, float& outValue)
	{
		outValue = myStruct.MyReadWrite + myStruct.MyReadOnly + myStruct.MyNotBlueprint;
	}

	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	static FMyStruct_HasNative MakeMyHasNativeStruct(float value)
	{
		FMyStruct_HasNative result;
		result.MyReadWrite = value;
		result.MyReadOnly = value;
		result.MyNotBlueprint = value;
		return result;
	}
};
```

蓝图节点：

![Untitled](HasNativeBreak/Untitled.png)

原理是：

通过Meta里配置的值去找UFunction函数，因此我们配置的时候需要提供的是能找到UFunction的完整路径值。这个函数的签名会自动的被反射提取信息到UK2Node_CallFunction节点上，从而构造出不同样式的Make和Break蓝图节点。

```cpp
E:\P4V\Engine\Source\Editor\BlueprintGraph\Private\EdGraphSchema_K2.cpp

const FString& MetaData = StructType->GetMetaData(FBlueprintMetadata::MD_NativeMakeFunction);
const UFunction* Function = FindObject<UFunction>(nullptr, *MetaData, true);

UK2Node_CallFunction* CallFunctionNode;

if (Params.bTransient || Params.CompilerContext)
{
	CallFunctionNode = (Params.bTransient ? NewObject<UK2Node_CallFunction>(Graph) : Params.CompilerContext->SpawnIntermediateNode<UK2Node_CallFunction>(GraphNode, Params.SourceGraph));
	CallFunctionNode->SetFromFunction(Function);
	CallFunctionNode->AllocateDefaultPins();
}
else
{
	FGraphNodeCreator<UK2Node_CallFunction> MakeStructCreator(*Graph);
	CallFunctionNode = MakeStructCreator.CreateNode(false);
	CallFunctionNode->SetFromFunction(Function);
	MakeStructCreator.Finalize();
}

SplitPinNode = CallFunctionNode;
```