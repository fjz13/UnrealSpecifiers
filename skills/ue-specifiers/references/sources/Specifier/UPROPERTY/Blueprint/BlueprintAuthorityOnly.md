---
title: "BlueprintAuthorityOnly"
id: "UPROPERTY.BlueprintAuthorityOnly"
kind: "specifier"
symbol: "BlueprintAuthorityOnly"
scope: "UPROPERTY"
category: "Blueprint"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "只能绑定为BlueprintAuthorityOnly的事件，让该多播委托只接受在服务端运行的事件"
usage: "UPROPERTY / Blueprint"
---

# BlueprintAuthorityOnly

## Decision Summary

- **Use when:** `BlueprintAuthorityOnly` specifier 的 `UPROPERTY / Blueprint` 场景需要：只能绑定为BlueprintAuthorityOnly的事件，让该多播委托只接受在服务端运行的事件。
- **Do not use when:** 声明宏、目标类型或代码契约不属于 `UPROPERTY / Blueprint`。
- **Requires:** specifier 必须放在 UE5.8 UHT 支持的宏和声明位置，并满足正文 caveat。
- **Conflicts:** 不要和同类互斥 specifier 或语义相反的暴露/持久化/网络规则混用。
- **Prefer instead:** 能用更窄暴露范围或更明确 metadata 表达时，优先选择更窄方案。

- **功能描述：** 只能绑定为BlueprintAuthorityOnly的事件，让该多播委托只接受在服务端运行的事件

- **元数据类型：** bool
- **引擎模块：** Blueprint, Network
- **限制类型：** Multicast Delegates
- **作用机制：** 在PropertyFlags中加入CPF_BlueprintAuthorityOnly
- **常用程度：** ★★★

## 测试代码：

```cpp
UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, BlueprintCallable)
		FMyDynamicMulticastDelegate_One MyMulticastDelegateAssignAndCall;

UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, BlueprintCallable, BlueprintAuthorityOnly)
		FMyDynamicMulticastDelegate_One MyMulticastDelegateAuthorityOnly;
```

## 蓝图中表现：


## 行为

在 UE5.8 UHT 中写入 `CPF_BlueprintAuthorityOnly`，用于 Blueprint 暴露属性的 authority-only 语义，常见于 delegate 属性。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `UhtPropertyMemberSpecifiers.cs` 对应 specifier 分支

## 常见误用

把它当成 property replication 或 RPC；或忽略运行时 authority 设计。
