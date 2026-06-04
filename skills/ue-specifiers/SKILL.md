---
name: ue-specifiers
description: Use when editing, reviewing, validating, or explaining Unreal Engine C++ reflection specifiers and metadata, including UCLASS, USTRUCT, UENUM, UINTERFACE, UPROPERTY, UFUNCTION, UPARAM, UMETA, meta=(...), Blueprint exposure, Details Panel behavior, replication, SaveGame, Config, Instanced objects, editor-only behavior, UHT diagnostics, and Unreal Engine version-specific specifier behavior.
---

# ue-specifiers

Use this skill to choose, verify, correct, and explain Unreal Engine C++ specifiers and metadata.

## Language

- Default output language: Chinese.
- Keep code identifiers in English.
- Keep Unreal Engine official terms in English when translation would reduce clarity.

## Knowledge Trust Levels

Source documents and indexes use these public statuses:

- `verified_UE5.8`
- `changed_in_version`
- `removed_or_deprecated`

Treat `verified_UE5.8` as "checked against UE5.8 source, UHT/parser behavior, successful compile evidence, or a focused repro sufficient for recommendation." It does not require manually clicking every editor UI variation. Do not present local project observation as general Unreal Engine behavior unless the source document also gives broader evidence.

## Recommendation Workflow

When recommending specifiers or metadata:

1. Identify the UE macro involved: `UCLASS`, `USTRUCT`, `UENUM`, `UINTERFACE`, `UPROPERTY`, `UFUNCTION`, `UPARAM`, `UMETA`, or `meta=(...)`.
2. Identify the user intent: Details Panel, Blueprint exposure, serialization, config, SaveGame, replication, editor-only behavior, instanced subobject, or UHT behavior.
3. Search `references/recipes/` first for scenario guidance.
4. Search `references/indexes/sources.index.md` for authoritative source routing; each row includes a short summary, usage hint, status, and `source_doc`.
5. Optionally search the focused indexes under `references/indexes/` for quick curated summaries, but resolve status conflicts in favor of `sources.index.md` and the source document frontmatter.
6. Open the `source_doc` under `references/sources/` when detailed behavior, examples, or original notes are needed.
7. Check `references/conflicts/` for incompatible or misleading combinations.
8. Check `references/pitfalls/` for common AI mistakes.
9. Mention version uncertainty when the item is not verified for the target UE version.
10. Provide: 推荐写法, 原因, 替代方案, 常见误用, and related local knowledge paths.

## Status Gates

Use status to control recommendations:

- `verified_UE5.8`: may recommend for UE5.8 when the use case matches the source document caveats.
- `changed_in_version`: do not recommend as a normal UE5.8 solution; explain the version change and prefer the replacement or current engine path.
- `removed_or_deprecated`: do not recommend for new code; mention only for migration, diagnosis, or historical compatibility.

Cold or internal rows such as UHT-only, NoExportTypes-only, generated, plugin-specific, or negative-reference pages can be `verified_UE5.8` but still not appropriate for ordinary project code. State the scope before recommending them.

This skill does not include Unreal reflection flag reference pages. For `EClassFlags`, `EPropertyFlags`, `EFunctionFlags`, `EStructFlags`, or `EEnumFlags`, inspect Unreal Engine source directly or use a separate dedicated reference.

## Important Rules

- Do not invent Unreal specifiers or metadata keys.
- Do not silently overwrite existing knowledge.
- If knowledge is version-sensitive, record the UE version.
- Prefer actual Unreal Engine source or compiler behavior over memory.
- If evidence is insufficient, mark the item as uncertain.
