---
title: "BlueprintGetter"
id: "UFUNCTION.BlueprintGetter"
kind: "specifier"
symbol: "BlueprintGetter"
scope: "UFUNCTION"
category: "Blueprint"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定该函数作为属性的自定义Get函数"
usage: "UFUNCTION / Blueprint"
---

# BlueprintGetter

- **功能描述：** 指定该函数作为属性的自定义Get函数。

- **元数据类型：** bool
- **引擎模块：** Blueprint
- **作用机制：** 在Meta中加入[BlueprintGetter](../../../Meta/Blueprint/BlueprintGetter.md)，在FunctionFlags加入FUNC_BlueprintCallable、FUNC_BlueprintPure
- **常用程度：** ★★

指定该函数作为属性的自定义Get函数。

此说明符隐含BlueprintPure和BlueprintCallable。

更多可以参考UPROPERTY的BlueprintGetter

## 行为

在 UE5.8 UHT 中设置 accessor export flag，并同时写入 `BlueprintCallable`、`BlueprintPure` 和 `BlueprintGetter` metadata。UHT 拒绝把 Blueprint event 同时作为 getter。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `UhtFunctionSpecifiers.cs` 对应 specifier 分支
  - UE5.8 `UhtFunction.cs` replicated/event 校验
  - 本地样例辅助对照：`D:/github/GitWorkspace/Hello/Source/Insider/Property/Blueprint/MyProperty_Get.h`。

## 常见误用

把 getter 写成事件；或忘记它通常要和属性侧 `BlueprintGetter=FuncName` 配合。
