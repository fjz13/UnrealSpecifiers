---
title: "BlueprintSetter"
id: "UFUNCTION.BlueprintSetter"
kind: "specifier"
symbol: "BlueprintSetter"
scope: "UFUNCTION"
category: "Blueprint"
source_status: "imported_from_unreal_specifiers"
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
- **作用机制：** 在Meta中加入[BlueprintSetter](../../../Meta/Blueprint/BlueprintSetter.md)，在FunctionFlags中加入[FUNC_BlueprintCallable ](../../../Flags/EFunctionFlags/FUNC_BlueprintCallable.md)
- **常用程度：** ★★

指定该函数作为属性的自定义Set函数。

此说明符隐含BlueprintCallable。

更多可以参考UPROPERTY的BlueprintSetter