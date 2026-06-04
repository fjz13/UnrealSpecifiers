---
name: ue-specifiers
description: Use when editing, reviewing, validating, auditing, or learning Unreal Engine C++ reflection specifiers and metadata, including UCLASS, USTRUCT, UENUM, UINTERFACE, UPROPERTY, UFUNCTION, UPARAM, UMETA, meta=(...), Blueprint exposure, Details Panel behavior, replication, SaveGame, Config, Instanced objects, editor-only behavior, UHT diagnostics, Unreal reflection flags, and Unreal Engine version-specific specifier behavior.
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
4. Search `references/indexes/sources.index.md` for broad source routing; each row includes a short summary, usage hint, status, and `source_doc`.
5. Search the focused indexes under `references/indexes/` for curated specifier or meta summaries.
6. Open the `source_doc` under `references/sources/` when detailed behavior, examples, or original notes are needed.
7. Check `references/conflicts/` for incompatible or misleading combinations.
8. Check `references/pitfalls/` for common AI mistakes.
9. Mention version uncertainty when the item is not verified for the target UE version.
10. Provide: 推荐写法, 原因, 替代方案, 常见误用, and related local knowledge paths.

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
9. Do not overwrite canonical recipes/indexes until the finding is reviewed or promoted.

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
- AI may write `references/learning/inbox/`, but must not overwrite `references/indexes/`, `references/recipes/`, `references/pitfalls/`, or `references/conflicts/` unless the user explicitly runs a promote/update command.
