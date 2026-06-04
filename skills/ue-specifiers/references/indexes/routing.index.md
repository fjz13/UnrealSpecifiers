# Routing Index

> First-stop routing map for this skill. Use it to choose the smallest next index. `sources.index.md` is only a category directory; do not treat any source index as a file to read end-to-end.
> `common.index.md` contains only `★★★★` and `★★★★★` items. Missing `常用程度` is treated as `0`.
> Category index filenames are relative to `references/indexes/sources/`. In category indexes, resolve each row `Doc` relative to the nearest preceding `Doc root`; `Doc root` is relative to `references/sources/`.

## Route Order

1. If the user asks for a common symbol or common scenario, search `common.index.md` first.
2. If common does not contain the target, use `sources.index.md` to choose one category file.
3. Search only that category file for the exact ID, metadata key, macro, subsystem, or `Doc`.
4. Open only the selected source files by combining `references/sources/`, the nearest `Doc root`, and the row `Doc`.
5. Use `Doc` sections such as behavior, caveats, and common misuse as the final authority.

## Scenario Routes

| User intent | First index | Fallback category index |
|---|---|---|
| Property editable/visible in Details Panel | `common.index.md` | `specifier-uproperty.index.md`; `meta-details-panel.index.md` |
| Blueprint property read/write exposure | `common.index.md` | `specifier-uproperty.index.md`; `meta-blueprint.index.md` |
| Blueprint function node | `common.index.md` | `specifier-ufunction.index.md`; `meta-blueprint.index.md` |
| RPC or replicated property | `common.index.md` | `specifier-ufunction.index.md`; `specifier-uproperty.index.md` |
| SaveGame persistence | `common.index.md` | `specifier-uproperty.index.md` |
| ini/config property | `common.index.md` | `specifier-uproperty.index.md`; `specifier-uclass.index.md`; `meta-development-config.index.md` |
| Instanced UObject subobject editing | `common.index.md` | `specifier-uproperty.index.md`; `specifier-uclass.index.md`; `meta-details-panel.index.md` |
| Conditional Details Panel UI | `common.index.md` | `meta-details-panel.index.md` |
| Editor button/function in Details Panel | `common.index.md` | `specifier-ufunction.index.md`; `meta-blueprint.index.md` |
| Blueprint function library world context | `common.index.md` | `meta-blueprint.index.md` |
| Numeric editor UI, sliders, clamps, units | `common.index.md` | `meta-details-panel.index.md` |
| Type picker, asset picker, object filtering | `meta-type-picker-assets.index.md` | `common.index.md` |
| Widget binding / UMG metadata | `meta-editor-ui.index.md` | `common.index.md` |
| Animation graph or RigVM metadata | `meta-animation-rigvm.index.md` | `common.index.md` |
| Material, GAS, Niagara, Script, Sequencer, UHT metadata | `meta-engine-subsystems.index.md` | `common.index.md` |
| UCLASS macro-level question | `common.index.md` | `specifier-uclass.index.md` |
| USTRUCT, UENUM, UINTERFACE, or UPARAM macro-level question | `common.index.md` | `specifier-other-macros.index.md` |
| Deprecated, removed, or version-sensitive item | Closest `*.index.md` category by symbol | None |

## Symbol Search Keys

| User mentions | Search key examples |
|---|---|
| UPROPERTY specifier | `EditAnywhere`, `SaveGame`, `ReplicatedUsing` |
| UFUNCTION specifier | `BlueprintCallable`, `Server`, `CallInEditor` |
| UCLASS specifier | `Config`, `Abstract`, `MinimalAPI` |
| USTRUCT specifier | `BlueprintType`, `NoExport` |
| UENUM specifier | `Flags`, `BlueprintType` |
| UPARAM specifier | `ref`, `DisplayName`, `NotReplicated` |
| metadata key | `EditCondition`, `WorldContext`, `AllowedClasses` |

## Reading Budget

- Normal answer: read one routing row, optionally one common row, one category index, and one to three source docs.
- Ambiguous answer: list the candidate source docs and explain the distinction before recommending.
- Do not duplicate long source explanations in index files; indexes only route to canonical source docs.

