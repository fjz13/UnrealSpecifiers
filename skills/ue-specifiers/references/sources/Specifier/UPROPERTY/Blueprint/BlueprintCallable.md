---
title: "BlueprintCallable"
id: "UPROPERTY.BlueprintCallable"
kind: "specifier"
symbol: "BlueprintCallable"
scope: "UPROPERTY"
category: "Blueprint"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "在蓝图中可以调用这个多播委托"
usage: "UPROPERTY / Blueprint"
---

# BlueprintCallable

## Decision Summary

- **Use when:** `BlueprintCallable` specifier 的 `UPROPERTY / Blueprint` 场景需要：在蓝图中可以调用这个多播委托。
- **Do not use when:** 声明宏、目标类型或代码契约不属于 `UPROPERTY / Blueprint`。
- **Requires:** specifier 必须放在 UE5.8 UHT 支持的宏和声明位置，并满足正文 caveat。
- **Conflicts:** 不要和同类互斥 specifier 或语义相反的暴露/持久化/网络规则混用。
- **Prefer instead:** 能用更窄暴露范围或更明确 metadata 表达时，优先选择更窄方案。

- **功能描述：** 在蓝图中可以调用这个多播委托

- **元数据类型：** bool
- **引擎模块：** Blueprint
- **限制类型：** Multicast Delegates
- **作用机制：** 在PropertyFlags中加入CPF_BlueprintCallable
- **常用程度：** ★★★

在蓝图中可以调用这个多播委托。

## 示例代码：

```cpp
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMyDynamicMulticastDelegate_One, int32, Value);

UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, BlueprintCallable)
	FMyDynamicMulticastDelegate_One MyMulticastDelegateAssignAndCall;

UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintCallable)
	FMyDynamicMulticastDelegate_One MyMulticastDelegateCall;

UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable)
	FMyDynamicMulticastDelegate_One MyMulticastDelegateAssign;

UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FMyDynamicMulticastDelegate_One MyMulticastDelegate;
```

## 示例效果：


注意BlueprintAssignable和BlueprintCallable只能用于多播委托：

```cpp
DECLARE_DYNAMIC_DELEGATE_OneParam(FMyDynamicSinglecastDelegate_One, int32, Value);

//编译报错：'BlueprintCallable' is only allowed on a property when it is a multicast delegate
UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintCallable)
	FMyDynamicSinglecastDelegate_One MyMyDelegate4;

	//编译报错：'BlueprintAssignable' is only allowed on a property when it is a multicast delegate
UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable)
	FMyDynamicSinglecastDelegate_One MyMyDelegate5;
```

## 行为

在 UE5.8 UHT 中写入 `CPF_BlueprintCallable`，主要用于让 Blueprint 调用 delegate 属性。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `UhtPropertyMemberSpecifiers.cs` 对应 specifier 分支

## 常见误用

用于普通字段并期待生成函数节点；或和 `BlueprintAssignable` 的绑定语义混淆。
