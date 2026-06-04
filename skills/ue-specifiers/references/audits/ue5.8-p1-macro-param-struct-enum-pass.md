# UE5.8 P1 Macro/Param/Struct/Enum Pass - 2026-06-05

Scope: audit the first P1 batch covering UENUM, UINTERFACE, UPARAM, USTRUCT, and two isolated UPROPERTY specifiers.

Result:

- Processed P1 rows: 17
- `verified_UE5.8`: 15
- `removed_or_deprecated`: 2

Important findings:

- `UPROPERTY.Localized` is deprecated in UE5.8 UHT and should not be recommended.
- `USTRUCT.immutable` is still parsed but UE5.8 validation rejects project structs; it is only legal for NoExportTypes.h mirror structs and is being phased out.
- Macro overview pages such as `UENUM(标识符)` and `UPARAM(标识符)` are route/index documents, not real standalone specifiers.
- `UPARAM.NotReplicated` is only valid for replicated parameters in service request functions, not ordinary UFUNCTION parameters.

Evidence checked:

- UE5.8 `UhtDefaultSpecifiers.cs` for `BlueprintType`, `Blueprintable`, `NotBlueprintable`, and `DisplayName` metadata writes.
- UE5.8 `UhtEnumParser.cs` and `UhtEnumSpecifiers.cs` for UENUM parsing and `Flags`.
- UE5.8 `UhtInterfaceClassParser.cs` for UINTERFACE routing.
- UE5.8 `UhtPropertyParser.cs` and `UhtPropertyArgumentSpecifiers.cs` for UPARAM routing and flags.
- UE5.8 `UhtScriptStructParser.cs`, `UhtScriptStructSpecifiers.cs`, and `UhtScriptStruct.cs` for USTRUCT routing, `BlueprintType`, and `immutable` validation.
- UE5.8 `UhtPropertyMemberSpecifiers.cs` for `AssetRegistrySearchable` and `Localized`.
- `D:/github/GitWorkspace/Hello/Source/Insider` was used as non-canonical sample comparison where matching examples exist.

Updated items:

- `UENUM.BlueprintType` -> `verified_UE5.8`
- `UENUM.Flags` -> `verified_UE5.8`
- `UENUM.UENUM(标识符)` -> `verified_UE5.8`
- `UINTERFACE.Blueprintable` -> `verified_UE5.8`
- `UINTERFACE.NotBlueprintable` -> `verified_UE5.8`
- `UINTERFACE.UINTERFACE(标识符)` -> `verified_UE5.8`
- `UPARAM.Const` -> `verified_UE5.8`
- `UPARAM.DisplayName` -> `verified_UE5.8`
- `UPARAM.NotReplicated` -> `verified_UE5.8`
- `UPARAM.Required` -> `verified_UE5.8`
- `UPARAM.UPARAM(标识符)` -> `verified_UE5.8`
- `UPARAM.ref` -> `verified_UE5.8`
- `UPROPERTY.AssetRegistrySearchable` -> `verified_UE5.8`
- `UPROPERTY.Localized` -> `removed_or_deprecated`
- `USTRUCT.BlueprintType` -> `verified_UE5.8`
- `USTRUCT.USTRUCT(标识符)` -> `verified_UE5.8`
- `USTRUCT.immutable` -> `removed_or_deprecated`
