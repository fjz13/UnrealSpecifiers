---
title: "Varying"
id: "meta.Varying"
kind: "meta"
symbol: "Varying"
category: "RigVM"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "ScriptStruct /Script/RigVM.RigVMFunction_GetDeltaTime"
usage: "UCLASS"
---

# Varying

- **功能描述：** ScriptStruct /Script/RigVM.RigVMFunction_GetDeltaTime
- **使用位置：** UCLASS
- **引擎模块：** RigVMStruct
- **元数据类型：** bool
- **常用程度：** 0

放在USTRUCT上的时候，发现用在IsDefinedAsVarying这种函数上，但是F5没有发现调用的地方。
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。
