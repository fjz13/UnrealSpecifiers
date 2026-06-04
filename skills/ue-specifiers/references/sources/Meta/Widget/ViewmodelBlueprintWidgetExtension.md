---
title: "ViewmodelBlueprintWidgetExtension"
id: "meta.ViewmodelBlueprintWidgetExtension"
kind: "meta"
symbol: "ViewmodelBlueprintWidgetExtension"
category: "Widget"
source_status: "imported_from_unreal_specifiers"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "用来验证InListItems的Object类型是否符合EntryWidgetClass的MVVM绑定的ViewModelProperty"
usage: "UFUNCTION"
---

# ViewmodelBlueprintWidgetExtension

- **功能描述：** 用来验证InListItems的Object类型是否符合EntryWidgetClass的MVVM绑定的ViewModelProperty。
- **使用位置：** UFUNCTION
- **引擎模块：** Widget Property
- **元数据类型：** string="abc"
- **常用程度：** 0

用来验证InListItems的Object类型是否符合EntryWidgetClass的MVVM绑定的ViewModelProperty。

当前只在ListView里该函数使用。

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