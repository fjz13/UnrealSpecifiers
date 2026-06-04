# UE5.8 Audit - Details Panel And Blueprint Property Basics

Date: 2026-06-04

Scope:

- `UPROPERTY.EditDefaultsOnly`
- `UPROPERTY.EditInstanceOnly`
- `UPROPERTY.VisibleDefaultsOnly`
- `UPROPERTY.VisibleInstanceOnly`
- `UPROPERTY.BlueprintReadWrite`
- `UPROPERTY.Category`

Status: all six items are `verified_UE5.8`.

Evidence:

- UE5.8 source: `C:/Program Files/Epic Games/UE_5.8/Engine/Build/Build.version` reports `5.8.0`, branch `++UE5+Release-5.8`.
- UE5.8 UHT source checked:
  - `C:/Program Files/Epic Games/UE_5.8/Engine/Source/Programs/Shared/EpicGames.UHT/Specifiers/UhtPropertyMemberSpecifiers.cs`
  - `C:/Program Files/Epic Games/UE_5.8/Engine/Source/Programs/Shared/EpicGames.UHT/Specifiers/UhtDefaultSpecifiers.cs`
  - `C:/Program Files/Epic Games/UE_5.8/Engine/Source/Programs/Shared/EpicGames.UHT/Types/UhtProperty.cs`
- UE5.8 build evidence: `bat/build-hello.bat` built `D:/github/GitWorkspace/Hello/Hello.uproject` as `HelloEditor Win64 Development` with exit code 0. Log: `D:/github/UnrealSpecifiers/.agents/logs/hello-build-20260604-180014-430-42.log`.
- UE5.8 sample corpus: `D:/github/GitWorkspace/Hello/Source/Insider/Property/MyProperty_Test.h` contains the inspected UPROPERTY examples and recorded property flag comments for this batch.

## Findings

| Item | Status | Evidence | Caveat |
|---|---|---|---|
| `UPROPERTY.EditDefaultsOnly` | `verified_UE5.8` | UE5.8 UHT maps `EditDefaultsOnly` to `Edit \| DisableEditOnInstance` and rejects a second edit/visibility specifier; Hello sample records `CPF_Edit \| CPF_DisableEditOnInstance`. | None. |
| `UPROPERTY.EditInstanceOnly` | `verified_UE5.8` | UE5.8 UHT maps `EditInstanceOnly` to `Edit \| DisableEditOnTemplate` and rejects a second edit/visibility specifier; Hello sample records `CPF_Edit \| CPF_DisableEditOnTemplate`. | None. |
| `UPROPERTY.VisibleDefaultsOnly` | `verified_UE5.8` | UE5.8 UHT maps `VisibleDefaultsOnly` to `Edit \| EditConst \| DisableEditOnInstance`; Hello sample records `CPF_Edit \| CPF_DisableEditOnInstance \| CPF_EditConst`. | None. |
| `UPROPERTY.VisibleInstanceOnly` | `verified_UE5.8` | UE5.8 UHT maps `VisibleInstanceOnly` to `Edit \| EditConst \| DisableEditOnTemplate`; Hello sample records `CPF_Edit \| CPF_DisableEditOnTemplate \| CPF_EditConst`. | None. |
| `UPROPERTY.BlueprintReadWrite` | `verified_UE5.8` | UE5.8 UHT sets `BlueprintVisible`, rejects combination with `BlueprintReadOnly`, and rejects private members unless `AllowPrivateAccess` is present; Hello sample records `CPF_BlueprintVisible` without `CPF_BlueprintReadOnly`. | None. |
| `UPROPERTY.Category` | `verified_UE5.8` | UE5.8 UHT stores `Category` as metadata and validates category requirements/warnings for exposed properties; Hello sample uses simple and nested category values. | None. |

## Promotion Notes

- Source documents can keep their current explanations; this pass changes status and routing metadata, not the canonical behavior text.
- Keep the historical source path segment `DetaisPanel` for now to avoid link churn. Generated frontmatter and indexes normalize the visible category to `DetailsPanel`.
- UE5.8 source has been checked directly for this batch.
