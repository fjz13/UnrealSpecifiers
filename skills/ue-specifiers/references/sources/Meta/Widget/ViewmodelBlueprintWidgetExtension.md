---
title: "ViewmodelBlueprintWidgetExtension"
id: "meta.ViewmodelBlueprintWidgetExtension"
kind: "meta"
symbol: "ViewmodelBlueprintWidgetExtension"
category: "Widget"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "用来验证InListItems的Object类型是否符合EntryWidgetClass的MVVM绑定的ViewModelProperty"
usage: "UFUNCTION"
---

# ViewmodelBlueprintWidgetExtension

## Decision Summary

- **Use when:** `ViewmodelBlueprintWidgetExtension` metadata 的 `UFUNCTION` 场景需要：用来验证InListItems的Object类型是否符合EntryWidgetClass的MVVM绑定的ViewModelProperty。
- **Do not use when:** 目标声明不属于 `UFUNCTION`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 用来验证InListItems的Object类型是否符合EntryWidgetClass的MVVM绑定的ViewModelProperty。
- **使用位置：** UFUNCTION
- **引擎模块：** Widget Property
- **元数据类型：** string="abc"
- **常用程度：** 0

用来验证InListItems的Object类型是否符合EntryWidgetClass的MVVM绑定的ViewModelProperty。

当前只在ListView里该函数使用。
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。

## 原理：

```cpp
UCLASS(meta = (EntryInterface = "/Script/UMG.UserObjectListEntry"), MinimalAPI)
class UListView : public UListViewBase, public ITypedUMGListView<UObject*>
{
	UFUNCTION(BlueprintCallable, Category = ListView, meta = (AllowPrivateAccess = true, DisplayName = "Set List Items", ViewmodelBlueprintWidgetExtension = "EntryViewModel"))
	UMG_API void BP_SetListItems(const TArray<UObject*>& InListItems);
}

void UMVVMViewBlueprintListViewBaseExtension::Precompile(UE::MVVM::Compiler::IMVVMBlueprintViewPrecompile* Compiler, UWidgetBlueprintGeneratedClass* Class)
{
}
```
