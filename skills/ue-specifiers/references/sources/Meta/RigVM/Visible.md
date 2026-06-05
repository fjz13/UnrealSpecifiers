---
title: "Visible"
id: "meta.Visible"
kind: "meta"
symbol: "Visible"
category: "RigVM"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定FRigUnit下的该属性为常量引脚，无法连接变量"
usage: "UPROPERTY"
---

# Visible

## Decision Summary

- **Use when:** `Visible` metadata 的 `UPROPERTY` 场景需要：指定FRigUnit下的该属性为常量引脚，无法连接变量。
- **Do not use when:** 目标声明不属于 `UPROPERTY`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 指定FRigUnit下的该属性为常量引脚，无法连接变量。
- **使用位置：** UPROPERTY
- **引擎模块：** RigVMStruct
- **元数据类型：** bool
- **限制类型：** FRigUnit中属性
- **关联项：** [Input](Input.md)
- **常用程度：** ★★★

指定FRigUnit下的该属性为常量引脚，无法连接变量。

Visible和Input+Constant的效果是一致的。
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。

## 测试代码：

```cpp
USTRUCT(meta = (DisplayName = "MyRig"))
struct INSIDER_API FRigUnit_MyRig : public FRigUnit
{
	GENERATED_BODY()

	RIGVM_METHOD()
		virtual void Execute() override;

public:
	UPROPERTY()
	float MyFloat_Normal;

	UPROPERTY(meta = (Input))
	float MyFloat_Input;

	UPROPERTY(meta = (Output))
	float MyFloat_Output;

	UPROPERTY(meta = (Input, Output))
	float MyFloat_IO;

	UPROPERTY(meta = (Hidden))
	float MyFloat_Hidden;

	UPROPERTY(meta = (Visible))
	float MyFloat_Visible;

	UPROPERTY(meta = (Input, Constant))
	float MyFloat_Constant;
};
```

## 测试效果：

Visible和Input+Constant的效果是一致的，也是成为一个常量。


## 原理：

```cpp
UENUM(BlueprintType)
enum class ERigVMPinDirection : uint8
{
	Input, // A const input value
	Output, // A mutable output value
	IO, // A mutable input and output value
	Visible, // A const value that cannot be connected to
	Hidden, // A mutable hidden value (used for interal state)
	Invalid // The max value for this enum - used for guarding.
};

FRigVMPinInfo::FRigVMPinInfo(FProperty* InProperty, ERigVMPinDirection InDirection, int32 InParentIndex, const uint8* InDefaultValueMemory)
{
	bIsConstant = InProperty->HasMetaData(TEXT("Constant"));
}

void URigVMController::ConfigurePinFromProperty(FProperty* InProperty, URigVMPin* InOutPin, ERigVMPinDirection InPinDirection) const
{
		InOutPin->bIsConstant = InProperty->HasMetaData(TEXT("Constant"));
}

bool URigVMPin::CanBeBoundToVariable(const FRigVMExternalVariable& InExternalVariable, const FString& InSegmentPath) const
{
	if (bIsConstant)
	{
		return false;
	}
}
```
