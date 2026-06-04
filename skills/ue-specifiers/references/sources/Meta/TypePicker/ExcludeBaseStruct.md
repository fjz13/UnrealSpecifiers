---
title: "ExcludeBaseStruct"
id: "meta.ExcludeBaseStruct"
kind: "meta"
symbol: "ExcludeBaseStruct"
category: "TypePicker"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "在使用BaseStruct的FInstancedStruct属性上忽略BaseStruct指向的结构基类"
usage: "UPROPERTY"
---

# ExcludeBaseStruct

- **功能描述：** 在使用BaseStruct的FInstancedStruct属性上忽略BaseStruct指向的结构基类。
- **使用位置：** UPROPERTY
- **引擎模块：** TypePicker
- **元数据类型：** bool
- **限制类型：** FInstancedStruct
- **关联项：** [BaseStruct](BaseStruct.md)
- **常用程度：** ★★★

在使用BaseStruct的FInstancedStruct属性上忽略BaseStruct指向的结构基类。
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。
