---
title: "CollapsableChildProperties"
id: "meta.CollapsableChildProperties"
kind: "meta"
symbol: "CollapsableChildProperties"
category: "Object"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "在TextureGraph模块中新增加的meta。用于折叠一个结构的内部属性"
usage: "UPROPERTY"
---

# CollapsableChildProperties

## Decision Summary

- **Use when:** `CollapsableChildProperties` metadata 的 `UPROPERTY` 场景需要：在TextureGraph模块中新增加的meta。用于折叠一个结构的内部属性。
- **Do not use when:** 目标声明不属于 `UPROPERTY`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 在TextureGraph模块中新增加的meta。用于折叠一个结构的内部属性。
- **使用位置：** UPROPERTY
- **元数据类型：** bool
- **限制类型：** TextureGraph插件内使用
- **关联项：** [ShowInnerProperties](ShowInnerProperties.md)
- **常用程度：** 0

在TextureGraph模块中新增加的meta。用于折叠一个结构的内部属性。
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。

## 源码：

```cpp
bool STG_GraphPinOutputSettings::CollapsibleChildProperties() const
{
	FProperty* Property = GetPinProperty();
	bool Collapsible = false;
	// check if there is a display name defined for the property, we use that as the Pin Name
	if (Property && Property->HasMetaData("CollapsableChildProperties"))
	{
		Collapsible = true;
	}
	return Collapsible;
}

	UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Input", CollapsableChildProperties,ShowOnlyInnerProperties, FullyExpand, NoResetToDefault, PinDisplayName = "Settings") )
	FTG_OutputSettings OutputSettings;
```
