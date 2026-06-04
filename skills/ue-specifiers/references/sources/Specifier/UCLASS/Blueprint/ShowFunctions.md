---
title: "ShowFunctions"
id: "UCLASS.ShowFunctions"
kind: "specifier"
symbol: "ShowFunctions"
scope: "UCLASS"
category: "Blueprint"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "在子类的函数覆盖列表里重新打开某些函数"
usage: "UCLASS / Blueprint"
---

# ShowFunctions

- **功能描述：**  在子类的函数覆盖列表里重新打开某些函数。
- **引擎模块：** Blueprint
- **元数据类型：** strings=(abc，"d|e"，"x|y|z")
- **作用机制：** 在Meta中去除[HideFunctions](../../../Meta/Blueprint/HideFunctions.md)
- **关联项：** [HideFunctions](HideFunctions.md)
- **常用程度：★★**

在子类的函数覆盖列表里重新打开某些函数。

测试代码和效果图见HideFunctions。

## 原理：

UHT中的代码，可见ShowFunctions的作用就是去除掉之前设置的HideFunctions。

```cpp
private void MergeCategories()
{
	MergeShowCategories();

	// Merge ShowFunctions and HideFunctions
	AppendStringListMetaData(SuperClass, UhtNames.HideFunctions, HideFunctions);
	foreach (string value in ShowFunctions)
	{
		HideFunctions.RemoveSwap(value);
	}
	ShowFunctions.Clear();
}
```

## 行为

UE5.8 UHT 把函数分类/名称加入 class `ShowFunctions` 列表。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `UhtClassSpecifiers.cs` class specifier branch
  - UE5.8 `UhtClass.cs` class flag/metadata resolution and validation

## 常见误用

把 class specifier 的 metadata/flag 结果和 property/function specifier 混淆；或忽略继承/撤销类 specifier 的相互作用。
