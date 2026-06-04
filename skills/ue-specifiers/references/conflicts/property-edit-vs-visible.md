# Conflict: Property Edit vs Visible

Status: verified_UE5.8.

## UE5.8 Source Evidence

Checked file:

- `C:/Program Files/Epic Games/UE_5.8/Engine/Source/Programs/Shared/EpicGames.UHT/Specifiers/UhtPropertyMemberSpecifiers.cs`

UHT uses a single `SeenEditSpecifier` gate for these property specifiers:

- `EditAnywhere`
- `EditDefaultsOnly`
- `EditInstanceOnly`
- `VisibleAnywhere`
- `VisibleDefaultsOnly`
- `VisibleInstanceOnly`

If a property has more than one of them, UHT logs an error: "Found more than one edit/visibility specifier (...), only one is allowed".

## Guidance

- Use exactly one edit/visibility specifier per property.
- Choose `Edit*` when Details Panel editing is intended.
- Choose `Visible*` when Details Panel display is intended but direct editing is not.
- Blueprint access is a separate dimension; use `BlueprintReadOnly` or `BlueprintReadWrite` independently when needed.

## Remaining Check

Open the UE5.8 Hello sample in editor to confirm the exact Details Panel UX wording before promoting this conflict note into canonical recipe guidance.
