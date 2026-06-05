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

## Batch 3

| Scenario | Insider sample | Expected route | Result | Follow-up |
|---|---|---|---|---|
| Primary asset id filtering | `Property/Asset/MyProperty_Asset.h` | `constraints.index.md` -> `Meta/TypePicker/AllowedTypes.md` | Updated | Added guardrail that `AllowedTypes` is for `FPrimaryAssetId` / Asset Manager picker filtering, not generic object validation. |
| DataTable row filtering | `Property/TypePicker/MyProperty_RowType.h`; `Property/Asset/MyProperty_AssetDataTags.h` | `constraints.index.md` -> `Meta/TypePicker/RowType.md`; `Meta/Asset/RequiredAssetDataTags.md` | Updated | Added guardrail that `RowType` and asset data tags are editor picker/asset registry filters. |
| Type/class picker UI-only options | `Property/TypePicker/MyProperty_Class.h` | `constraints.index.md` -> `Meta/TypePicker/AllowedClasses.md`; category type-picker index | Pass | Existing type-picker source index routes `MetaClass`, `HideViewOptions`, `ShowTreeView`, and `ShowDisplayNames` correctly. |
| Custom thunk wildcard struct | `Function/Wildcard/MyFunction_Custom.h` | `constraints.index.md` -> `Meta/UHT/CustomThunk.md`; `Meta/Blueprint/Param/CustomStructureParam.md` | Updated | Strengthened guardrail that `CustomThunk`/`CustomStructureParam` require hand-written `DECLARE_FUNCTION(exec...)` thunk code. |
| Variadic/custom thunk path | `Function/Wildcard/MyFunction_Variadic.h` | `constraints.index.md` -> `Meta/Blueprint/Variadic.md`; `Specifier/UFUNCTION/UHT/Variadic.md` | Pass | Existing custom-thunk guardrail covers the high-maintenance path. |
| Animation getter metadata | `Property/AnimBP/MyAnimInstance.h` | `constraints.index.md` -> `Meta/AnimationGraph/AnimGetter.md`; `GetterContext.md` | Updated | Added guardrail that AnimationGraph metadata is subsystem-specific and usually requires an `UAnimInstance`/AnimGraph declaration shape. |
| RigVM pin metadata | `Class/ControlRig/MyRig_Test.h`; `Class/ControlRig/MyRig_CustomWidget.h` | `constraints.index.md` -> `Meta/RigVM/Input.md`; `Output.md`; `CustomWidget.md` | Updated | Added guardrail that RigVM `Input`/`Output` are FRigUnit pin metadata, not ordinary UPROPERTY access/exposure flags. |
| Deprecation metadata | `Class/Display/MyClass_Deprecated.h`; `Property/Development/MyProperty_Development.h` | `constraints.index.md` -> `Meta/Development/DeprecatedProperty.md`; `DeprecatedFunction.md`; `Specifier/UCLASS/Development/Deprecated.md` | Updated | Added guardrail distinguishing UE/editor deprecation metadata from C++ `UE_DEPRECATED` compiler warnings. |
| Development-only Blueprint nodes | `Function/MyFunction_Misc.h` | `constraints.index.md` -> `Meta/Development/DevelopmentOnly.md` | Pass | Existing deprecated/version-sensitive route is enough for this lower-frequency case. |
| Sealed RPC events | `Function/MyFunction_Sealed.h` | `constraints.index.md` -> `Specifier/UFUNCTION/Blueprint/SealedEvent.md` | Pass | Source detail already says `SealedEvent` is event-only and cannot be used on Blueprint events. |

## Batch 3 Result

Batch 3 found no category routing failure. The main fixes were early guardrails for picker-specific metadata, custom thunk implementation obligations, subsystem-specific Animation/RigVM metadata, and declaration-specific deprecation behavior.

## Batch 4

| Scenario | Insider sample | Expected route | Result | Follow-up |
|---|---|---|---|---|
| Blueprint property accessors | `Property/Blueprint/MyProperty_Get.h`; `Property/Blueprint/MyProperty_Set.h` | `constraints.index.md` -> `Specifier/UPROPERTY/Blueprint/BlueprintGetter.md`; `BlueprintSetter.md` | Pass | Existing accessor guardrail already says `BlueprintGetter`/`BlueprintSetter`/`Getter`/`Setter` require matching functions and should not be decoration. |
| Spawn/Create node initialization pins | `Property/Blueprint/MyProperty_ExposeOnSpawn.h` | `constraints.index.md` -> `Meta/Blueprint/ExposeOnSpawn.md` | Updated | Added direct guardrail that `ExposeOnSpawn` is for supported Blueprint Spawn/Create pins on reflected editable/Blueprint-visible properties, not generic constructor API. |
| Dynamic Blueprint output types | `Function/MyFunction_OutputType.h` | `constraints.index.md` -> `Meta/Blueprint/Param/DeterminesOutputType.md`; `DynamicOutputParam.md` | Updated | Added guardrail that `DeterminesOutputType` must name an object/class type picker pin and that non-return dynamic outputs require `DynamicOutputParam`. |
| Expanded enum/bool exec pins | `Function/Exec/MyFunction_Exec.h` | `constraints.index.md` -> `Meta/Blueprint/Exec/ExpandEnumAsExecs.md`; `ExpandBoolAsExecs.md` | Updated | Added guardrail that these metadata entries target bool/enum parameters or `ReturnValue`, hide the original data pin, and reshape Blueprint execution flow. |
| Hidden/internal function pins | `Function/Pin/MyFunction_HidePin.h` | `constraints.index.md` -> `Meta/Pin/HidePin.md`; `InternalUseParam.md` | Updated | Added guardrail that hidden/internal pins are UI shaping only and must name real pins; they do not provide defaults, validation, or access control. |
| Commutative associative operator nodes | `Function/Pin/MyFunction_BinaryOperator.h` | `constraints.index.md` -> `Meta/Blueprint/CommutativeAssociativeBinaryOperator.md` | Updated | Added guardrail that the function must be `BlueprintPure` with exactly two same-type parameters and a return value. |
| UPARAM direction and display | `Function/Param/MyFunction_TestParam.h` | `constraints.index.md` -> `Specifier/UPARAM/Blueprint/ref.md` | Pass | Existing row covers `UPARAM(ref)` direction and `UPARAM(DisplayName=...)` presentation. |
| Async action node generation | `Function/Async/MyFunction_Async.h` | `constraints.index.md` -> `Meta/Blueprint/ExposedAsyncProxy.md`; `HasDedicatedAsyncNode.md`; `BlueprintInternalUseOnly.md` | Updated | Added guardrail that async action metadata is class-side node generation support and still requires the async action base class, factory function shape, and `BlueprintAssignable` delegate pins. |
| World context pin behavior | `Function/MyFunction_WorldContext.h` | `constraints.index.md` -> `Meta/Blueprint/WorldContext.md`; `CallableWithoutWorldContext.md`; `ShowWorldContextPin.md` | Pass | Existing world context rows already cover existing parameter naming and pin display/callability modifiers. |

## Batch 4 Result

Batch 4 found that the routing structure is still workable, but several Blueprint node-shaping caveats were too deep in source detail docs. The fix was to expose short, code-writing guardrails in `constraints.index.md` and strengthen the related Decision Summary requirements.

## Batch 5

| Scenario | Insider sample | Expected route | Result | Follow-up |
|---|---|---|---|---|
| Blueprint class/type exposure | `Class/Blueprint/MyClass_BlueprintType.h`; `Class/Blueprint/MyClass_Blueprintable.h`; `Struct/MyStruct_BlueprintType.h` | `constraints.index.md` -> `Specifier/UCLASS/Blueprint/BlueprintType.md`; `Blueprintable.md`; `Specifier/USTRUCT/Blueprint/BlueprintType.md` | Pass | Existing type exposure row already separates Blueprint variable/parameter exposure from Blueprint inheritance exposure. |
| Blueprint-spawnable components | `Class/Blueprint/MyActorComponent_Spawnable.h` | `constraints.index.md` -> `Meta/Component/BlueprintSpawnableComponent.md` | Updated | Added guardrail that this metadata is for `UActorComponent` Add Component UI availability and does not create components or actors by itself. |
| Blueprint function library context restrictions | `Class/Blueprint/MyClass_RestrictedToClasses.h`; `Class/Blueprint/MyClass_ProhibitedInterfaces.h`; `Class/Blueprint/MyClass_KismetHideOverrides.h` | `constraints.index.md` -> `Meta/Blueprint/RestrictedToClasses.md`; `ProhibitedInterfaces.md`; `KismetHideOverrides.md` | Updated | Added guardrail that these shape Blueprint authoring/action/override availability, not runtime access control. |
| Blueprint thread-safe function library calls | `Class/Blueprint/MyClass_ThreadSafe.h`; `Struct/MyStruct_NativeMakeBreak.h` | `constraints.index.md` -> `Meta/Blueprint/BlueprintThreadSafe.md`; `NotBlueprintThreadSafe.md` | Updated | Added guardrail that thread-safe metadata only changes call eligibility and the C++ implementation must actually be safe off the game thread. |
| Blueprint autocast and type promotion | `Function/TypeCast/MyFunction_AutoCast.h`; `Function/TypeCast/MyFunction_IgnoreTypePromotion.h` | `constraints.index.md` -> `Meta/Blueprint/BlueprintAutocast.md`; `IgnoreTypePromotion.md` | Updated | Added guardrail for pure, low-cost conversion functions and type-promotion opt-out semantics. |
| Custom Blueprint object creation entry | `Class/Blueprint/MyClass_CustomSpawnObject.h` | `constraints.index.md` -> `Meta/Blueprint/DontUseGenericSpawnObject.md` | Updated | Added guardrail that this blocks generic Blueprint Create Object for eligible UObject classes, but not C++ `NewObject`, and should be paired with a domain factory. |
| Native struct Make/Break nodes | `Struct/MyStruct_NativeMakeBreak.h`; `Function/MyFunction_NativeMakeBreak.h`; `Function/TypeCast/MyFunction_IgnoreTypePromotion.h` | `constraints.index.md` -> `Meta/Struct/HasNativeMake.md`; `HasNativeBreak.md`; `Meta/Blueprint/NativeMakeFunc.md`; `NativeBreakFunc.md` | Updated | Added guardrail distinguishing USTRUCT `HasNativeMake`/`HasNativeBreak` function paths from UFUNCTION `NativeMakeFunc`/`NativeBreakFunc` node presentation metadata. |

## Batch 5 Result

Batch 5 covered lower-frequency Blueprint authoring and node-construction metadata that still affects C++ declaration choices. The main fixes were early guardrails for component spawning availability, function library context restrictions, thread-safe call eligibility, implicit conversion/type-promotion behavior, custom object creation entry points, and native Make/Break node paths.

## Batch 6

| Scenario | Insider sample | Expected route | Result | Follow-up |
|---|---|---|---|---|
| Details Panel display-only metadata | `Property/Editor/MyProperty_Show.h`; `MyProperty_HideInDetailPanel.h`; `MyProperty_NoResetToDefault.h`; `MyProperty_MaxPropertyDepth.h`; `Property/Object/MyProperty_Inner.h` | `constraints.index.md` -> `Meta/Object/ShowOnlyInnerProperties.md`; `Meta/DetailsPanel/NoResetToDefault.md`; `MaxPropertyDepth.md`; `HideInDetailPanel.md` | Updated | Added guardrail that these only affect Details Panel presentation and should not be used as runtime validation or access control. |
| Path picker metadata | `Property/Path/MyProperty_Path.h` | `constraints.index.md` -> `Meta/Path/ContentDir.md`; `FilePathFilter.md`; `LongPackageName.md` | Updated | Added guardrail that path metadata targets `FDirectoryPath`/`FFilePath` editor pickers and does not guarantee runtime path resolution or file loading. |
| Soft reference dependency tracking | `Property/Object/MyProperty_Soft.h` | `constraints.index.md` -> `Meta/Object/Untracked.md` | Updated | Added guardrail that `Untracked` affects soft reference asset dependency tracking only, not loading, GC, or persistence. |
| Asset registry and picker filtering | `Property/Asset/MyProperty_AssetRegistrySearchable.h`; `Property/Asset/MyProperty_GetAssetFilter.h` | `constraints.index.md` -> `Specifier/UPROPERTY/Asset/AssetRegistrySearchable.md`; `Meta/Asset/GetAssetFilter.md` | Updated | Added guardrail that asset registry tags and picker filters are editor/registry paths, not runtime asset validation. |
| Duplicate/export/construction-script serialization flows | `Property/Serialization/MyProperty_Serialization.h`; `MyProperty_SerializationText.h`; `MyComponent_SkipUCSModifiedProperties.h` | `constraints.index.md` -> `Specifier/UPROPERTY/Serialization/DuplicateTransient.md`; `SkipSerialization.md`; `TextExportTransient.md`; `Meta/Serialization/SkipUCSModifiedProperties.md` | Updated | Added guardrail that these flags target specific duplicate/export/UCS serialization flows and should not be treated as generic persistence toggles. |
| Material expression metadata | `Property/Material/MyProperty_Material.h` | `constraints.index.md` -> `Meta/Material/RequiredInput.md`; `OverridingInputProperty.md`; `ShowAsInputPin.md` | Updated | Added guardrail that these are consumed by `UMaterialExpression` editor/material node paths, not ordinary `UPROPERTY` behavior. |
| Unsafe during Actor construction | `Function/MyFunction_Unsafe.h` | `constraints.index.md` -> `Meta/Blueprint/UnsafeDuringActorConstruction.md` | Updated | Added guardrail that this limits unsafe Blueprint use during actor construction and does not make the function generally safe. |
| Python/script export metadata | `Python/MyPython_ScriptMethod.h`; `MyPython_ScriptOperator.h`; `MyPython_ScriptMakeBreak.h`; `MyPython_ScriptConstant.h` | `constraints.index.md` -> `Meta/Script/ScriptMethod.md`; `ScriptOperator.md`; `ScriptConstant.md`; `ScriptDefaultMake.md` | Updated | Added guardrail that script metadata affects Python/script export behavior and is separate from Blueprint node behavior. |

## Batch 6 Result

Batch 6 covered the remaining editor/tooling-heavy sample groups. The main fixes were boundaries: Details Panel metadata is presentation-only, path metadata is picker-only, asset filtering is editor/registry-only, material metadata is `UMaterialExpression`-specific, Python script metadata is export-specific, and serialization flags must be chosen for the exact serialization flow.

## Route Smoke Test 1

| Prompt shape | Expected first route | Result | Follow-up |
|---|---|---|---|
| Write a replicated actor property with RepNotify and Blueprint read access | `constraints.index.md` before source docs | Pass | Constraint rows cover replication setup, RepNotify, and Blueprint access separation. |
| Write a Blueprint async action with proxy output and world context | `constraints.index.md` -> `Meta/Blueprint/ExposedAsyncProxy.md`; `WorldContext.md` | Pass | Batch 4 async guardrail now routes to async base/factory/delegate requirements. |
| Add a UMG widget animation binding property | `constraints.index.md` -> `Meta/Widget/BindWidgetAnim.md` | Pass | Constraint row keeps `Transient` requirement visible before opening source detail. |
| Add a type picker or data table row picker property | `constraints.index.md` -> `Meta/TypePicker/AllowedClasses.md`; `AllowedTypes.md`; `RowType.md` | Pass | Batch 3 picker guardrail separates class/object, primary asset, row handle, and asset registry filters. |
| Explain a single known symbol such as `BlueprintCallable` | `common.index.md` | Pass | Single-symbol lookup still uses common first. |
| Bare ambiguous symbol such as `Category`, `BlueprintType`, or `Transient` | `ambiguous-symbols.index.md` if macro/context is unclear | Pass | `SKILL.md` still directs ambiguous symbols through the ambiguity index. |

## Route Smoke Test 1 Result

The authoring route should now prefer `constraints.index.md` for combined UE C++ declaration behavior and reserve `common.index.md` for direct symbol lookup. `SKILL.md` and `routing.index.md` were updated accordingly.
