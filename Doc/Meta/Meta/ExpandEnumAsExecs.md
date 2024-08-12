# ExpandEnumAsExecs

Usage: UFUNCTION
Feature: Blueprint
Type: strings="a，b，c"
Description: 指定多个enum或bool类型的函数参数，自动根据条目生成相应的多个输入或输出执行引脚，并根据实参值不同来相应改变控制流。
Example: ExpandEnumAsExecs="EnumA, EnumB | boolVal, ReturnValue”
Status: Done
Group: Blueprint
Sub-item: ExpandBoolAsExecs (ExpandBoolAsExecs.md)

指定多个enum或bool类型的函数参数，自动根据条目生成相应的多个输入或输出执行引脚，并根据实参值不同来相应改变控制流。

支持改变输入和输出的Exec，输入Exec只可以一个，但是输出ExecEnum Pin可以多个。但是不能用在BlueprintPure上（都没Exec引脚了）。

也可以通过‘|’来分隔。

支持3种参数类型，enum class，TEnumAsByte<EMyExecPins2::Type>和bool，eunum必须用UENUM标记。

引用类型的参数和返回值用作输出Pin，值类型的参数用作输入Pin。
可以用“ReturnValue”这个名字来指定使用返回值参数。

如果有多个输出Enum参数，会在函数的调用之后排成Sequecene来一一分别根据输出Enum的值来触发输出Exec。

测试代码：

```cpp
UENUM(BlueprintType)
enum class EMyExecPins : uint8
{
	First,
	Second,
	Third,
};

UENUM(BlueprintType)
namespace EMyExecPins2
{
	enum Type : int
	{
		Found,
		NotFound,
	};
}

UENUM(BlueprintType)
enum class EMyExecAnimalPins : uint8
{
	Cat,
	Dog,
};

public:
	UFUNCTION(BlueprintCallable, meta = (ExpandEnumAsExecs = "Pins"))
	static int32 MyEnumAsExec_Output(FString Name, EMyExecPins& Pins) { return 0; }

	UFUNCTION(BlueprintCallable, meta = (ExpandEnumAsExecs = "Pins"))
	static int32 MyEnumAsExec_Input(FString Name, TEnumAsByte<EMyExecPins2::Type> Pins) { return 0; }

	UFUNCTION(BlueprintCallable, meta = (ExpandEnumAsExecs = "ReturnValue"))
	static EMyExecPins MyEnumAsExec_Return(FString Name) { return EMyExecPins::First; }
public:
	UFUNCTION(BlueprintCallable, meta = (ExpandEnumAsExecs = "Pins"))
	static int32 MyBoolAsExec_Output(FString Name, bool& Pins) { return 0; }

	UFUNCTION(BlueprintCallable, meta = (ExpandEnumAsExecs = "Pins"))
	static int32 MyBoolAsExec_Input(FString Name, bool Pins) { return 0; }

	UFUNCTION(BlueprintCallable, meta = (ExpandEnumAsExecs = "ReturnValue"))
	static bool MyBoolAsExec_Return(FString Name) { return false; }
public:
	UFUNCTION(BlueprintCallable, meta = (ExpandEnumAsExecs = "InPins,OutAnimal|OutPins|ReturnValue"))
	static bool MyEnumAsExec_MultipleOut(FString Name, EMyExecPins InPins, EMyExecAnimalPins& OutAnimal, TEnumAsByte<EMyExecPins2::Type>& OutPins, FString& Result);
```

蓝图效果：

可以对照上述上述的函数原型和蓝图节点，可以发现ExpandEnumAsExecs执行3种参数类型。同时也验证了在同时拥有多个输出Enum参数的时候(代码里是OutAnimal|OutPins|ReturnValue)，会按顺序执行3次输出，就像用Sequence节点连接在了一起一样。

![Untitled](ExpandEnumAsExecs/Untitled.png)

## 原理：

真正的创建Pin是在void UK2Node_CallFunction::CreateExecPinsForFunctionCall(const UFunction* Function)，然后这些新的ExecPin和配套的赋值输入参数值，以及根据输出参数执行不同输出ExecPin的逻辑在UK2Node_CallFunction::ExpandNode中。代码太多就不贴出来了。

是如何控制Exec流向的？在函数的实现里，只要把相应的引用输出参数赋值，就自然会流向不同的Pin。这部分逻辑是在UK2Node_CallFunction::ExpandNode中实现。大概逻辑是针对Input引脚，会在中间插入UK2Node_AssignmentStatement，执行不同输入Pin，会相应的设置输入enum参数的的值。而针对Output引脚，会在中间插入UK2Node_SwitchEnum，这样当我们在函数中设置引用输出enum参数的值后，就可以根据enum的值，流向相应的不同输出Pin节点。而对bool参数，也会创建相应的中间蓝图节点来获取和设置bool参数。

函数原始的参数Pin会被隐藏起来，从而只暴露生成后的Exec Pin。