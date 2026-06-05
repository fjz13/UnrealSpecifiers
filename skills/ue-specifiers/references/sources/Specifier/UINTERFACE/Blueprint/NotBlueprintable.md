---
title: "NotBlueprintable"
id: "UINTERFACE.NotBlueprintable"
kind: "specifier"
symbol: "NotBlueprintable"
scope: "UINTERFACE"
category: "Blueprint"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定不可以在蓝图中实现"
usage: "UINTERFACE / Blueprint"
---

# NotBlueprintable

## Decision Summary

- **Use when:** `NotBlueprintable` specifier 的 `UINTERFACE / Blueprint` 场景需要：指定不可以在蓝图中实现。
- **Do not use when:** 声明宏、目标类型或代码契约不属于 `UINTERFACE / Blueprint`。
- **Requires:** specifier 必须放在 UE5.8 UHT 支持的宏和声明位置，并满足正文 caveat。
- **Conflicts:** 不要和同类互斥 specifier 或语义相反的暴露/持久化/网络规则混用。
- **Prefer instead:** 能用更窄暴露范围或更明确 metadata 表达时，优先选择更窄方案。

- **功能描述：**  指定不可以在蓝图中实现
- **元数据类型：** bool
- **引擎模块：** Blueprint
- **作用机制：** 在Meta中去除[IsBlueprintBase](../../../Meta/Blueprint/IsBlueprintBase.md)、[BlueprintType](../../../Meta/Blueprint/BlueprintType.md)，等价于[CannotImplementInterfaceInBlueprint](../../../Meta/Blueprint/CannotImplementInterfaceInBlueprint.md)
- **关联项：** [Blueprintable](Blueprintable.md)
- **常用程度：★★★**

在Class Settings里的Interface里找不到不允许实现的接口。


什么情况下需要用到该标记？虽然不能在蓝图中实现，但是依然可以在C++里实现，也可以通过反射判断一个对象是否实现该接口。

## 行为

UE5.8 UHT 的默认 `NotBlueprintable` specifier 写入 `IsBlueprintBase=false`，并移除当前 metadata index 上的 `BlueprintType`。用于 UINTERFACE 时阻止 Blueprint 实现接口。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `UhtDefaultSpecifiers.cs` `NotBlueprintableSpecifier` writes `IsBlueprintBase=false` and removes `BlueprintType`
  - 本地样例辅助对照：`D:/github/GitWorkspace/Hello/Source/Insider/Interface/MyInterface_Test.h`。

## 常见误用

接口中仍声明 `BlueprintImplementableEvent`/`BlueprintNativeEvent` 并期待 Blueprint 实现；或和 `Blueprintable` 同时表达相反意图。
