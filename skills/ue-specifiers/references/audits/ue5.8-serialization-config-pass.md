# UE5.8 Audit - Serialization And Config Property Basics

Date: 2026-06-04

Scope:

- `UPROPERTY.Transient`
- `UPROPERTY.DuplicateTransient`
- `UPROPERTY.Config`
- `UPROPERTY.GlobalConfig`

Status: all four items are `verified_UE5.8`.

Evidence:

- UE5.8 source: `C:/Program Files/Epic Games/UE_5.8/Engine/Build/Build.version` reports `5.8.0`, branch `++UE5+Release-5.8`.
- UE5.8 UHT source checked:
  - `C:/Program Files/Epic Games/UE_5.8/Engine/Source/Programs/Shared/EpicGames.UHT/Specifiers/UhtPropertyMemberSpecifiers.cs`
- UE5.8 CoreUObject source checked:
  - `C:/Program Files/Epic Games/UE_5.8/Engine/Source/Runtime/CoreUObject/Private/UObject/Property.cpp`
  - `C:/Program Files/Epic Games/UE_5.8/Engine/Source/Runtime/CoreUObject/Private/UObject/Obj.cpp`
  - `C:/Program Files/Epic Games/UE_5.8/Engine/Source/Runtime/CoreUObject/Public/UObject/ObjectMacros.h`
- UE5.8 build evidence: `bat/build-hello.bat` built `D:/github/GitWorkspace/Hello/Hello.uproject` as `HelloEditor Win64 Development` with exit code 0. Log: `D:/github/UnrealSpecifiers/.agents/logs/hello-build-20260604-203401-708-30174.log`.
- UE5.8 sample corpus:
  - `D:/github/GitWorkspace/Hello/Source/Insider/Property/Serialization/MyProperty_Serialization.h`
  - `D:/github/GitWorkspace/Hello/Source/Insider/Property/Config/MyProperty_Config.h`
  - `D:/github/GitWorkspace/Hello/Source/Insider/Property/Config/MyProperty_Config.cpp`

## Findings

| Item | Status | Evidence | Caveat |
|---|---|---|---|
| `UPROPERTY.Transient` | `verified_UE5.8` | UE5.8 UHT maps `Transient` to `EPropertyFlags.Transient`; `FProperty::ShouldSerializeValue` skips `CPF_Transient` when archive is persistent and not serializing defaults; `FProperty::ShouldPort` skips transient properties unless explicitly included. Hello sample records `CPF_Transient`. | `Transient` is not a Blueprint access control specifier. |
| `UPROPERTY.DuplicateTransient` | `verified_UE5.8` | UE5.8 UHT maps `DuplicateTransient` to `EPropertyFlags.DuplicateTransient`; `FProperty::ShouldSerializeValue` skips it under `PPF_Duplicate`; `FProperty::ShouldPort` treats it as transient in `PPF_Copy`. Hello sample records `CPF_DuplicateTransient`. | It targets duplication/copy paths, not every persistence path. |
| `UPROPERTY.Config` | `verified_UE5.8` | UE5.8 UHT maps `Config` to `EPropertyFlags.Config`; `SaveConfig` defaults to `CPF_Config` and `LoadConfig`/`SaveConfig` use class config context. Hello sample uses `UPROPERTY(..., Config)` and explicit `SaveConfig(CPF_Config, *fileName)`. | Config file selection comes from class config rules, not from property `Config` itself. |
| `UPROPERTY.GlobalConfig` | `verified_UE5.8` | UE5.8 UHT maps `GlobalConfig` to `EPropertyFlags.GlobalConfig | EPropertyFlags.Config`; `LoadConfig`/`SaveConfig` use the property owner class for global config behavior. Hello sample shows child save/load behavior using the owner class section. | Not suitable when each derived class should have an independent setting. |

## Promotion Notes

- Source detail pages were updated with `行为`, `UE5.8 审计结论`, and `常见误用`.
- Keep `Config` and `GlobalConfig` explanations paired: `GlobalConfig` includes `Config` behavior but changes owner-class lookup/save semantics.
- Keep `Transient` and `DuplicateTransient` explanations separate: one is general persistent serialization/text-port skipping, the other is duplication/copy oriented.
