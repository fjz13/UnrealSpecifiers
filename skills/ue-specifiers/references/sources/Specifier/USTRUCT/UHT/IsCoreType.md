---
title: "IsCoreType"
id: "USTRUCT.IsCoreType"
kind: "specifier"
symbol: "IsCoreType"
scope: "USTRUCT"
category: "UHT"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定该结构是核心类，UHT在用它的时候不需要前向声明"
usage: "USTRUCT / UHT"
---

# IsCoreType

- **功能描述：** 指定该结构是核心类，UHT在用它的时候不需要前向声明。
- **元数据类型：** bool
- **引擎模块：** UHT
- **限制类型：** 只在NoExportTypes.h供UHT使用
- **常用程度：** 0

指定该结构是核心类，UHT在用它的时候不需要前向声明。
## UE5.8 审计结论

UE5.8 UHT 或宏路径仍保留该条目；本轮按 UE5.8 标记为已验证。P3 中不少条目属于引擎内部、NoExportTypes 或插件专用用法，不建议普通项目代码直接套用。

## 原理：

看UHT源码是把struct用在参数或属性等被引用的时候。

```cpp
public override string? UhtStructProperty::GetForwardDeclarations()
		{
			if (ScriptStruct.IsCoreType)
			{
				return null;
			}

			if (TemplateWrapper != null)
			{
				StringBuilder builder = new();
				TemplateWrapper.AppendForwardDeclarations(builder);
				return builder.ToString();
			}

			return $"struct {ScriptStruct.SourceName};";
		}
```