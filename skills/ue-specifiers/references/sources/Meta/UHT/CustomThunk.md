---
title: "CustomThunk"
id: "meta.CustomThunk"
kind: "meta"
symbol: "CustomThunk"
category: "UHT"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定UHT不为该函数生成蓝图调用的辅助函数，而需要用户自定义编写"
usage: "UFUNCTION"
---

# CustomThunk

- **功能描述：** 指定UHT不为该函数生成蓝图调用的辅助函数，而需要用户自定义编写。

- **使用位置：** UFUNCTION

- **引擎模块：** UHT

- **元数据类型：** bool

- **关联项：**

  UFUNCTION：[ServiceRequest](../../Specifier/UFUNCTION/Network/ServiceRequest.md), [CustomThunk](../../Specifier/UFUNCTION/UHT/CustomThunk.md)

- **常用程度：** ★★★★★
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。
