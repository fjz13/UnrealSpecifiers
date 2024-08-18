# PinHiddenByDefault

功能描述: 使得这个结构里的属性在蓝图里作为引脚时默认是隐藏的。
使用位置: UPROPERTY
Feature: Blueprint
引擎模块: Pin
元数据类型: bool
限制类型: struct member property
Status: Done
常用程度: 2

使得这个结构里的属性在蓝图里作为引脚时默认是隐藏的。

需要注意的是这个meta只作用于结构的成员属性，且只作用在蓝图里的节点。在有些时候一个结构里拥有多个属性，但不是希望一下子暴露所有属性来让用户编辑，有些属性可能是高级属性需要一开始隐藏起来。

该标记也可以在动画蓝图中，让动画节点的某些属性不暴露成引脚。

测试代码：

```cpp
USTRUCT(BlueprintType)
struct FMyPinHiddenTestStruct
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category=PinHiddenByDefaultTest)
	int32 MyInt_NotHidden = 123;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category=PinHiddenByDefaultTest, meta = (PinHiddenByDefault))
	int32 MyInt_PinHiddenByDefault = 123;
};

	UFUNCTION(BlueprintCallable)
	static FMyPinHiddenTestStruct MyHiddenPinTestFunc(FMyPinHiddenTestStruct Input);
```

测试结果：

可以发现MakeStruct和BreakStruct的节点，默认只有MyInt_NotHidden。当选择该蓝图节点时，可以在右侧细节面板看到MyInt_PinHiddenByDefault 的显示默认没有选中，这就是区别。

同样的，当该结构当作函数输入和输出参数的时候，当用SplitStuctPin展开结构节点，会发现MyInt_PinHiddenByDefault 也被隐藏了起来。

![Untitled](PinHiddenByDefault/Untitled.png)

## 原理：

通过源码可以发现，FStructOperationOptionalPinManager 里使用了该meta，然后FMakeStructPinManager 和FBreakStructPinManager 继承了，从而使得PinHiddenByDefault的Pin一开始不显示。

```cpp
struct FStructOperationOptionalPinManager : public FOptionalPinManager
{
	//~ Begin FOptionalPinsUpdater Interface
	virtual void GetRecordDefaults(FProperty* TestProperty, FOptionalPinFromProperty& Record) const override
	{
		Record.bCanToggleVisibility = true;
		Record.bShowPin = true;
		if (TestProperty)
		{
			Record.bShowPin = !TestProperty->HasMetaData(TEXT("PinHiddenByDefault"));
			if (Record.bShowPin)
			{
				if (UStruct* OwnerStruct = TestProperty->GetOwnerStruct())
				{
					Record.bShowPin = !OwnerStruct->HasMetaData(TEXT("HiddenByDefault"));
				}
			}
		}
	}

	virtual void CustomizePinData(UEdGraphPin* Pin, FName SourcePropertyName, int32 ArrayIndex, FProperty* Property) const override;
	// End of FOptionalPinsUpdater interfac
};

struct FMakeStructPinManager : public FStructOperationOptionalPinManager
{}
struct FBreakStructPinManager : public FStructOperationOptionalPinManager
{}

```