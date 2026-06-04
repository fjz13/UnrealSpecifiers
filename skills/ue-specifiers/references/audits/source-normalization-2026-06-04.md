# Source Normalization Audit - 2026-06-04

Target version label: `UE5.8`.

Scope:

- Normalized Markdown source documents: 447
- Added machine-readable frontmatter to each source document.
- Regenerated `references/indexes/sources.index.md` as a navigation-only catalog.
- Recorded per-source progress in `references/audits/source-normalization-status.jsonl`.

Important distinction:

- `normalization_status=normalized` means the document has the standard source metadata block.
- `source_status=verified_UE5.8` only applies to items already backed by semantic audit evidence.
- Future imported items should remain `imported_from_unreal_specifiers` until semantic UE5.8 evidence is added.

Counts:

- meta: 303
- specifier: 144
- with code blocks: 354
- with test/example sections: 268
- with principle sections: 257
- with media references: 277

Next maintenance pass:

- Re-run `references/audits/audit-manifest.jsonl` sync when source documents are added or removed.
- Promote verified findings into source documents only when the finding changes or clarifies the canonical explanation.
- Keep full explanations in `references/sources/`; keep indexes concise.
