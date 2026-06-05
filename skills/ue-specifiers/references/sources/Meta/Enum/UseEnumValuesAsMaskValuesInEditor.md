---
title: "UseEnumValuesAsMaskValuesInEditor"
id: "meta.UseEnumValuesAsMaskValuesInEditor"
kind: "meta"
symbol: "UseEnumValuesAsMaskValuesInEditor"
scope: "UseEnumValuesAsMaskValuesInEditor"
category: "Enum"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定枚举值已经是位移后的值，而不是位标记的索引下标"
usage: "UENUM"
---

# UseEnumValuesAsMaskValuesInEditor

## Decision Summary

- **Use when:** `UseEnumValuesAsMaskValuesInEditor` metadata 的 `UENUM` 场景需要：指定枚举值已经是位移后的值，而不是位标记的索引下标。
- **Do not use when:** 目标声明不属于 `UENUM`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 指定枚举值已经是位移后的值，而不是位标记的索引下标。
- **使用位置：** UENUM
- **元数据类型：** bool
- **关联项：** [Bitflags](Bitflags.md)
- **常用程度：** ★★

指定在编辑器里的枚举值直接就是位标记的最终值，而不是标记位。但是注意在C++里的定义是一样的形式：

```cpp
UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EMotionExtractor_MotionType : uint8
{
	None				= 0 UMETA(Hidden),
	Translation			= 1 << 0,
	Rotation			= 1 << 1,
	Scale				= 1 << 2,
	TranslationSpeed	= 1 << 3,
	RotationSpeed		= 1 << 4,
};

UENUM(meta = (Bitflags))
enum class EPCGChangeType : uint8
{
	None = 0,
	Cosmetic = 1 << 0,
	Settings = 1 << 1,
	Input = 1 << 2,
	Edge = 1 << 3,
	Node = 1 << 4,
	Structural = 1 << 5
};
```

## 测试的代码：

```cpp
UENUM(BlueprintType,Meta = (Bitflags))
enum class EMyEnum_BitFlags:uint8
{
	First,//0
	Second,//1
	Third,//2
};

UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EMyEnum_BitFlagsInEditor:uint8
{
	First,//0
	Second,//1
	Third,//2
};
```

## 测试的蓝图1：


## 测试的蓝图2：


因此可以看出前者是1<<2+1<<2，而后者是1|2，因此后者是直接把枚举值作为已经位移后的值
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。
