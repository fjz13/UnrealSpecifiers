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
- 批次记录：`references/audits/ue5.8-p1-macro-param-struct-enum-pass.md`。

## 常见误用

把它和 bitmask/flag 语义混淆；`BlueprintType` 只控制 Blueprint 类型暴露，不改变枚举值。
