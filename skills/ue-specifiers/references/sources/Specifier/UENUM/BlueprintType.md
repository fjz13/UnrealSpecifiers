---
title: "BlueprintType"
id: "UENUM.BlueprintType"
kind: "specifier"
symbol: "BlueprintType"
scope: "UENUM"
category: "BlueprintType"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "可以作为蓝图变量"
usage: "UENUM / BlueprintType"
---

# BlueprintType

## Decision Summary

- **Use when:** enum 需要作为 Blueprint 变量、参数、返回值或下拉选项。
- **Do not use when:** enum 只在 C++ 内部使用。
- **Requires:** 枚举项名称和 UMETA 展示应适合 Blueprint 用户。
- **Conflicts:** 不等同于 bitmask/flags 语义。
- **Prefer instead:** C++-only enum 保持普通 enum 或不暴露。

- **功能描述：**  可以作为蓝图变量
- **元数据类型：** bool
- **引擎模块：** Blueprint
- **作用机制：** 在Meta中增加[BlueprintType](../../Meta/Blueprint/BlueprintType.md)
- **常用程度：★★★★★**

和其他地方的BlueprintType用法一样。

## 行为

UE5.8 UHT 的默认 `BlueprintType` specifier 写入 `BlueprintType=true` metadata。用于 UENUM 时表示该枚举类型可作为 Blueprint 类型使用。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `UhtDefaultSpecifiers.cs` `BlueprintTypeSpecifier` writes `BlueprintType` metadata
  - UE5.8 `UhtEnumParser.cs` routes `UENUM` to enum specifier table
  - 本地样例辅助对照：`D:/github/GitWorkspace/Hello/Source/Insider/Enum/MyEnum_Flags.h`。

## 常见误用

把它和 bitmask/flag 语义混淆；`BlueprintType` 只控制 Blueprint 类型暴露，不改变枚举值。
