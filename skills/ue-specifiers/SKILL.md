---
name: ue-specifiers
description: Use when editing, reviewing, validating, auditing, or learning Unreal Engine C++ reflection specifiers and metadata, including UCLASS, USTRUCT, UENUM, UINTERFACE, UPROPERTY, UFUNCTION, UPARAM, UMETA, meta=(...), Blueprint exposure, Details Panel behavior, replication, SaveGame, Config, Instanced objects, editor-only behavior, UHT diagnostics, and Unreal Engine version-specific specifier behavior.
---

# ue-specifiers

Use this skill to choose, verify, correct, and improve Unreal Engine C++ specifier and metadata knowledge.

## Language

- Default output language: Chinese.
- Keep code identifiers in English.
- Keep Unreal Engine official terms in English when translation would reduce clarity.

## Knowledge Trust Levels

Every knowledge item should use one of these statuses:

- `unknown`
- `imported_from_unreal_specifiers`
- `suspected_stale`
- `verified_UE5.8`
- `changed_in_version`
- `removed_or_deprecated`
- `project_observation_only`
- `promoted`

Treat `verified_UE5.8` as "checked against UE5.8 source, UHT/parser behavior, successful compile evidence, or a focused repro sufficient for recommendation." It does not require manually clicking every editor UI variation. If a claim is based only on local project observation, keep it as `project_observation_only`.

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
- `imported_from_unreal_specifiers`, `suspected_stale`, `unknown`, `project_observation_only`: treat as unverified. Use only with explicit uncertainty or after checking source.

Cold or internal rows such as UHT-only, NoExportTypes-only, generated, plugin-specific, or negative-reference pages can be `verified_UE5.8` but still not appropriate for ordinary project code. State the scope before recommending them.

This skill does not include Unreal reflection flag reference pages. For `EClassFlags`, `EPropertyFlags`, `EFunctionFlags`, `EStructFlags`, or `EEnumFlags`, inspect Unreal Engine source directly or use a separate dedicated reference.

## Audit Workflow

When auditing old knowledge:

1. Pick a small batch from `references/audits/audit-manifest.jsonl`.
2. For each item, check the source document claim, Unreal Engine source evidence if available, UHT/reflection behavior, and a minimal repro if needed.
3. Prefer one compact batch note under `references/audits/` that lists item, status, evidence, and caveats.
4. Create per-item finding files only for changed behavior, contradictions, unresolved ambiguity, or important exceptions.
5. Update `references/audits/audit-status.jsonl`.
6. For source-level format progress, update `references/audits/source-normalization-status.jsonl`.
7. Keep canonical source explanations under `references/sources/`; keep indexes and recipes as lightweight navigation, not duplicated explanations.
8. Regenerate `references/indexes/sources.index.md` when source frontmatter, summary, usage, or status changes.
9. During explicit audit or maintenance work, keep `references/indexes/` synchronized with source frontmatter and audit status. During ordinary usage, treat indexes as read-only navigation.

Maintenance scripts:

- `python skills/ue-specifiers/scripts/audit_manifest.py status`
- `python skills/ue-specifiers/scripts/sync_audit_manifest.py --dry-run`
- `python skills/ue-specifiers/scripts/build_index.py --dry-run`
- `python skills/ue-specifiers/scripts/normalize_sources.py --dry-run`

## Learning Workflow

When learning from daily development:

1. Extract the concrete lesson from the project change.
2. Write a note into `references/learning/inbox/`.
3. Include project name, file path, before/after code, problem, fix, related symbol, confidence, and whether the lesson is project-specific or general UE behavior.
4. Do not promote directly unless the user explicitly asks to promote.
5. Promote only after review or reproduction.

Optional local sample corpus:

- During local development, if `D:/github/GitWorkspace/Hello/Source/Insider` exists, use it as a non-canonical UE5.8 sample corpus for concrete specifier/meta examples.
- Treat those examples as project observations unless a finding or repro verifies general Unreal Engine behavior.
- See `references/sample-corpus.md` before using local sample paths.

## Important Rules

- Do not invent Unreal specifiers or metadata keys.
- Do not silently overwrite existing knowledge.
- If knowledge is version-sensitive, record the UE version.
- Prefer actual Unreal Engine source or compiler behavior over memory.
- If evidence is insufficient, mark the item as uncertain.
- AI may write `references/learning/inbox/`. Only update `references/indexes/`, `references/recipes/`, `references/pitfalls/`, or `references/conflicts/` during explicit audit, maintenance, promote, or update work.
