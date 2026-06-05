---
name: ue-specifiers
description: Use when writing, editing, reviewing, validating, or explaining Unreal Engine C++ reflected declarations: UCLASS, USTRUCT, UENUM, UINTERFACE, UPROPERTY, UFUNCTION, UPARAM, UMETA, meta=(...), Blueprint exposure, Details Panel, replication/RPC, SaveGame, Config, Instanced objects, UMG binding, type pickers, UHT diagnostics, or UE5.8 specifier behavior.
---

# ue-specifiers

Use this skill to make Unreal Engine C++ reflected declarations correct while writing code. Treat it as a code-authoring guardrail first, and as a reference lookup only when the user is asking about specifiers/metadata directly.

## Language

- Default output language: Chinese.
- Keep code identifiers in English.
- Keep Unreal Engine official terms in English when translation would reduce clarity.

## Evidence And Status

Source documents and indexes use these statuses to control code recommendations:

- `verified_UE5.8`: may use for UE5.8 when the use case matches the source document caveats. This means checked against UE5.8 source, UHT/parser behavior, successful compile evidence, or a focused repro sufficient for recommendation; it does not require manual editor UI testing for every variation.
- `changed_in_version`: do not use as a normal UE5.8 solution; explain the version change only when relevant and prefer the current engine path.
- `removed_or_deprecated`: do not use for new code; mention only for migration, diagnosis, or historical compatibility.

Do not present local project observation as general Unreal Engine behavior unless the source document also gives broader evidence. Cold or internal rows such as UHT-only, NoExportTypes-only, generated, plugin-specific, or negative-reference pages can be `verified_UE5.8` but still not appropriate for ordinary project code; state the scope before recommending them.

## Code Authoring Workflow

When writing or editing UE C++ reflected declarations:

1. Infer the reflected contract before choosing specifiers: C++ only, Blueprint API, Details Panel editing, config, SaveGame, replication/RPC, instanced subobject, type/object picker, editor-only behavior, or UHT-only behavior.
2. Use the minimal specifier and metadata set that satisfies that contract. Do not add Blueprint, editor, config, network, or SaveGame exposure unless the code path requires it.
3. Check that every chosen specifier/meta key is valid for its macro and declaration kind: `UCLASS`, `USTRUCT`, `UENUM`, `UINTERFACE`, `UPROPERTY`, `UFUNCTION`, `UPARAM`, `UMETA`, or `meta=(...)`.
4. For code-writing tasks with combined behavior such as Blueprint exposure plus Details Panel editing, persistence, networking, instancing, Blueprint node shape, UMG binding, bitmask, picker behavior, or subsystem metadata, check `references/indexes/constraints.index.md` before opening source docs.
5. For single known symbols or direct lookup questions, search `references/indexes/common.index.md` first. If a bare symbol can refer to multiple source docs and the macro/context is unclear, use `references/indexes/ambiguous-symbols.index.md` to disambiguate. For obscure, version-sensitive, or UHT-diagnostic choices, open `references/indexes/routing.index.md`, choose the smallest next file, then use `references/indexes/sources.index.md` only as a category directory.
6. Open source documents only when needed to resolve validity, scope, caveats, common misuse, or UE version behavior. When a source document has `Decision Summary`, read that section first and use the longer body only for evidence or edge cases. In `common.index.md`, `Doc` is relative to `references/sources/`; in category indexes, combine the nearest `Doc root` with the row `Doc`, and treat `Doc root` as relative to `references/sources/`.
7. Prefer code that compiles under UE5.8 UHT behavior. Mention version uncertainty only when the item is not verified for the target UE version or when behavior is version-sensitive.

## Code Output Rules

- For code-writing tasks, output the corrected UE C++ code in the repository's existing style.
- Do not turn normal code generation into a specifier reference answer.
- Explain specifier/meta choices only when they are non-obvious, risky, deprecated, version-sensitive, contrary to the user's requested exposure, or explicitly requested.
- If the requested exposure is too broad, use the narrower valid specifier set and briefly state the reason.
- If the user's code does not need reflection, do not add Unreal reflection macros or metadata just because the surrounding code uses them.

## Minimal Exposure Defaults

- Prefer C++-only declarations when Blueprint/editor/config/network systems do not need access.
- Prefer read-only Blueprint exposure over write exposure unless Blueprint mutation is part of the workflow.
- Prefer the narrowest Details Panel edit scope: defaults-only, instance-only, or visible-only as required by the use case.
- Do not add `EditAnywhere`, `BlueprintReadWrite`, `BlueprintCallable`, `Config`, `SaveGame`, replication, or RPC specifiers as convenience defaults.
- For object/class/type pickers, constrain selectable types with the narrowest valid metadata instead of accepting broad UObject/class choices.

This skill does not include Unreal reflection flag reference pages. For `EClassFlags`, `EPropertyFlags`, `EFunctionFlags`, `EStructFlags`, or `EEnumFlags`, inspect Unreal Engine source directly or use a separate dedicated reference.

## Important Rules

- Do not invent Unreal specifiers or metadata keys.
- Do not silently overwrite existing knowledge.
- If knowledge is version-sensitive, record the UE version.
- Prefer actual Unreal Engine source or compiler behavior over memory.
- If evidence is insufficient, mark the item as uncertain.
