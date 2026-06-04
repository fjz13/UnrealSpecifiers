# Scripts

All scripts use Python standard library only and are read-only by default.

## Query

```powershell
python skills/ue-specifiers/scripts/query_specifier.py EditAnywhere
python skills/ue-specifiers/scripts/query_specifier.py --macro UPROPERTY --name EditAnywhere
python skills/ue-specifiers/scripts/query_specifier.py "蓝图 只读"
```

Searches `references/indexes`, `references/recipes`, `references/pitfalls`, and `references/conflicts`.

## Audit Manifest

```powershell
python skills/ue-specifiers/scripts/audit_manifest.py status
python skills/ue-specifiers/scripts/audit_manifest.py list --priority P0 --limit 20
python skills/ue-specifiers/scripts/audit_manifest.py next --priority P0 --limit 5
```

Reads `references/audits/audit-manifest.jsonl` and reports status/finding coverage.

## Header Lint

```powershell
python skills/ue-specifiers/scripts/lint_unreal_header.py Source/MyPlugin/Public/MyClass.h
```

Checks obvious reflection macro mistakes:

- `Edit*` mixed with `Visible*`
- `BlueprintReadOnly` mixed with `BlueprintReadWrite`
- Blueprint-exposed properties missing `Category`
- `ReplicatedUsing` without matching `OnRep_` declaration
- suspicious or unindexed `meta` keys

## Learn From Patch

```powershell
git diff > recent.diff
python skills/ue-specifiers/scripts/learn_from_patch.py --diff-file recent.diff --project LiveData
```

Prints a candidate learning note to stdout. It does not write to canonical references.

## Promote Learning

```powershell
python skills/ue-specifiers/scripts/promote_learning.py references/learning/reviewed/example.md
```

Prints a read-only promotion preview. It does not edit indexes, recipes, pitfalls, or conflicts.

## Build Index

```powershell
python skills/ue-specifiers/scripts/build_index.py --dry-run
python skills/ue-specifiers/scripts/build_index.py
```

Regenerates `references/indexes/sources.index.md` from source frontmatter.

## Normalize Sources

```powershell
python skills/ue-specifiers/scripts/normalize_sources.py --dry-run
python skills/ue-specifiers/scripts/normalize_sources.py
```

Adds or refreshes source frontmatter, writes `references/audits/source-normalization-status.jsonl`, writes the batch summary, and regenerates `references/indexes/sources.index.md`.
