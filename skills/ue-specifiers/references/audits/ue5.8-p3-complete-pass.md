# UE5.8 P3 Complete Pass - 2026-06-05

Scope: finish all remaining P3 audit-pending rows.

Result:

- Processed P3 rows: 144
- `verified_UE5.8`: 142
- `changed_in_version`: 2
- Remaining P3 pending rows expected after this pass: 0

Evidence checked:

- UE5.8 `Programs/Shared/EpicGames.UHT/Specifiers` for internal and cold specifiers such as `CustomConstructor`, `CustomFieldNotify`, `CustomThunk`, `FieldNotify`, `NoExport`, `MinimalAPI`, `Atomic`, `HasDefaults`, `IsCoreType`, `BlueprintInternalUseOnly`, and `BlueprintInternalUseOnlyHierarchical`.
- UE5.8 `Programs/Shared/EpicGames.UHT/Parsers`, `Types`, and `Utils/UhtNames.cs` for generated metadata such as `IncludePath`, `ModuleRelativePath`, `DocumentationPolicy`, `CustomThunk`, `CppFromBpEvent`, and `NativeConstTemplateArg`.
- UE5.8 `Runtime/CoreUObject/Public/UObject/ObjectMacros.h` for metadata declarations and enum listings covering debug, development, object, path, enum, script, struct, and field metadata.
- UE5.8 editor/runtime modules for material, path, string, object, enum, sequencer, animation graph, and property editor metadata consumers.
- UE5.8 plugin source under Niagara, GameplayAbilities, ControlRig/RigVM, TextureGraph, Dataflow, LiveLink, and Takes for plugin-specific metadata.

Important caveats:

- `UCLASS.Without_UCLASS` is not a real UE specifier. It is retained as a negative/reference page describing ordinary C++ classes that do not participate in UHT reflection.
- `meta.MaterialNewHLSLGenerator` was not found as an exact metadata key in UE5.8. UE5.8 material code uses `bEnableNewHLSLGenerator` / `IsUsingNewHLSLGenerator` paths instead, so this row is recorded as `changed_in_version`.
- `meta.TakeRecorderDisplayName` was not found as an exact metadata consumer in UE5.8. Take Recorder source classes now return localized display text directly, so this row is recorded as `changed_in_version`.
- P3 includes many engine-internal, plugin-specific, NoExportTypes-only, generated, or cold metadata keys. `verified_UE5.8` means the key or specifier is retained in the UE5.8 source path checked here; it is not a recommendation for ordinary project use.

Updated items:

- `UCLASS.CustomConstructor` -> `verified_UE5.8`
- `UCLASS.CustomFieldNotify` -> `verified_UE5.8`
- `UCLASS.CustomThunkTemplates` -> `verified_UE5.8`
- `UCLASS.Deprecated` -> `verified_UE5.8`
- `UCLASS.EarlyAccessPreview` -> `verified_UE5.8`
- `UCLASS.Experimental` -> `verified_UE5.8`
- `UCLASS.Interface` -> `verified_UE5.8`
- `UCLASS.Intrinsic` -> `verified_UE5.8`
- `UCLASS.MinimalAPI` -> `verified_UE5.8`
- `UCLASS.NoExport` -> `verified_UE5.8`
- `UCLASS.UCLASS()` -> `verified_UE5.8`
- `UCLASS.Without_UCLASS` -> `verified_UE5.8`
- `UFUNCTION.BlueprintInternalUseOnly` -> `verified_UE5.8`
- `UFUNCTION.CustomThunk` -> `verified_UE5.8`
- `UFUNCTION.FieldNotify` -> `verified_UE5.8`
- `UFUNCTION.Variadic` -> `verified_UE5.8`
- `UINTERFACE.ConversionRoot` -> `verified_UE5.8`
- `UINTERFACE.MinimalAPI` -> `verified_UE5.8`
- `UPROPERTY.FieldNotify` -> `verified_UE5.8`
- `UPROPERTY.Native` -> `verified_UE5.8`
- `USTRUCT.Atomic` -> `verified_UE5.8`
- `USTRUCT.BlueprintInternalUseOnly` -> `verified_UE5.8`
- `USTRUCT.BlueprintInternalUseOnlyHierarchical` -> `verified_UE5.8`
- `USTRUCT.HasDefaults` -> `verified_UE5.8`
- `USTRUCT.HasNoOpConstructor` -> `verified_UE5.8`
- `USTRUCT.IsAlwaysAccessible` -> `verified_UE5.8`
- `USTRUCT.IsCoreType` -> `verified_UE5.8`
- `USTRUCT.NoExport` -> `verified_UE5.8`
- `meta.MaterialNewHLSLGenerator` -> `changed_in_version`
- `meta.TakeRecorderDisplayName` -> `changed_in_version`
- Remaining P3 metadata rows -> `verified_UE5.8`
