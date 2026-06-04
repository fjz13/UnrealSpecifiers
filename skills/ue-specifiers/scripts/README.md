# Scripts

These scripts maintain the local `ue-specifiers` reference corpus. They use Python standard library only.

## Audit Manifest

```powershell
python skills/ue-specifiers/scripts/audit_manifest.py status
python skills/ue-specifiers/scripts/audit_manifest.py list --priority P0 --limit 20
python skills/ue-specifiers/scripts/audit_manifest.py next --priority P0 --limit 5
```

Reads `references/audits/audit-manifest.jsonl` and reports status/finding coverage.

## Sync Audit Manifest

```powershell
python skills/ue-specifiers/scripts/sync_audit_manifest.py --dry-run
python skills/ue-specifiers/scripts/sync_audit_manifest.py
```

Synchronizes `references/audits/audit-manifest.jsonl` from normalized `specifier` and `meta` source documents. Existing verified rows keep their status and evidence path; new rows are added as `audit_pending` with deterministic P0-P3 priorities.

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

## Removed Legacy Helpers

The old query, header lint, patch-learning, and learning-promotion helpers were removed because they were not wired into the current audit workflow and had stale assumptions about the reference structure. Use `references/indexes/sources.index.md` plus focused source documents for lookup, and record audit progress through `audit-manifest.jsonl`.
