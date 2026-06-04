---
title: "HasNoOpConstructor"
id: "USTRUCT.HasNoOpConstructor"
kind: "specifier"
symbol: "HasNoOpConstructor"
scope: "USTRUCT"
category: "UHT"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定该结构拥有ForceInit的构造函数，这样在作为BP function返回值的时候，可以调用来初始化"
usage: "USTRUCT / UHT"
---

# HasNoOpConstructor

- **功能描述：** 指定该结构拥有ForceInit的构造函数，这样在作为BP function返回值的时候，可以调用来初始化
- **元数据类型：** bool
- **引擎模块：** UHT
- **限制类型：** 只在NoExportTypes.h供UHT使用
- **常用程度：** 0

指定该结构拥有ForceInit的构造函数，这样在作为BP Function返回值或参数的时候，引擎就知道这个结构有这么一个构造函数可以调用来初始化。

作用的地方是UhtHeaderCodeGenerator中的AppendEventParameter，为了这样的代码，这是一个暴露到BP中的Event，要为它生成一些胶水代码。这里FLinearColor 就是HasNoOpConstructor。例如以下这个函数：

```cpp
UFUNCTION(BlueprintNativeEvent, Category = "Modifier")
FLinearColor GetVisualizationColor(FInputActionValue SampleValue, FInputActionValue FinalValue) const;
```

生成的代码：

```cpp
struct InputModifier_eventGetVisualizationColor_Parms
	{
		FInputActionValue SampleValue;
		FInputActionValue FinalValue;
		FLinearColor ReturnValue;

		/** Constructor, initializes return property only **/
		InputModifier_eventGetVisualizationColor_Parms()
			: ReturnValue(ForceInit)//强制初始化
		{
		}
	};

static FName NAME_UInputModifier_GetVisualizationColor = FName(TEXT("GetVisualizationColor"));
	FLinearColor UInputModifier::GetVisualizationColor(FInputActionValue SampleValue, FInputActionValue FinalValue) const
	{
		InputModifier_eventGetVisualizationColor_Parms Parms;
		Parms.SampleValue=SampleValue;
		Parms.FinalValue=FinalValue;
		const_cast<UInputModifier*>(this)->ProcessEvent(FindFunctionChecked(NAME_UInputModifier_GetVisualizationColor),&Parms);
		return Parms.ReturnValue;
	}
```

因此要求该结构拥有ForceInit的构造函数

```cpp
FORCEINLINE explicit FLinearColor(EForceInit)
	: R(0), G(0), B(0), A(0)
	{}
```
## UE5.8 审计结论

UE5.8 UHT 或宏路径仍保留该条目；本轮按 UE5.8 标记为已验证。P3 中不少条目属于引擎内部、NoExportTypes 或插件专用用法，不建议普通项目代码直接套用。

## 原理：

```cpp
if (ScriptStruct.HasNoOpConstructor)
{
//If true, the an argument will need to be added to the constructor
	PropertyCaps |= UhtPropertyCaps.RequiresNullConstructorArg;
}
```