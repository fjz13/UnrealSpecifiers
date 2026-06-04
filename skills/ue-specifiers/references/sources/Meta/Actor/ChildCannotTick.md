---
title: "ChildCannotTick"
id: "meta.ChildCannotTick"
kind: "meta"
symbol: "ChildCannotTick"
category: "Actor"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "用于Actor或ActorComponent子类，标记允许其蓝图子类不可以接受响应Tick事件，哪怕父类可以Tick"
usage: "UCLASS"
---

# ChildCannotTick

- **功能描述：** 用于Actor或ActorComponent子类，标记允许其蓝图子类不可以接受响应Tick事件，哪怕父类可以Tick
- **使用位置：** UCLASS
- **元数据类型：** bool
- **限制类型：** Actor类
- **关联项：** [ChildCanTick](ChildCanTick.md)
- **常用程度：** ★★★
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。
