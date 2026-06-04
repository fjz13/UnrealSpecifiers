---
title: "DeprecationMessage"
id: "meta.DeprecationMessage"
kind: "meta"
symbol: "DeprecationMessage"
category: "Development"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "定义弃用的消息"
usage: "UCLASS, UFUNCTION, UPROPERTY"
---

# DeprecationMessage

- **功能描述：** 定义弃用的消息

- **使用位置：** UCLASS, UFUNCTION, UPROPERTY

- **引擎模块：** Development

- **元数据类型：** string="abc"

- **关联项：**

  UCLASS：[Deprecated](../../Specifier/UCLASS/Development/Deprecated/Deprecated.md)

- **常用程度：** ★

## 例子：

```cpp
UFUNCTION(meta=(DeprecatedFunction,DeprecationMessage="This function is deprecated, please use OtherFunctionName instead."))
ReturnType FunctionName([Parameter, Parameter, ...])

UPROPERTY(BlueprintReadWrite, meta=(DeprecatedProperty, DeprecationMessage="This is deprecated"))
FString PlantName;
```
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。
