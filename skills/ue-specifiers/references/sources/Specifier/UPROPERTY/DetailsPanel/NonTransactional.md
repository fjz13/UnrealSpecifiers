---
title: "NonTransactional"
id: "UPROPERTY.NonTransactional"
kind: "specifier"
symbol: "NonTransactional"
scope: "UPROPERTY"
category: "DetailsPanel"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "对该属性的改变操作，不会被包含进编辑器的Undo/Redo命令中"
usage: "UPROPERTY / DetailsPanel"
---

# NonTransactional

## Decision Summary

- **Use when:** `NonTransactional` specifier 的 `UPROPERTY / DetailsPanel` 场景需要：对该属性的改变操作，不会被包含进编辑器的Undo/Redo命令中。
- **Do not use when:** 声明宏、目标类型或代码契约不属于 `UPROPERTY / DetailsPanel`。
- **Requires:** specifier 必须放在 UE5.8 UHT 支持的宏和声明位置，并满足正文 caveat。
- **Conflicts:** 不要和同类互斥 specifier 或语义相反的暴露/持久化/网络规则混用。
- **Prefer instead:** 能用更窄暴露范围或更明确 metadata 表达时，优先选择更窄方案。

- **功能描述：** 对该属性的改变操作，不会被包含进编辑器的Undo/Redo命令中。

- **元数据类型：** bool
- **引擎模块：** Editor
- **作用机制：** 在PropertyFlags中加入CPF_NonTransactional
- **常用程度：** ★★

指定该属性的改变，不能在编辑器中通过Ctrl+Z来撤销或Ctrl+Y来重做。在Actor或在BP的Class Defautls都可以生效。

## 测试代码：

```jsx
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyProperty_Transaction :public AActor
{
public:
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,NonTransactional,Category = Transaction)
		int32 MyInt_NonTransactional= 123;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = Transaction)
		int32 MyInt_Transactional = 123;
};
```

## 蓝图表现：

在MyInt_Transactional 上可以撤销之前的输入，而MyInt_NonTransactional上的输入无法用Ctrl+Z撤销。


## 行为

在 UE5.8 UHT 中写入 `CPF_NonTransactional`，用于让属性变更不进入编辑器事务/undo 路径。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `UhtPropertyMemberSpecifiers.cs` 对应 specifier 分支

## 常见误用

把它当成序列化开关；或用于需要撤销记录的编辑器数据。
