---
title: "StructTypeConst"
id: "meta.StructTypeConst"
kind: "meta"
symbol: "StructTypeConst"
category: "TypePicker"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定FInstancedStruct属性的类型不能在编辑器被选择"
usage: "UPROPERTY"
---

# StructTypeConst

## Decision Summary

- **Use when:** `StructTypeConst` metadata 的 `UPROPERTY` 场景需要：指定FInstancedStruct属性的类型不能在编辑器被选择。
- **Do not use when:** 目标声明不属于 `UPROPERTY`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 指定FInstancedStruct属性的类型不能在编辑器被选择。
- **使用位置：** UPROPERTY
- **引擎模块：** TypePicker
- **元数据类型：** bool
- **限制类型：** FInstancedStruct
- **关联项：** [BaseStruct](BaseStruct.md)
- **常用程度：** ★

指定FInstancedStruct属性的类型不能在编辑器被选择。

用处往往是在之后交给用户在代码里初始化。
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。

## 原理：

如果有该标记，就禁用编辑的控件。

```cpp
void FInstancedStructDetails::CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
		static const FName NAME_StructTypeConst = "StructTypeConst";
		const bool bEnableStructSelection = !StructProperty->HasMetaData(NAME_StructTypeConst);


			.IsEnabled(bEnableStructSelection)

}
```
