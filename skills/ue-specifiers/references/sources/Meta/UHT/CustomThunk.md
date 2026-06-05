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

## Decision Summary

- **Use when:** UHT 生成的默认 Blueprint 调用 thunk 不够用，必须手写参数解析/调用桥接。
- **Do not use when:** 普通 UFUNCTION 暴露已经能表达函数签名。
- **Requires:** 手写 `DECLARE_FUNCTION(exec...)` thunk 实现和完整测试；通常是高级引擎/插件场景。
- **Conflicts:** 不要作为解决普通 Blueprint 类型问题的快捷方式。
- **Prefer instead:** 固定签名、常规反射类型和普通 `BlueprintCallable`。

- **功能描述：** 指定UHT不为该函数生成蓝图调用的辅助函数，而需要用户自定义编写。

- **使用位置：** UFUNCTION

- **引擎模块：** UHT

- **元数据类型：** bool

- **关联项：**

  UFUNCTION：[ServiceRequest](../../Specifier/UFUNCTION/Network/ServiceRequest.md), [CustomThunk](../../Specifier/UFUNCTION/UHT/CustomThunk.md)

- **常用程度：** ★★★★★
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。
