---
title: "Interface"
id: "UCLASS.Interface"
kind: "specifier"
symbol: "Interface"
scope: "UCLASS"
category: "UHT"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "标识这个Class是个Interface"
usage: "UCLASS / UHT"
---

# Interface

## Decision Summary

- **Use when:** `Interface` specifier 的 `UCLASS / UHT` 场景需要：标识这个Class是个Interface。
- **Do not use when:** 声明宏、目标类型或代码契约不属于 `UCLASS / UHT`。
- **Requires:** specifier 必须放在 UE5.8 UHT 支持的宏和声明位置，并满足正文 caveat。
- **Conflicts:** 不要和同类互斥 specifier 或语义相反的暴露/持久化/网络规则混用。
- **Prefer instead:** 能用更窄暴露范围或更明确 metadata 表达时，优先选择更窄方案。

- **功能描述：** 标识这个Class是个Interface。
- **引擎模块：** UHT
- **元数据类型：** bool
- **作用机制：** 在ClassFlags中添加CLASS_Interface
- **常用程度：** 0

标识这个Class是个Interface。

只用在NoExportTypes.h中，我们自己的UInterface不需要手动设置。

是UHT在为UInterface生成的时候，设置在.generated.h里的。
## UE5.8 审计结论

UE5.8 UHT 或宏路径仍保留该条目；本轮按 UE5.8 标记为已验证。P3 中不少条目属于引擎内部、NoExportTypes 或插件专用用法，不建议普通项目代码直接套用。

## 源码例子：

```cpp
UCLASS(abstract, noexport, intrinsic, interface, Config = Engine)
class UInterface : public UObject
{}
```

## 原理：

```cpp
bool FKismetEditorUtilities::IsClassABlueprintInterface(const UClass* Class)
{
	if (Class->HasAnyClassFlags(CLASS_Interface) && !Class->HasAnyClassFlags(CLASS_NewerVersionExists))
	{
		return true;
	}
	return false;
}
```
