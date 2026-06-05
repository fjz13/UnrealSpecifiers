---
title: "HideBehind"
id: "meta.HideBehind"
kind: "meta"
symbol: "HideBehind"
category: "DetailsPanel"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "只在指定的属性为true或不为空的时候本属性才显示"
usage: "UPROPERTY"
---

# HideBehind

## Decision Summary

- **Use when:** `HideBehind` metadata 的 `UPROPERTY` 场景需要：只在指定的属性为true或不为空的时候本属性才显示。
- **Do not use when:** 目标声明不属于 `UPROPERTY`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 只在指定的属性为true或不为空的时候本属性才显示
- **使用位置：** UPROPERTY
- **引擎模块：** DetailsPanel
- **元数据类型：** string="abc"
- **限制类型：** Foliage模块中
- **常用程度：** ★

```cpp
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Placement, meta=(UIMin = 0, ClampMin = 0, UIMax = 359, ClampMax = 359, HideBehind="AlignToNormal"))
	float AlignMaxAngle;
```

只在Foliage里用到，其实用EditCondition就可以达到同样的效果了。

## 行为

UE5.8 details metadata；PropertyEditor/Details customization 用于隐藏在另一个 property 后。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `ObjectMacros.h` property/class metadata declaration/comment
  - UE5.8 `PropertyEditor` Details metadata usage

## 常见误用

参数名、属性名或目标宏写错导致 metadata 被保留但没有对应编辑器/Blueprint 行为。
