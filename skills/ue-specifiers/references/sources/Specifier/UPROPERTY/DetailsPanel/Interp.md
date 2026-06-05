---
title: "Interp"
id: "UPROPERTY.Interp"
kind: "specifier"
symbol: "Interp"
scope: "UPROPERTY"
category: "DetailsPanel"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定该属性值可暴露到时间轴里编辑，在平常的Timeline或UMG的动画里使用"
usage: "UPROPERTY / DetailsPanel"
---

# Interp

## Decision Summary

- **Use when:** `Interp` specifier 的 `UPROPERTY / DetailsPanel` 场景需要：指定该属性值可暴露到时间轴里编辑，在平常的Timeline或UMG的动画里使用。
- **Do not use when:** 声明宏、目标类型或代码契约不属于 `UPROPERTY / DetailsPanel`。
- **Requires:** specifier 必须放在 UE5.8 UHT 支持的宏和声明位置，并满足正文 caveat。
- **Conflicts:** 不要和同类互斥 specifier 或语义相反的暴露/持久化/网络规则混用。
- **Prefer instead:** 能用更窄暴露范围或更明确 metadata 表达时，优先选择更窄方案。

- **功能描述：** 指定该属性值可暴露到时间轴里编辑，在平常的Timeline或UMG的动画里使用。

- **元数据类型：** bool
- **引擎模块：** Sequencer
- **作用机制：** 在PropertyFlags中加入CPF_Edit, CPF_BlueprintVisible, CPF_Interp
- **常用程度：** ★★★

该属性可以暴露到时间轴里，一般用来编辑动画。

## 示例代码：

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyProperty_Interp :public AActor
{
public:
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = Animation)
		FVector MyInterpVector;
};
```

## 示例效果：

影响的是属性上的该标志


从而可以在Sequencer里对该属性添加Track


## 行为

在 UE5.8 UHT 中写入 `CPF_Edit | CPF_BlueprintVisible | CPF_Interp`，用于可插值/可关键帧编辑的属性暴露。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `UhtPropertyMemberSpecifiers.cs` 对应 specifier 分支

## 常见误用

以为它自动复制或自动驱动动画；它只是属性标志和编辑器暴露基础。
