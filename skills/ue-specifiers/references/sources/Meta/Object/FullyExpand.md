---
title: "FullyExpand"
id: "meta.FullyExpand"
kind: "meta"
symbol: "FullyExpand"
category: "Object"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "但是没有发现该Meta被使用的原理代码"
usage: "UPROPERTY"
---

# FullyExpand

## Decision Summary

- **Use when:** `FullyExpand` metadata 的 `UPROPERTY` 场景需要：但是没有发现该Meta被使用的原理代码。
- **Do not use when:** 目标声明不属于 `UPROPERTY`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **使用位置：** UPROPERTY
- **元数据类型：** bool
- **关联项：** [ShowInnerProperties](ShowInnerProperties.md)

但是没有发现该Meta被使用的原理代码。

在源码中搜索发现有多处应用，但实际上没有原理代码。

```cpp
	/** The options that are available on the node. */
	UPROPERTY(EditAnywhere, Instanced, Category = "Options", meta=(ShowInnerProperties, FullyExpand="true"))
	TObjectPtr<UMovieGraphValueContainer> SelectOptions;

	/** The currently selected option. */
	UPROPERTY(EditAnywhere, Instanced, Category = "Options", meta=(ShowInnerProperties, FullyExpand="true"))
	TObjectPtr<UMovieGraphValueContainer> SelectedOption;
```
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。
