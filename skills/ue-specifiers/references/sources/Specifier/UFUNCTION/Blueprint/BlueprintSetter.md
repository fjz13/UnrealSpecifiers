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
