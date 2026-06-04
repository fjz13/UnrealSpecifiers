---
title: "Constant"
id: "meta.Constant"
kind: "meta"
symbol: "Constant"
category: "RigVM"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "标识一个属性成为一个常量的引脚"
usage: "UPROPERTY, USTRUCT"
---

# Constant

- **功能描述：** 标识一个属性成为一个常量的引脚。
- **使用位置：** UPROPERTY, USTRUCT
- **引擎模块：** RigVMStruct
- **元数据类型：** bool
- **关联项：** [Input](Input.md)
- **常用程度：** ★★★

放在UPROPERTY上的时候，和Visible一样，标识一个属性成为一个常量的引脚。

放在USTRUCT上的时候，发现用在IsDefinedAsConstant这种函数上，但是F5没有发现调用的地方。

```cpp
USTRUCT(meta = (DisplayName = "Rotation Order", Category = "Math|Quaternion", Constant))
struct RIGVM_API FRigVMFunction_MathQuaternionRotationOrder : public FRigVMFunction_MathBase
{
}
```
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。
