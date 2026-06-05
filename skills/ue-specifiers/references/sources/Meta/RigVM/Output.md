---
title: "Output"
id: "meta.Output"
kind: "meta"
symbol: "Output"
category: "RigVM"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定FRigUnit下的该属性作为输出引脚"
usage: "UPROPERTY"
---

# Output

## Decision Summary

- **Use when:** RigVM/RigUnit 字段需要标记为输出 pin。
- **Do not use when:** 字段不是 RigVM 暴露参数，或属于普通 UE 反射属性。
- **Requires:** 目标类型和模块应处在 RigVM/Control Rig 工作流中。
- **Conflicts:** 不适用于普通 Blueprint 函数参数方向。
- **Prefer instead:** 普通 UFUNCTION 输出用返回值或非 const 引用参数。

- **功能描述：** 指定FRigUnit下的该属性作为输出引脚。
- **使用位置：** UPROPERTY
- **引擎模块：** RigVMStruct
- **元数据类型：** bool
- **限制类型：** FRigUnit中属性
- **关联项：** [Input](Input.md)
- **常用程度：** ★★★★★

指定FRigUnit下的该属性作为输出引脚。
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。
