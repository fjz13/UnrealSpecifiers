---
title: "AnimBlueprintFunction"
id: "meta.AnimBlueprintFunction"
kind: "meta"
symbol: "AnimBlueprintFunction"
category: "AnimationGraph"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "标明是动画蓝图里的内部纯存根函数，只在动画蓝图编译时设置"
usage: "UFUNCTION"
---

# AnimBlueprintFunction

## Decision Summary

- **Use when:** `AnimBlueprintFunction` metadata 的 `UFUNCTION` 场景需要：标明是动画蓝图里的内部纯存根函数，只在动画蓝图编译时设置。
- **Do not use when:** 目标声明不属于 `UFUNCTION`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 标明是动画蓝图里的内部纯存根函数，只在动画蓝图编译时设置
- **使用位置：** UFUNCTION
- **引擎模块：** AnimationGraph
- **元数据类型：** bool
- **限制类型：** Anim BP

只是在内部使用，在动画蓝图编译的时候设置。但是没有在代码里显式的编写。
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。
