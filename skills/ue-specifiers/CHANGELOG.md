# Changelog

## Unreleased

- Created initial `ue-specifiers` skill scaffold.
- Added P0 Markdown indexes imported from `references/sources`.
- Added workflow placeholders for recipes, audits, learning, scripts, and templates.
- Added first-pass recipes, audit manifest, and initial audit findings.
- Added local sample corpus notes for optional `Hello/Source/Insider` examples.
- Retargeted audit validation planning to UE5.8 after local `Hello.uproject` upgrade and successful compile.
- Implemented first-pass read-only scripts for query, audit manifest inspection, linting, learning extraction, and promotion preview.

### Learning Records

- `learning/inbox`: new unreviewed observations.
- `learning/reviewed`: reviewed observations not yet promoted.
- `learning/promoted`: observations promoted into canonical references.
- `learning/rejected`: project-specific or incorrect observations that should not enter canonical knowledge.

Promoted changes should record:

- source learning note path
- target files updated
- verification evidence or finding path
- whether the update is general UE behavior, version-specific behavior, or project convention
