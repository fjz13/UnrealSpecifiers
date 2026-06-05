# ue-specifiers Insider Routing Audit

Scope: first practical routing pass against `D:\github\GitWorkspace\Hello\Source\Insider` after the UE5.8 source/index normalization.

Goal: verify the skill routes real UE C++ declaration tasks to the smallest useful index/detail docs, especially when Codex is writing code rather than answering lookup questions.

## Batch 1

| Scenario | Insider sample | Expected route | Result | Follow-up |
|---|---|---|---|---|
| Conditional Details Panel fields | `Property/Editor/MyProperty_EditCondition.h` | `constraints.index.md` -> `Meta/DetailsPanel/EditCondition.md` | Pass | Existing constraint covers `EditCondition`, `EditConditionHides`, `InlineEditConditionToggle`, `HideEditConditionToggle`. |
| Replicated actor property and RepNotify | `Property/Network/MyProperty_Network.h` | `constraints.index.md` -> `Specifier/UPROPERTY/Network/Replicated.md`; `ReplicatedUsing.md` | Pass | Existing route covers replication and notify setup. |
| Excluding a replicated struct member | `Property/Network/MyProperty_Network.h` | `constraints.index.md` -> `Specifier/UPROPERTY/Network/NotReplicated.md` | Updated | Added direct guardrail that property-side `NotReplicated` is for USTRUCT members inside replicated structs, not arbitrary actor properties. |
| SaveGame field marking | `Property/Serialization/MyProperty_SaveGame.h` | `constraints.index.md` -> `Specifier/UPROPERTY/Serialization/SaveGame.md` | Pass | Existing constraint already says `SaveGame` marks serialization intent and does not save automatically. |
| UMG widget binding | `Property/Widget/MyProperty_BindWidget.h` | `constraints.index.md` -> `Meta/Widget/BindWidget.md`; `BindWidgetOptional.md` | Pass | Existing route covers required/optional widget name matching. |
| UMG animation binding | `Property/Widget/MyProperty_BindWidget.h` | `constraints.index.md` -> `Meta/Widget/BindWidgetAnim.md` | Updated | Added direct guardrail that `BindWidgetAnim` properties must be `Transient`. |
| Enum bitmask UI | `Enum/MyEnum_Flags.h` | `constraints.index.md` -> `Meta/Enum/Bitmask.md`; `BitmaskEnum.md`; `Bitflags.md` | Pass | Existing constraint covers bitmask semantics vs normal enum dropdowns. |
| Type picker narrowing | `Property/TypePicker/MyProperty_Class.h` | `constraints.index.md` -> `Meta/TypePicker/AllowedClasses.md`; `MustImplement.md`; `MetaClass.md` | Pass | Existing route directs broad class/object picker tasks to the type-picker index. |
| Latent Blueprint function | `Function/Async/MyFunction_Latent.h` | `constraints.index.md` -> `Meta/Blueprint/Latent/Latent.md`; `LatentInfo.md` | Updated | Added direct guardrail that `Latent` should name a matching `FLatentActionInfo` parameter via `LatentInfo`. |
| Self/default pin shaping | `Function/Pin/MyFunction_SelfPin.h` | `constraints.index.md` -> `Meta/Blueprint/DefaultToSelf.md`; `Meta/Pin/HideSelfPin.md` | Updated | Added direct guardrail that `HideSelfPin` hides the member-function target pin, while static parameter hiding needs `HidePin` or `InternalUseParam`. |

## Result

Batch 1 found no routing structure failure. The main gap was that several important caveats existed in source detail docs but were not visible early enough in `constraints.index.md`.

Updated:

- `skills/ue-specifiers/references/indexes/constraints.index.md`
- `skills/ue-specifiers/references/sources/Meta/Widget/BindWidgetAnim.md`
- `skills/ue-specifiers/references/sources/Meta/Blueprint/Latent/LatentInfo.md`
- `skills/ue-specifiers/references/sources/Meta/Pin/HideSelfPin.md`
- `skills/ue-specifiers/tools/validate.ps1`

Next recommended batch: config/default config, instanced inline UObject editing, Blueprint event/native event, RPC direction/reliability, numeric UI clamps/sliders, and display/category behavior.
