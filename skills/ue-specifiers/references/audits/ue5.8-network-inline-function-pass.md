# UE5.8 Network, Inline Object, and Function Specifier Pass

Date: 2026-06-05

Scope: audited 4 P0 pending items against installed UE5.8 source and local Hello sample code.

## Verified Items

| Item | Status | UE5.8 evidence | Caveat |
|---|---|---|---|
| `UPROPERTY.Replicated` | `verified_UE5.8` | UHT `ReplicatedSpecifier` sets `EPropertyFlags.Net` and logs an error for direct struct members; Hello `Property/Network/MyProperty_Network.h/.cpp` shows `CPF_Net` plus `DOREPLIFETIME`. | Runtime replication still requires owning object replication and lifetime registration. |
| `UCLASS.EditInlineNew` | `verified_UE5.8` | UHT `EditInlineNewSpecifier` adds `EClassFlags.EditInlineNew`; `NotEditInlineNewSpecifier` removes it. PropertyEditor inline class filter requires `CLASS_EditInlineNew` for inline-created class choices. | Details Panel visual combinations were not exhaustively clicked. |
| `UFUNCTION.BlueprintPure` | `verified_UE5.8` | UHT `BlueprintPureSpecifier` sets `BlueprintCallable` and, unless false, `BlueprintPure`; `UhtFunction` rejects pure functions without outputs and can auto-pure const callable output functions. | Blueprint graph node rendering was not exhaustively observed. |
| `UFUNCTION.CallInEditor` | `verified_UE5.8` | UHT `CallInEditorSpecifier` writes `CallInEditor=true` metadata. PropertyEditor filters zero-parameter CallInEditor functions and adds function call widgets to Details Panel. | Editor button placement was not manually clicked in every object type. |

## Source Details Updated

- `references/sources/Specifier/UPROPERTY/Network/Replicated.md`
- `references/sources/Specifier/UCLASS/Instance/EditInlineNew/EditInlineNew.md`
- `references/sources/Specifier/UFUNCTION/Blueprint/BlueprintPure/BlueprintPure.md`
- `references/sources/Specifier/UFUNCTION/Blueprint/CallInEditor/CallInEditor.md`

Each source detail now includes:

- `## 行为`
- `## UE5.8 审计结论`
- `## 常见误用`

## Local Sample Corpus

Hello project evidence is supportive, not canonical:

- Project: `D:/github/GitWorkspace/Hello/Hello.uproject`
- EngineAssociation: `5.8`
- Sample root: `D:/github/GitWorkspace/Hello/Source/Insider`
- Relevant samples:
  - `Property/Network/MyProperty_Network.h`
  - `Property/Network/MyProperty_Network.cpp`
  - `Class/Instance/MyClass_Edit.h`
  - `Function/MyFunction_Default.h`
