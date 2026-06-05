---
title: "HasNativeMake"
id: "meta.HasNativeMake"
kind: "meta"
symbol: "HasNativeMake"
scope: "HasNativeMake"
category: "Struct"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "为该结构指定一个C++内的UFunction函数作为Mreak节点的实现"
usage: "USTRUCT"
---

# HasNativeMake

## Decision Summary

- **Use when:** 结构体在 Blueprint 中需要使用指定 C++ 函数作为 Make 节点。
- **Do not use when:** 默认自动生成的 Make 节点已经满足需求。
- **Requires:** 指定函数签名与 Blueprint Make struct 语义匹配。
- **Conflicts:** 不改变结构体构造或序列化规则。
- **Prefer instead:** 简单 USTRUCT 使用默认 Make/Break 节点。

- **功能描述：** 为该结构指定一个C++内的UFunction函数作为Mreak节点的实现
- **使用位置：** USTRUCT
- **元数据类型：** string="abc"
- **关联项：** [HasNativeBreak](HasNativeBreak.md)
- **常用程度：** ★★★★★
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。
