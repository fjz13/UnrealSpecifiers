---
title: "HasDefaults"
id: "USTRUCT.HasDefaults"
kind: "specifier"
symbol: "HasDefaults"
scope: "USTRUCT"
category: "UHT"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定该结构的字段拥有默认值。这样如果本结构作为函数参数或返回值时候，函数则可以为其提供默认值"
usage: "USTRUCT / UHT"
---

# HasDefaults

## Decision Summary

- **Use when:** `HasDefaults` specifier 的 `USTRUCT / UHT` 场景需要：指定该结构的字段拥有默认值。这样如果本结构作为函数参数或返回值时候，函数则可以为其提供默认值。
- **Do not use when:** 声明宏、目标类型或代码契约不属于 `USTRUCT / UHT`。
- **Requires:** specifier 必须放在 UE5.8 UHT 支持的宏和声明位置，并满足正文 caveat。
- **Conflicts:** 不要和同类互斥 specifier 或语义相反的暴露/持久化/网络规则混用。
- **Prefer instead:** 能用更窄暴露范围或更明确 metadata 表达时，优先选择更窄方案。

- **功能描述：** 指定该结构的字段拥有默认值。这样如果本结构作为函数参数或返回值时候，函数则可以为其提供默认值。
- **元数据类型：** bool
- **引擎模块：** UHT
- **限制类型：** 只在NoExportTypes.h供UHT使用
- **作用机制：** 在FunctionFlags中加入FUNC_HasDefaults
- **常用程度：** 0

指定该结构的字段拥有默认值。

不是指的是NoExportTypes.h的声明上是否写有默认值，而是指其真正的声明之处，其内部的属性都有初始值。这样如果本结构作为函数参数或返回值时候，函数则可以为其提供默认值。

NoExportTypes.h里的大部分结构都拥有该结构（88/135)，没有的是像FPackedXXX的。
## UE5.8 审计结论

UE5.8 UHT 或宏路径仍保留该条目；本轮按 UE5.8 标记为已验证。P3 中不少条目属于引擎内部、NoExportTypes 或插件专用用法，不建议普通项目代码直接套用。

## 原理：

如果是一个class中的函数且参数用到了结构，如果该结构拥有HasDefaults，则会造成EFunctionFlags.HasDefaults

```cpp
// The following code is only performed on functions in a class.
if (Outer is UhtClass)
{
	foreach (UhtType type in Children)
	{
		if (type is UhtProperty property)
		{
			if (property.PropertyFlags.HasExactFlags(EPropertyFlags.OutParm | EPropertyFlags.ReturnParm, EPropertyFlags.OutParm))
			{
				FunctionFlags |= EFunctionFlags.HasOutParms;
			}
			if (property is UhtStructProperty structProperty)
			{
				if (structProperty.ScriptStruct.HasDefaults)
				{
					FunctionFlags |= EFunctionFlags.HasDefaults;
				}
			}
		}
	}
}
```
