# Recipes Index

> 场景 recipe 是给 AI 做开发决策用的短指南，不替代 `references/indexes/` 或原始 `references/sources` 文档。

| Recipe | 适用场景 | 高频相关项 | 状态 |
|---|---|---|---|
| `recipes/property-details-panel.md` | 属性需要在 Details Panel 可编辑或只读展示 | `EditAnywhere`, `EditDefaultsOnly`, `VisibleAnywhere`, `Category` | `verified_UE5.8` |
| `recipes/property-blueprint-exposure.md` | 属性需要 Blueprint 读写或只读访问 | `BlueprintReadOnly`, `BlueprintReadWrite`, `EditAnywhere`, `Category` | `verified_UE5.8` |
| `recipes/blueprint-function-node.md` | C++ 函数暴露为 Blueprint 节点 | `BlueprintCallable`, `BlueprintPure`, `Category`, `DisplayName` | `verified_UE5.8` |
| `recipes/replicated-property.md` | 属性需要网络复制或复制通知 | `Replicated`, `ReplicatedUsing`, `OnRep_` | `verified_UE5.8` |
| `recipes/savegame-property.md` | 属性需要进入 SaveGame 持久化 | `SaveGame`, `Transient` | `verified_UE5.8` |
| `recipes/config-property.md` | 属性需要从 ini config 读取 | `Config`, `GlobalConfig`, `UCLASS(Config=...)` | `imported_from_unreal_specifiers` |
| `recipes/instanced-subobject.md` | UObject 子对象需要内联实例化编辑 | `Instanced`, `EditInlineNew`, `DefaultToInstanced` | `verified_UE5.8` |
| `recipes/edit-condition.md` | Details Panel 属性受条件控制 | `EditCondition`, `EditConditionHides`, `InlineEditConditionToggle` | `verified_UE5.8` |
| `recipes/call-in-editor.md` | 在编辑器 Details Panel 调用函数 | `CallInEditor`, `BlueprintCallable` | `imported_from_unreal_specifiers` |
| `recipes/world-context.md` | Blueprint 函数库需要 World 上下文 | `WorldContext`, `DefaultToSelf`, `HidePin` | `verified_UE5.8` |
