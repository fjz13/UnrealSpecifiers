# UE5.8 First Pass Source Detail Backfill

Date: 2026-06-05

Scope: backfilled canonical `references/sources` detail bodies for the 9 items that were already marked `verified_UE5.8` in `ue5.8-first-pass.md`.

## Backfilled Items

| Item | Source detail updated | Evidence basis |
|---|---|---|
| `UPROPERTY.EditAnywhere` | `references/sources/Specifier/UPROPERTY/DetaisPanel/EditAnywhere/EditAnywhere.md` | UE5.8 UHT `EditAnywhereSpecifier` sets `EPropertyFlags.Edit` and enforces edit/visibility exclusivity. |
| `UPROPERTY.VisibleAnywhere` | `references/sources/Specifier/UPROPERTY/DetaisPanel/VisibleAnywhere.md` | UE5.8 UHT `VisibleAnywhereSpecifier` sets `EPropertyFlags.Edit | EPropertyFlags.EditConst` and enforces edit/visibility exclusivity. |
| `UPROPERTY.BlueprintReadOnly` | `references/sources/Specifier/UPROPERTY/Blueprint/BlueprintReadOnly/BlueprintReadOnly.md` | UE5.8 UHT `BlueprintReadOnlySpecifier` sets `BlueprintVisible | BlueprintReadOnly` and rejects write/setter conflicts. |
| `UPROPERTY.SaveGame` | `references/sources/Specifier/UPROPERTY/Serialization/SaveGame/SaveGame.md` | UE5.8 UHT sets `EPropertyFlags.SaveGame`; `FProperty::ShouldSerializeValue` skips non-`CPF_SaveGame` properties when `Ar.IsSaveGame()`. |
| `UPROPERTY.ReplicatedUsing` | `references/sources/Specifier/UPROPERTY/Network/ReplicatedUsing/ReplicatedUsing.md` | UE5.8 UHT sets `Net`, records `RepNotifyName`, sets `RepNotify`, and requires a valid notify function name. |
| `UPROPERTY.Instanced` | `references/sources/Specifier/UPROPERTY/Instance/Instanced/Instanced.md` | UE5.8 UHT sets `PersistentInstance | ExportObject | InstancedReference` and adds `EditInline` metadata. |
| `UFUNCTION.BlueprintCallable` | `references/sources/Specifier/UFUNCTION/Blueprint/BlueprintCallable/BlueprintCallable.md` | UE5.8 UHT function specifier sets `EFunctionFlags.BlueprintCallable`. |
| `meta.EditCondition` | `references/sources/Meta/DetailsPanel/EditCondition/EditCondition.md` | UE5.8 PropertyEditor parses and evaluates expressions through `FEditConditionParser`; parser tests cover common expression kinds. |
| `meta.WorldContext` | `references/sources/Meta/Blueprint/WorldContext/WorldContext.md` | UE5.8 BlueprintGraph defines and consumes `MD_WorldContext`, `MD_CallableWithoutWorldContext`, and `MD_ShowWorldContextPin` in K2 call handling. |

## Progress Note

The source detail pages now carry the same canonical section shape used by later UE5.8 batches:

- `## 行为`
- `## UE5.8 审计结论`
- `## 常见误用`

The index remains a lightweight routing surface with summary, usage, status, and `source_doc`; detailed explanations stay in `references/sources`.
