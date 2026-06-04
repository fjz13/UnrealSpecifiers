---
title: "CollapsableChildProperties"
id: "meta.CollapsableChildProperties"
kind: "meta"
symbol: "CollapsableChildProperties"
category: "Object"
source_status: "imported_from_unreal_specifiers"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "在TextureGraph模块中新增加的meta。用于折叠一个结构的内部属性"
usage: "UPROPERTY"
---

# CollapsableChildProperties

- **功能描述：** 在TextureGraph模块中新增加的meta。用于折叠一个结构的内部属性。
- **使用位置：** UPROPERTY
- **元数据类型：** bool
- **限制类型：** TextureGraph插件内使用
- **关联项：** [ShowInnerProperties](ShowInnerProperties/ShowInnerProperties.md)
- **常用程度：** 0

在TextureGraph模块中新增加的meta。用于折叠一个结构的内部属性。

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