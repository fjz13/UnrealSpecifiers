# Routing Index

> First-stop routing map for this skill. Use it to choose the smallest next index. `sources.index.md` is only a category directory; do not treat any source index as a file to read end-to-end.
> `common.index.md` contains only `★★★★` and `★★★★★` items. Missing `常用程度` is treated as `0`.
> Category index filenames are relative to `references/indexes/sources/`. In category indexes, resolve each row `Doc` relative to the nearest preceding `Doc root`; `Doc root` is relative to `references/sources/`. Use `constraints.index.md` first for specifier/meta combinations.

## Route Order

1. If the task combines exposure, editing, persistence, replication, instancing, UMG binding, Blueprint node shaping, numeric UI, bitmask, picker behavior, or subsystem metadata, check `constraints.index.md`.
2. If the user asks for a single common symbol or direct lookup, search `common.index.md`.
3. If a bare symbol can refer to multiple source docs and the macro/context is unclear, check `ambiguous-symbols.index.md`.
4. If common does not contain the target, use `sources.index.md` to choose one category file.
5. Search only that category file for the exact ID, metadata key, macro, subsystem, or `Doc`.
6. Open only the selected source files by combining `references/sources/`, the nearest `Doc root`, and the row `Doc`.
7. Use `Doc` sections such as behavior, caveats, and common misuse as the final authority.

## Scenario Routes

| Code task | First index | Fallback category index |
|---|---|---|
| Property editable/visible in Details Panel | `common.index.md` | `specifier-uproperty.index.md`; `meta-details-panel.index.md` |
| Blueprint property read/write exposure | `common.index.md` | `specifier-uproperty.index.md`; `meta-blueprint.index.md` |
| Blueprint function node | `common.index.md` | `specifier-ufunction.index.md`; `meta-blueprint.index.md` |
| RPC or replicated property | `constraints.index.md` | `specifier-ufunction.index.md`; `specifier-uproperty.index.md` |
| SaveGame persistence | `constraints.index.md` | `specifier-uproperty.index.md` |
| ini/config property | `constraints.index.md` | `specifier-uproperty.index.md`; `specifier-uclass.index.md`; `meta-development-config.index.md` |
| Instanced UObject subobject editing | `constraints.index.md` | `specifier-uproperty.index.md`; `specifier-uclass.index.md`; `meta-details-panel.index.md` |
| Conditional Details Panel UI | `constraints.index.md` | `meta-details-panel.index.md`; `common.index.md` |
| Editor button/function in Details Panel | `constraints.index.md` | `specifier-ufunction.index.md`; `meta-blueprint.index.md`; `common.index.md` |
| Blueprint event override/default implementation | `constraints.index.md` | `specifier-ufunction.index.md`; `common.index.md` |
| Blueprint function library world context | `constraints.index.md` | `meta-blueprint.index.md`; `common.index.md` |
| Blueprint node shaping, latent action, or custom thunk | `constraints.index.md` | `meta-blueprint.index.md`; `meta-engine-subsystems.index.md`; `common.index.md` |
| Numeric editor UI, sliders, clamps, units | `constraints.index.md` | `meta-details-panel.index.md`; `common.index.md` |
| Enum bitmask or flags UI | `constraints.index.md` | `meta-blueprint.index.md`; `specifier-other-macros.index.md`; `common.index.md` |
| Type picker, asset picker, object filtering | `constraints.index.md` | `meta-type-picker-assets.index.md`; `common.index.md` |
| Widget binding / UMG metadata | `constraints.index.md` | `meta-editor-ui.index.md`; `common.index.md` |
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

## Ambiguous Common Symbols

Use `ambiguous-symbols.index.md` when a bare symbol such as `BlueprintType`, `Category`, `Config`, `Deprecated`, `DisplayName`, `FieldNotify`, or `Transient` has multiple macro or metadata/specifier meanings.

## Reading Budget

- Normal answer: read one routing row, optionally one common row, one category index, and one to three source docs.
- Ambiguous answer: list the candidate source docs and explain the distinction before recommending.
- Do not duplicate long source explanations in index files; indexes only route to canonical source docs.

