---
title: "BindWidgetAnimOptional"
id: "meta.BindWidgetAnimOptional"
kind: "meta"
symbol: "BindWidgetAnimOptional"
category: "Widget"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定在C++类中该UWidgetAnimation属性可以要绑定到UMG下的某个动画，也可以不绑定"
usage: "UPROPERTY"
---

# BindWidgetAnimOptional

- **功能描述：** 指定在C++类中该UWidgetAnimation属性可以要绑定到UMG下的某个动画，也可以不绑定。
- **使用位置：** UPROPERTY
- **引擎模块：** Widget Property
- **元数据类型：** bool
- **限制类型：** UWidget子类里UWidgetAnimation属性
- **关联项：** [BindWidgetAnim](BindWidgetAnim.md)
- **常用程度：** ★★★

同BindWidgetOptional作用也类似，在不绑定的时候在编译结果里会有一个提示，而不是像BindWidget一样强制的错误。


自然的也说过不能像Widget一样，不加BindWidget就自动默认绑定。

因此用法上要嘛加BindWidgetAnim，要嘛加BindWidgetAnimOptional。
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。
