---
title: "Spacer"
id: "meta.Spacer"
kind: "meta"
symbol: "Spacer"
scope: "UMETA"
category: "Enum"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "隐藏UENUM的某个值"
usage: "UENUM::UMETA"
---

# Spacer

- **功能描述：** 隐藏UENUM的某个值
- **使用位置：** UENUM::UMETA
- **引擎模块：** Enum Property
- **元数据类型：** bool
- **限制类型：** UENUM
- **常用程度：** ★★★★★

Spacer和Hidden的功能大体是一致的。唯一区别是Spacer在蓝图里==的时候还是会显示出来。

因此还是建议如果要隐藏枚举值，还是要尽量都用Hidden。


其他示例代码见Hidden
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。
