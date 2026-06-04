# UE5.8 P2 Complete Pass - 2026-06-05

Scope: audit all remaining P2 rows after P0/P1 completion.

Result:

- Processed P2 rows: 69
- `verified_UE5.8`: 67
- `changed_in_version`: 1
- `removed_or_deprecated`: 1
- Remaining P2 pending rows expected after this pass: 0

Evidence checked:

- UE5.8 `Programs/Shared/EpicGames.UHT/Specifiers/UhtFunctionSpecifiers.cs`, `UhtDefaultSpecifiers.cs`, and parser tables for `UFUNCTION`, `Category`, `Exec`, route pages, `Comment`, and `FriendlyName`.
- UE5.8 `Runtime/CoreUObject/Public/UObject/ObjectMacros.h` for class/property/function metadata declarations including component, asset picker, details panel, and pin metadata.
- UE5.8 `Runtime/Engine/Private/ObjectEditorUtils.cpp` and editor detail customizations for `DevelopmentStatus`.
- UE5.8 `Editor/UMGEditor` and `Runtime/UMG` for `BindWidget*`, `OptionalWidget`, `DesignerRebuild`, `DisableNativeTick`, `EntryClass`, `EntryInterface`, `IsBindableEvent`, and `ViewmodelBlueprintWidgetExtension` examples.
- UE5.8 `Editor/AnimGraph`, `Runtime/Engine/Classes/Animation`, `Runtime/AnimGraphRuntime`, and `Editor/Persona` for animation graph metadata such as `AnimGetter`, `GetterContext`, `FoldProperty`, `AnimNotifyBoneName`, and `AnimNotifyExpand`.
- UE5.8 `Editor/PropertyEditor`, `Editor/DetailCustomizations`, `Editor/StructUtilsEditor`, and `Editor/ContentBrowser` for type picker, class/struct picker, asset picker, row type, directory path, map key, array title, and content visibility metadata.

Important caveats:

- `meta.AllowedParamType` was not found in the local UE5.8 installed source tree. The imported source doc references an AnimNext-style parameter widget example, so this row is recorded as `changed_in_version` instead of being marked verified.
- `meta.OnEvaluate` is still recognized by UE5.8 AnimGraph compiler code, but the compiler emits a deprecation warning. It is recorded as `removed_or_deprecated` and should not be recommended for new code.
- Many P2 rows are editor-only metadata. `verified_UE5.8` means UE5.8 source retains a declaration, example, or consuming path; it does not mean every editor UI path was manually clicked.

Updated items:

- `UFUNCTION.Category` -> `verified_UE5.8`
- `UFUNCTION.Exec` -> `verified_UE5.8`
- `UFUNCTION.UFUNCTION(标识符)` -> `verified_UE5.8`
- `meta.AllowAbstract` -> `verified_UE5.8`
- `meta.AllowAnyActor` -> `verified_UE5.8`
- `meta.AllowedClasses` -> `verified_UE5.8`
- `meta.AllowedParamType` -> `changed_in_version`
- `meta.AllowedTypes` -> `verified_UE5.8`
- `meta.AlwaysAsPin` -> `verified_UE5.8`
- `meta.AnimBlueprintFunction` -> `verified_UE5.8`
- `meta.AnimGetter` -> `verified_UE5.8`
- `meta.AnimNotifyBoneName` -> `verified_UE5.8`
- `meta.AnimNotifyExpand` -> `verified_UE5.8`
- `meta.AnimationGraph.CustomWidget` -> `verified_UE5.8`
- `meta.ArraySizeEnum` -> `verified_UE5.8`
- `meta.BaseClass` -> `verified_UE5.8`
- `meta.BaseStruct` -> `verified_UE5.8`
- `meta.BindWidget` -> `verified_UE5.8`
- `meta.BindWidgetAnim` -> `verified_UE5.8`
- `meta.BindWidgetAnimOptional` -> `verified_UE5.8`
- `meta.BindWidgetOptional` -> `verified_UE5.8`
- `meta.BlueprintBaseOnly` -> `verified_UE5.8`
- `meta.BlueprintSpawnableComponent` -> `verified_UE5.8`
- `meta.ChildCanTick` -> `verified_UE5.8`
- `meta.ChildCannotTick` -> `verified_UE5.8`
- `meta.Comment` -> `verified_UE5.8`
- `meta.CustomizeProperty` -> `verified_UE5.8`
- `meta.DefaultGraphNode` -> `verified_UE5.8`
- `meta.DeprecationMessage` -> `verified_UE5.8`
- `meta.DesignerRebuild` -> `verified_UE5.8`
- `meta.DevelopmentOnly` -> `verified_UE5.8`
- `meta.DevelopmentStatus` -> `verified_UE5.8`
- `meta.DisableNativeTick` -> `verified_UE5.8`
- `meta.DisallowedAssetDataTags` -> `verified_UE5.8`
- `meta.DisallowedClasses` -> `verified_UE5.8`
- `meta.DisallowedStructs` -> `verified_UE5.8`
- `meta.EditFixedOrder` -> `verified_UE5.8`
- `meta.EntryClass` -> `verified_UE5.8`
- `meta.EntryInterface` -> `verified_UE5.8`
- `meta.ExactClass` -> `verified_UE5.8`
- `meta.ExcludeBaseStruct` -> `verified_UE5.8`
- `meta.FoldProperty` -> `verified_UE5.8`
- `meta.ForceShowEngineContent` -> `verified_UE5.8`
- `meta.ForceShowPluginContent` -> `verified_UE5.8`
- `meta.FriendlyName` -> `verified_UE5.8`
- `meta.GetAllowedClasses` -> `verified_UE5.8`
- `meta.GetAssetFilter` -> `verified_UE5.8`
- `meta.GetDisallowedClasses` -> `verified_UE5.8`
- `meta.GetterContext` -> `verified_UE5.8`
- `meta.HideViewOptions` -> `verified_UE5.8`
- `meta.IsBindableEvent` -> `verified_UE5.8`
- `meta.MetaClass` -> `verified_UE5.8`
- `meta.MetaStruct` -> `verified_UE5.8`
- `meta.MustImplement` -> `verified_UE5.8`
- `meta.NeverAsPin` -> `verified_UE5.8`
- `meta.NoElementDuplicate` -> `verified_UE5.8`
- `meta.OnEvaluate` -> `removed_or_deprecated`
- `meta.OnlyPlaceable` -> `verified_UE5.8`
- `meta.OptionalWidget` -> `verified_UE5.8`
- `meta.PinShownByDefault` -> `verified_UE5.8`
- `meta.ReadOnlyKeys` -> `verified_UE5.8`
- `meta.RequiredAssetDataTags` -> `verified_UE5.8`
- `meta.RowType` -> `verified_UE5.8`
- `meta.ShowDisplayNames` -> `verified_UE5.8`
- `meta.ShowTreeView` -> `verified_UE5.8`
- `meta.StructTypeConst` -> `verified_UE5.8`
- `meta.TitleProperty` -> `verified_UE5.8`
- `meta.UseComponentPicker` -> `verified_UE5.8`
- `meta.ViewmodelBlueprintWidgetExtension` -> `verified_UE5.8`
