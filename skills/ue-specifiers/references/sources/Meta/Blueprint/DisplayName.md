---
title: "DisplayName"
id: "meta.Blueprint.DisplayName"
kind: "meta"
symbol: "DisplayName"
category: "Blueprint"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "此节点在蓝图中的命名将被此处提供的值所取代，而非代码生成的命名"
usage: "UCLASS, UENUM::UMETA, UFUNCTION, UPARAM, UPROPERTY"
---

# DisplayName

## Decision Summary

- **Use when:** Blueprint/editor 展示名需要比 C++ 标识符更友好。
- **Do not use when:** 只是想重命名 C++ API 或隐藏不清晰命名。
- **Requires:** 保持展示名稳定，避免破坏用户查找和教程一致性。
- **Conflicts:** 不改变真实 C++ 名称、序列化名或调用签名。
- **Prefer instead:** 新 API 优先使用清晰 C++ 命名，只在展示确有必要时加 display name。

- **功能描述：** 此节点在蓝图中的命名将被此处提供的值所取代，而非代码生成的命名。

- **使用位置：** UCLASS, UENUM::UMETA, UFUNCTION, UPARAM, UPROPERTY

- **引擎模块：** Blueprint

- **元数据类型：** string="abc"

- **关联项：**

  UPARAM：[DisplayName](../../Specifier/UPARAM/Blueprint/DisplayName.md)

- **常用程度：** ★★★★★

## 行为

UE5.8 UHT 默认 specifier 会把 `DisplayName` 写入 metadata；`GetDisplayNameText` 优先返回该值，否则回退 source name。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `UhtDefaultSpecifiers.cs` `DisplayName` metadata writer
  - UE5.8 `UhtType.cs` display name lookup

## 常见误用

以为它改 C++ 符号名；或在需要稳定 API 名称的地方只看显示名。
