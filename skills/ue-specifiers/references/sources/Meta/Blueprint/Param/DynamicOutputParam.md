---
title: "DynamicOutputParam"
id: "meta.DynamicOutputParam"
kind: "meta"
symbol: "DynamicOutputParam"
category: "Blueprint"
source_status: "imported_from_unreal_specifiers"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "配合DeterminesOutputType，指定多个支持动态类型的输出参数"
usage: "UFUNCTION"
---

# DynamicOutputParam

- **功能描述：** 配合DeterminesOutputType，指定多个支持动态类型的输出参数。
- **使用位置：** UFUNCTION
- **元数据类型：** strings="a，b，c"
- **限制类型：** Class或Object指针类型，或容器类型
- **关联项：** [DeterminesOutputType](DeterminesOutputType/DeterminesOutputType.md)

常常和DeterminesOutputType一起配合。动态参数的数量可以为多个。