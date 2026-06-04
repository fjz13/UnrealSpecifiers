---
title: "RepRetry"
id: "UPROPERTY.RepRetry"
kind: "specifier"
symbol: "RepRetry"
scope: "UPROPERTY"
category: "Network"
source_status: "imported_from_unreal_specifiers"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "只适用于结构体属性。如果此属性未能完全发送（举例而言：Object引用尚无法通过网络进行序列化），则重新尝试对其的复制。对简单引用而言，这是默认选择；但对结构体而言，这会产生带宽开销，并非优选项。因此在指定此标签之前其均为禁用状态"
usage: "UPROPERTY / Network"
---

# RepRetry

- **功能描述：** 只适用于结构体属性。如果此属性未能完全发送（举例而言：Object引用尚无法通过网络进行序列化），则重新尝试对其的复制。对简单引用而言，这是默认选择；但对结构体而言，这会产生带宽开销，并非优选项。因此在指定此标签之前其均为禁用状态。
- **元数据类型：** bool
- **引擎模块：** Network