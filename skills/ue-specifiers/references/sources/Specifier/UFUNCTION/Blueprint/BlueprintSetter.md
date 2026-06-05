---
title: "BlueprintSetter"
id: "UFUNCTION.BlueprintSetter"
kind: "specifier"
symbol: "BlueprintSetter"
scope: "UFUNCTION"
category: "Blueprint"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定该函数作为属性的自定义Set函数"
usage: "UFUNCTION / Blueprint"
---

# BlueprintSetter

## Decision Summary

- **Use when:** `BlueprintSetter` specifier 的 `UFUNCTION / Blueprint` 场景需要：指定该函数作为属性的自定义Set函数。
- **Do not use when:** 声明宏、目标类型或代码契约不属于 `UFUNCTION / Blueprint`。
- **Requires:** specifier 必须放在 UE5.8 UHT 支持的宏和声明位置，并满足正文 caveat。
- **Conflicts:** 不要和同类互斥 specifier 或语义相反的暴露/持久化/网络规则混用。
- **Prefer instead:** 能用更窄暴露范围或更明确 metadata 表达时，优先选择更窄方案。

- **功能描述：** 指定该函数作为属性的自定义Set函数。
- **元数据类型：** bool
- **引擎模块：** Blueprint
- **作用机制：** 在Meta中加入[BlueprintSetter](../../../Meta/Blueprint/BlueprintSetter.md)，在FunctionFlags中加入FUNC_BlueprintCallable 
- **常用程度：** ★★

指定该函数作为属性的自定义Set函数。

此说明符隐含BlueprintCallable。

更多可以参考UPROPERTY的BlueprintSetter

## 行为

在 UE5.8 UHT 中设置 accessor export flag，写入 `BlueprintCallable` 和 `BlueprintSetter` metadata。UHT 拒绝把 Blueprint event 同时作为 setter。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `UhtFunctionSpecifiers.cs` 对应 specifier 分支
  - UE5.8 `UhtFunction.cs` replicated/event 校验
  - 本地样例辅助对照：`D:/github/GitWorkspace/Hello/Source/Insider/Property/Blueprint/MyProperty_Set.h`。

## 常见误用

把 setter 写成事件；或忘记属性侧 `BlueprintSetter=FuncName` 需要匹配函数签名。
