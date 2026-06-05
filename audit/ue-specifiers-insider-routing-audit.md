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

## Batch 2

| Scenario | Insider sample | Expected route | Result | Follow-up |
|---|---|---|---|---|
| Class/property config pairing | `Class/Config/MyClass_Config.h`; `Property/Config/MyProperty_Config.h` | `constraints.index.md` -> `Specifier/UPROPERTY/Config/Config.md`; `Specifier/UCLASS/Config/Config.md` | Pass | Existing property config docs already explain `UCLASS(Config=...)` pairing and non-SaveGame semantics. |
| Config save destination | `Class/Config/MyClass_DefaultConfig.h`; `Class/Config/MyClass_UserConfig.h` | `constraints.index.md` -> `Specifier/UCLASS/Config/DefaultConfig.md`; `GlobalUserConfig.md`; `ProjectUserConfig.md` | Updated | Added direct guardrail that class-side config destination choices do not make properties config-backed by themselves. |
| Instanced inline UObject ownership | `Class/Instance/MyClass_DefaultToInstanced.h`; `Property/Object/MyProperty_Instanced.h` | `constraints.index.md` -> `Specifier/UPROPERTY/Instanced.md`; `Specifier/UCLASS/Instance/EditInlineNew.md`; `DefaultToInstanced.md` | Pass | Existing constraints cover property-side ownership and class-side inline creation ability. |
| Inline Details Panel display | `Property/EditInline/MyProperty_EditInline.h` | `constraints.index.md` -> `Meta/DetailsPanel/EditInline.md`; `NoEditInline.md` | Updated | Added direct guardrail that `EditInline`/`NoEditInline` are Details Panel display metadata and not ownership semantics. |
| Blueprint event/default implementation | `Function/MyFunction_Default.h` | `constraints.index.md` -> `Specifier/UFUNCTION/Blueprint/BlueprintNativeEvent.md`; `BlueprintImplementableEvent.md` | Pass | Existing constraint and source docs cover `_Implementation` vs Blueprint-only implementation. |
| Blueprint event override display | `Function/MyFunction_ForceAsFunction.h` | `constraints.index.md` -> `Meta/Blueprint/ForceAsFunction.md` | Updated | Added direct guardrail that `ForceAsFunction` changes Blueprint override presentation, and output/return events already become functions. |
| RPC direction and reliability | `Function/MyFunction_Network.h`; `Function/MyFunction_PlayerController.h` | `constraints.index.md` -> `Specifier/UFUNCTION/Network/Server.md`; `Client.md`; `NetMulticast.md`; `Reliable.md`; `WithValidation.md` | Pass | Existing constraints cover RPC direction, reliability, validation, and implementation suffix expectations. |
| Blueprint authority/cosmetic filters | `Function/MyFunction_Network.h` | `constraints.index.md` -> `Specifier/UFUNCTION/Network/BlueprintAuthorityOnly.md`; `BlueprintCosmetic.md` | Updated | Added direct guardrail that these are local Blueprint execution filters, not RPC directions. |
| Numeric editor UI | `Property/Numeric/MyProperty_Numeric.h` | `constraints.index.md` -> `Meta/Numeric/ClampMin.md`; `UIMin.md`; related numeric metadata docs | Pass | Existing numeric constraint correctly separates editor input clamps/UI ranges from runtime validation. |
| Display/category presentation | `Function/Display/MyFunction_Display.h`; `Class/Display/MyClass_AdvancedClassDisplay.h`; `Class/Display/MyClass_CollapseCategories.h` | `constraints.index.md` -> `Meta/Blueprint/AdvancedDisplay.md`; `Specifier/UPROPERTY/DetailsPanel/Category.md`; display/category source indexes | Pass | Existing category and node-shaping constraints cover presentation-only behavior. |

## Batch 2 Result

Batch 2 found no category routing failure. The useful fixes were again early guardrails: config destination, Blueprint authority/cosmetic filters, inline display vs ownership, and event override presentation.

Next recommended batch: type/object/asset picker edge cases, Blueprint pin wildcards/custom thunk, animation/RigVM metadata, and deprecated/version-sensitive entries.
