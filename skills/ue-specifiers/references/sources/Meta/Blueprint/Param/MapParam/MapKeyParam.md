---
title: "MapKeyParam"
id: "meta.MapKeyParam"
kind: "meta"
symbol: "MapKeyParam"
category: "Blueprint"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定一个函数参数为Map的Key，其根据MapParam指定的实际Map参数的Key类型而相应改变"
usage: "UFUNCTION"
---

# MapKeyParam

- **功能描述：** 指定一个函数参数为Map的Key，其根据MapParam指定的实际Map参数的Key类型而相应改变。
- **使用位置：** UFUNCTION
- **元数据类型：** string="abc"
- **限制类型：** TMap
- **关联项：** [MapParam](MapParam.md)
- **常用程度：** ★★★

## 行为

UE5.8 function/interface metadata；TMap key wildcard type 参数。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `ObjectMacros.h` metadata declaration/comment
  - UE5.8 `BlueprintGraph` metadata constants or node usage

## 常见误用

参数名、属性名或目标宏写错导致 metadata 被保留但没有对应编辑器/Blueprint 行为。
