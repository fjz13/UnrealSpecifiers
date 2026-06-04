# UE5.8 P0 Complete Pass - 2026-06-05

Scope: finish the remaining P0 `audit_pending` specifier and metadata rows in `audit-manifest.jsonl`.

Result:

- Processed P0 rows: 50
- `verified_UE5.8`: 49
- `removed_or_deprecated`: 1 (`UPROPERTY.RepRetry`)
- Remaining P0 pending rows expected after this pass: 0

Evidence checked:

- `C:/Program Files/Epic Games/UE_5.8/Engine/Source/Programs/Shared/EpicGames.UHT/Specifiers/UhtFunctionSpecifiers.cs` for UFUNCTION specifier flag writes and direct UHT errors.
- `C:/Program Files/Epic Games/UE_5.8/Engine/Source/Programs/Shared/EpicGames.UHT/Types/UhtFunction.cs` for replicated function and `SealedEvent` validation.
- `C:/Program Files/Epic Games/UE_5.8/Engine/Source/Programs/Shared/EpicGames.UHT/Specifiers/UhtPropertyMemberSpecifiers.cs` for UPROPERTY specifier flag writes and `RepRetry` deprecation.
- `C:/Program Files/Epic Games/UE_5.8/Engine/Source/Programs/Shared/EpicGames.UHT/Specifiers/UhtPropertyArgumentSpecifiers.cs` for `NotReplicated` service-request parameter handling.
- `C:/Program Files/Epic Games/UE_5.8/Engine/Source/Programs/Shared/EpicGames.UHT/Parsers/UhtFunctionParser.cs` for function `AdvancedDisplay` metadata handling.
- `C:/Program Files/Epic Games/UE_5.8/Engine/Source/Programs/Shared/EpicGames.UHT/Specifiers/UhtDefaultSpecifiers.cs` and `Types/UhtType.cs` for `DisplayName`, numeric metadata validation, tooltip lookup, and short-tooltip fallback.
- `C:/Program Files/Epic Games/UE_5.8/Engine/Source/Editor/BlueprintGraph` for `AutoCreateRefTerm`, `DefaultToSelf`, `ExpandEnumAsExecs`, and `HidePin` runtime/editor graph behavior.
- `C:/Program Files/Epic Games/UE_5.8/Engine/Source/Editor/PropertyEditor/Private/PropertyNode.cpp` for `EditConditionHides` and `InlineEditConditionToggle` behavior.
- `D:/github/GitWorkspace/Hello/Source/Insider` sample corpus was used only as local comparison evidence where matching examples already exist.

Important findings:

- `UPROPERTY.RepRetry` is deprecated in UE5.8 UHT: the specifier branch logs an error instead of setting a usable property flag. It is therefore marked `removed_or_deprecated`, not `verified_UE5.8`.
- `UFUNCTION.WithValidation` is still present in UE5.8 UHT and sets `FUNC_NetValidate`; keep the documentation caveat that it is an RPC validation path, not a general function validator.
- `ServiceRequest` and `ServiceResponse` remain present in UE5.8 UHT, require endpoint names, and are service RPC semantics rather than a replacement for normal Gameplay `Server`/`Client` RPCs.
- `AdvancedDisplay` has two P0 meanings: UPROPERTY specifier writes `CPF_AdvancedDisplay`, while UFUNCTION metadata marks selected parameters as advanced display.
- `NotReplicated` has separate UHT paths for USTRUCT members and service request parameters; it is not valid for ordinary UCLASS replicated properties.

Updated items:

- `UFUNCTION.BlueprintAuthorityOnly` -> `verified_UE5.8`
- `UFUNCTION.BlueprintCosmetic` -> `verified_UE5.8`
- `UFUNCTION.BlueprintGetter` -> `verified_UE5.8`
- `UFUNCTION.BlueprintImplementableEvent` -> `verified_UE5.8`
- `UFUNCTION.BlueprintNativeEvent` -> `verified_UE5.8`
- `UFUNCTION.BlueprintSetter` -> `verified_UE5.8`
- `UFUNCTION.Client` -> `verified_UE5.8`
- `UFUNCTION.NetMulticast` -> `verified_UE5.8`
- `UFUNCTION.Reliable` -> `verified_UE5.8`
- `UFUNCTION.SealedEvent` -> `verified_UE5.8`
- `UFUNCTION.Server` -> `verified_UE5.8`
- `UFUNCTION.ServiceRequest` -> `verified_UE5.8`
- `UFUNCTION.ServiceResponse` -> `verified_UE5.8`
- `UFUNCTION.Unreliable` -> `verified_UE5.8`
- `UFUNCTION.WithValidation` -> `verified_UE5.8`
- `UPROPERTY.AdvancedDisplay` -> `verified_UE5.8`
- `UPROPERTY.BlueprintAssignable` -> `verified_UE5.8`
- `UPROPERTY.BlueprintAuthorityOnly` -> `verified_UE5.8`
- `UPROPERTY.BlueprintCallable` -> `verified_UE5.8`
- `UPROPERTY.BlueprintGetter` -> `verified_UE5.8`
- `UPROPERTY.BlueprintSetter` -> `verified_UE5.8`
- `UPROPERTY.EditFixedSize` -> `verified_UE5.8`
- `UPROPERTY.Export` -> `verified_UE5.8`
- `UPROPERTY.Getter` -> `verified_UE5.8`
- `UPROPERTY.Interp` -> `verified_UE5.8`
- `UPROPERTY.NoClear` -> `verified_UE5.8`
- `UPROPERTY.NonPIEDuplicateTransient` -> `verified_UE5.8`
- `UPROPERTY.NonTransactional` -> `verified_UE5.8`
- `UPROPERTY.NotReplicated` -> `verified_UE5.8`
- `UPROPERTY.RepRetry` -> `removed_or_deprecated`
- `UPROPERTY.Setter` -> `verified_UE5.8`
- `UPROPERTY.SimpleDisplay` -> `verified_UE5.8`
- `UPROPERTY.SkipSerialization` -> `verified_UE5.8`
- `UPROPERTY.TextExportTransient` -> `verified_UE5.8`
- `meta.AdvancedDisplay` -> `verified_UE5.8`
- `meta.AllowPrivateAccess` -> `verified_UE5.8`
- `meta.AutoCreateRefTerm` -> `verified_UE5.8`
- `meta.Blueprint.DisplayName` -> `verified_UE5.8`
- `meta.ClampMax` -> `verified_UE5.8`
- `meta.ClampMin` -> `verified_UE5.8`
- `meta.DefaultToSelf` -> `verified_UE5.8`
- `meta.EditConditionHides` -> `verified_UE5.8`
- `meta.Enum.UMETA.DisplayName` -> `verified_UE5.8`
- `meta.ExpandEnumAsExecs` -> `verified_UE5.8`
- `meta.HidePin` -> `verified_UE5.8`
- `meta.InlineEditConditionToggle` -> `verified_UE5.8`
- `meta.ShortTooltip` -> `verified_UE5.8`
- `meta.ToolTip` -> `verified_UE5.8`
- `meta.UIMax` -> `verified_UE5.8`
- `meta.UIMin` -> `verified_UE5.8`
