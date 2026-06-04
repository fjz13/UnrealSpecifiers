---
title: "NotReplicated"
id: "UPROPERTY.NotReplicated"
kind: "specifier"
symbol: "NotReplicated"
scope: "UPROPERTY"
category: "Network"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "跳过复制。这只会应用到服务请求函数中的结构体成员和参数"
usage: "UPROPERTY / Network"
---

# NotReplicated

- **功能描述：** 跳过复制。这只会应用到服务请求函数中的结构体成员和参数。

- **元数据类型：** bool
- **引擎模块：** Network
- **限制类型：** Struct members
- **作用机制：** 在PropertyFlags中加入[CPF_RepSkip](../../../Flags/EPropertyFlags/CPF_RepSkip.md)
- **常用程度：** ★★★

只用在结构成员中，指定struct中的某个属性不复制，否则默认就都会复制。这个用于排除掉结构中的某属性。

## 示例代码：

```cpp
USTRUCT(BlueprintType)
struct FMyReplicatedStruct
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString MyString_Default;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,NotReplicated)
		FString MyString_NotReplicated;
};

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyProperty_Network :public AActor
{
public:
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
		FMyReplicatedStruct MyStruct_Replicated;
};
```

其中MyStruct_Replicated会复制，但是其中的MyString_NotReplicated不会复制。

## 行为

在 UE5.8 UHT 中，property member 版本只允许 USTRUCT 成员并写入 `CPF_RepSkip`；参数版本只允许 service request replicated parameter 并改为 regular parameter。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `UhtPropertyMemberSpecifiers.cs` 对应 specifier 分支
  - UE5.8 `UhtPropertyArgumentSpecifiers.cs` service request parameter 分支
- 批次记录：`references/audits/ue5.8-p0-complete-pass.md`。

## 常见误用

在普通 UCLASS replicated 属性上使用；或以为它能替代 `DOREPLIFETIME` 配置。
