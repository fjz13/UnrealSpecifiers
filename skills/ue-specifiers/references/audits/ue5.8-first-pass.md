# UE5.8 Audit First Pass

Date: 2026-06-04

Status meaning: `verified_UE5.8` means the item was checked against UE5.8 installed engine source, UHT/parser behavior, successful Hello compile evidence, or focused source evidence sufficient for recommendation. It does not mean every Details Panel or Blueprint UI permutation was manually clicked.

Source detail backfill: see `ue5.8-first-pass-source-backfill.md` for the 2026-06-05 pass that added canonical source detail sections for these already verified items.

## Verified Items

| Item | Status | UE5.8 evidence | Caveat |
|---|---|---|---|
| `UPROPERTY.EditAnywhere` | `verified_UE5.8` | UHT `EditAnywhereSpecifier` sets `EPropertyFlags.Edit`; edit/visibility specifiers share `SeenEditSpecifier`. | Details Panel visual wording not exhaustively observed. |
| `UPROPERTY.VisibleAnywhere` | `verified_UE5.8` | UHT `VisibleAnywhereSpecifier` sets `EPropertyFlags.Edit | EPropertyFlags.EditConst`; same edit/visibility exclusivity gate. | Details Panel visual wording not exhaustively observed. |
| `UPROPERTY.BlueprintReadOnly` | `verified_UE5.8` | UHT sets `EPropertyFlags.BlueprintVisible | EPropertyFlags.BlueprintReadOnly`; rejects `BlueprintReadOnly` with `BlueprintReadWrite` / setter conflicts. | Blueprint editor UI not exhaustively observed. |
| `UFUNCTION.BlueprintCallable` | `verified_UE5.8` | UHT function specifier sets `EFunctionFlags.BlueprintCallable`; `BlueprintPure` implies callable in UHT source. | Blueprint node menu placement not exhaustively observed. |
| `UPROPERTY.ReplicatedUsing` | `verified_UE5.8` | UHT sets `EPropertyFlags.Net`, stores `RepNotifyName`, and sets `EPropertyFlags.RepNotify`; ObjectMacros documents `ReplicatedUsing=FunctionName`. | Runtime replication still depends on replication setup such as lifetime props. |
| `meta.EditCondition` | `verified_UE5.8` | PropertyEditor reads `EditCondition` metadata, parses with `FEditConditionParser`, evaluates it, and handles `EditConditionHides`, `InlineEditConditionToggle`, `HideEditConditionToggle`; parser tests cover bool, numeric, enum, grouping, object, and pointer expressions. | Details Panel UI presentation not exhaustively observed. |
| `UPROPERTY.SaveGame` | `verified_UE5.8` | CoreUObject `FProperty::ShouldSerializeValue` skips non-`CPF_SaveGame` fields when `Ar.IsSaveGame()`; `ArIsSaveGame` default is false. | Save/load sample behavior not re-run as a dedicated automation test. |
| `UPROPERTY.Instanced` | `verified_UE5.8` | UHT `InstancedSpecifier` sets `PersistentInstance | ExportObject | InstancedReference` and adds `EditInline` metadata; UHT validates allowed property kinds. | Details Panel inline object picker not exhaustively observed. |
| `meta.WorldContext` | `verified_UE5.8` | BlueprintGraph defines `MD_WorldContext`, `MD_CallableWithoutWorldContext`, `MD_ShowWorldContextPin`; `UK2Node_CallFunction` enforces unsafe context and auto-connects world context when available. | Blueprint node pin display not exhaustively observed. |

## Local Sample Corpus

Hello project evidence is supportive, not canonical:

- Project: `D:/github/GitWorkspace/Hello/Hello.uproject`
- EngineAssociation: `5.8`
- Sample root: `D:/github/GitWorkspace/Hello/Source/Insider`
- Compile check: `bat/build-hello.bat` succeeded on 2026-06-04.

Useful sample paths:

- `Property/Editor/MyProperty_EditCondition.h`
- `Property/Serialization/MyProperty_SaveGame.h`
- `Property/Serialization/MyProperty_SaveGame.cpp`
- `Property/Object/MyProperty_Instanced.h`
- `Function/MyFunction_WorldContext.h`

## Follow-Up

Use per-item findings only when an item has a correction, version change, contradiction, or unresolved edge case. Do not generate one audit markdown file per specifier just to restate `references/sources`.
