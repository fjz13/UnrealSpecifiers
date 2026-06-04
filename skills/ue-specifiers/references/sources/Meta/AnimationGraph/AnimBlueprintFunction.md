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

- **功能描述：** 标明是动画蓝图里的内部纯存根函数，只在动画蓝图编译时设置
- **使用位置：** UFUNCTION
- **引擎模块：** AnimationGraph
- **元数据类型：** bool
- **限制类型：** Anim BP

只是在内部使用，在动画蓝图编译的时候设置。但是没有在代码里显式的编写。
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。
