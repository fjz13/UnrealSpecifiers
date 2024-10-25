# UnsafeDuringActorConstruction

- **功能描述：** 标明该函数不能在Actor的构造函数里调用
- **使用位置：** UFUNCTION
- **引擎模块：** Blueprint
- **元数据类型：** bool
- **常用程度：** ★★

标明该函数不能在Actor的构造函数里调用。一般是涉及渲染及物理的函数，在Actor的构造期间不允许被调用。

## 测试代码：

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyFunction_Unsafe :public UBlueprintFunctionLibrary
{
public:
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	static void MySafeFunction();
	UFUNCTION(BlueprintCallable, meta=(UnsafeDuringActorConstruction = "true"))
	static void MyUnsafeFunction();
};
```

在蓝图里函数的细节面板上也可以设置该Meta：UnsafeDuringActorConstruction，和在C++里设置是一样的效果。

可以发现MyUnsafeFunction函数不能在Actor构造函数里被调用出来，而蓝图里自定义的函数加上UnsafeDuringActorConstruction 标志后也会生成相应的警告和编译错误信息。

![Untitled](Untitled.png)

## 原理：

在蓝图中有该系列的判断，一目了然。

```cpp
bool UEdGraphSchema_K2::CanFunctionBeUsedInGraph(const UClass* InClass, const UFunction* InFunction, const UEdGraph* InDestGraph, uint32 InAllowedFunctionTypes, bool bInCalledForEach, FText* OutReason) const
{
const bool bIsUnsafeForConstruction = InFunction->GetBoolMetaData(FBlueprintMetadata::MD_UnsafeForConstructionScripts);
if (bIsUnsafeForConstruction && bIsConstructionScript)
{
	if(OutReason != nullptr)
	{
		*OutReason = LOCTEXT("FunctionUnsafeForConstructionScript", "Function cannot be used in a Construction Script.");
	}

	return false;
}
}
```