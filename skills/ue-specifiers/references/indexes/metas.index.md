# Metas Index

> 该文件是给 AI 快速检索用的摘要索引，不替代原始 `references/sources` 文档。状态为 `imported_from_unreal_specifiers` 的条目只表示已从本仓库文档导入，尚未按目标 UE 版本重新验证。
> 完整 source 路由索引见 `references/indexes/sources.index.md`。

## Details Panel

| ID | Macro | 摘要 | 使用场景 | 相关项 | 状态 | source_doc |
|---|---|---|---|---|---|---|
| `meta.EditCondition` | `UPROPERTY` | 条件控制属性是否可编辑 | bool 或表达式条件控制另一个属性 | `EditConditionHides`, `InlineEditConditionToggle` | `verified_UE5.8` | `references/sources/Meta/DetailsPanel/EditCondition/EditCondition.md` |
| `meta.EditConditionHides` | `UPROPERTY` | 条件不满足时隐藏属性 | 希望隐藏而不是禁用 | `EditCondition` | `imported_from_unreal_specifiers` | `references/sources/Meta/DetailsPanel/EditConditionHides/EditConditionHides.md` |
| `meta.InlineEditConditionToggle` | `UPROPERTY` | 将 bool 条件作为内联开关显示 | 条件开关和被控制属性需要紧凑展示 | `EditCondition`, `HideEditConditionToggle` | `imported_from_unreal_specifiers` | `references/sources/Meta/DetailsPanel/InlineEditConditionToggle/InlineEditConditionToggle.md` |

## Blueprint Nodes And Parameters

| ID | Macro | 摘要 | 使用场景 | 相关项 | 状态 | source_doc |
|---|---|---|---|---|---|---|
| `meta.DisplayName` | `UCLASS`, `UFUNCTION`, `UPROPERTY`, `UMETA` | 设置编辑器或 Blueprint 显示名称 | 对用户展示友好名称 | `ToolTip`, `ShortToolTip` | `imported_from_unreal_specifiers` | `references/sources/Meta/Blueprint/DisplayName.md` |
| `meta.AllowPrivateAccess` | `UPROPERTY` | 允许 Blueprint 访问 private 属性 | C++ private 成员仍需 Blueprint 暴露 | `BlueprintReadOnly`, `BlueprintReadWrite` | `imported_from_unreal_specifiers` | `references/sources/Meta/Blueprint/AllowPrivateAccess/AllowPrivateAccess.md` |
| `meta.WorldContext` | `UFUNCTION` | 指定 WorldContext 参数 | 静态 Blueprint 函数库需要世界上下文 | `DefaultToSelf`, `HidePin` | `verified_UE5.8` | `references/sources/Meta/Blueprint/WorldContext/WorldContext.md` |
| `meta.DefaultToSelf` | `UFUNCTION` | 参数默认使用 self | Blueprint 节点上下文对象默认绑定调用者 | `WorldContext`, `HidePin` | `imported_from_unreal_specifiers` | `references/sources/Meta/Blueprint/DefaultToSelf/DefaultToSelf.md` |
| `meta.AutoCreateRefTerm` | `UFUNCTION` | 为引用参数自动创建默认输入 | 可选数组、集合或引用参数节点更易用 | `AdvancedDisplay` | `imported_from_unreal_specifiers` | `references/sources/Meta/Blueprint/Param/AutoCreateRefTerm/AutoCreateRefTerm.md` |
| `meta.AdvancedDisplay` | `UFUNCTION`, `UPROPERTY` | 将参数或属性放入高级显示区域 | 减少 Blueprint 节点或 Details Panel 噪声 | `AutoCreateRefTerm` | `imported_from_unreal_specifiers` | `references/sources/Meta/Blueprint/AdvancedDisplay/AdvancedDisplay.md` |
| `meta.ExpandEnumAsExecs` | `UFUNCTION` | 将枚举参数展开为执行引脚 | Blueprint 节点按枚举分支执行 | `ExpandBoolAsExecs` | `imported_from_unreal_specifiers` | `references/sources/Meta/Blueprint/Exec/ExpandEnumAsExecs/ExpandEnumAsExecs.md` |

## Tooltips

| ID | Macro | 摘要 | 使用场景 | 相关项 | 状态 | source_doc |
|---|---|---|---|---|---|---|
| `meta.ToolTip` | `UCLASS`, `UFUNCTION`, `UPROPERTY` | 设置完整提示文本 | 编辑器或 Blueprint 需要说明用途 | `DisplayName`, `ShortToolTip` | `imported_from_unreal_specifiers` | `references/sources/Meta/Development/ToolTip/ToolTip.md` |
| `meta.ShortToolTip` | `UCLASS`, `UFUNCTION`, `UPROPERTY` | 设置较短提示文本 | 类型选择器或紧凑 UI 需要短说明 | `ToolTip`, `DisplayName` | `imported_from_unreal_specifiers` | `references/sources/Meta/Development/ShortTooltip.md` |

## Numeric UI

| ID | Macro | 摘要 | 使用场景 | 相关项 | 状态 | source_doc |
|---|---|---|---|---|---|---|
| `meta.ClampMin` | `UPROPERTY` | 设置数值硬下限 | 防止编辑器输入小于最小值 | `ClampMax`, `UIMin`, `UIMax` | `imported_from_unreal_specifiers` | `references/sources/Meta/Numeric/ClampMin.md` |
| `meta.ClampMax` | `UPROPERTY` | 设置数值硬上限 | 防止编辑器输入大于最大值 | `ClampMin`, `UIMin`, `UIMax` | `imported_from_unreal_specifiers` | `references/sources/Meta/Numeric/ClampMax.md` |
| `meta.UIMin` | `UPROPERTY` | 设置编辑器 UI 滑条下限 | 限制滑条范围但不一定限制最终值 | `UIMax`, `ClampMin`, `ClampMax` | `imported_from_unreal_specifiers` | `references/sources/Meta/Numeric/UIMin/UIMin.md` |
| `meta.UIMax` | `UPROPERTY` | 设置编辑器 UI 滑条上限 | 限制滑条范围但不一定限制最终值 | `UIMin`, `ClampMin`, `ClampMax` | `imported_from_unreal_specifiers` | `references/sources/Meta/Numeric/UIMax.md` |

## Pins

| ID | Macro | 摘要 | 使用场景 | 相关项 | 状态 | source_doc |
|---|---|---|---|---|---|---|
| `meta.HidePin` | `UFUNCTION` | 隐藏指定 Blueprint 节点参数引脚 | 参数由上下文或默认值提供，不希望用户手动连接 | `WorldContext`, `DefaultToSelf` | `imported_from_unreal_specifiers` | `references/sources/Meta/Pin/HidePin/HidePin.md` |

## Missing Or Deferred P0 Items

- P0 中的 `ShortToolTip` 在本仓库文档路径中拼写为 `ShortTooltip.md`。
- `DisplayName` 存在多个上下文文档，本索引优先记录 Blueprint 通用路径；UMETA 枚举值路径为 `references/sources/Meta/Enum/UMETA/DisplayName/DisplayName.md`。
