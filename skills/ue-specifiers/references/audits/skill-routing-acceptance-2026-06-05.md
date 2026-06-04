# Skill Routing Acceptance - 2026-06-05

Scope: verify that `ue-specifiers` can route common and risky UE specifier/meta queries after the UE5.8 audit pass.

Checks:

- `BlueprintCallable`: routes to `UFUNCTION.BlueprintCallable` in `sources.index.md`; status `verified_UE5.8`; recommend normally for Blueprint callable functions.
- `BindWidget`: routes to `meta.BindWidget`; status `verified_UE5.8`; recommend only for UMG/UserWidget binding scenarios.
- `EditCondition`: routes to recipe `recipes/edit-condition.md` and source `meta.EditCondition`; status `verified_UE5.8`; recommend with `EditConditionHides` / `InlineEditConditionToggle` caveats.
- `OnEvaluate`: routes to `meta.OnEvaluate`; status `removed_or_deprecated`; do not recommend for new animation graph code.
- `MaterialNewHLSLGenerator`: routes to `meta.MaterialNewHLSLGenerator`; status `changed_in_version`; do not recommend as a UE5.8 metadata key.
- `TakeRecorderDisplayName`: routes to `meta.TakeRecorderDisplayName`; status `changed_in_version`; do not recommend as a UE5.8 metadata key.
- `AllowedParamType`: routes to `meta.AllowedParamType`; status `changed_in_version`; do not recommend as a UE5.8 metadata key without fresh source evidence.
- `Without_UCLASS`: routes to `UCLASS.Without_UCLASS`; status `verified_UE5.8`; treat as a negative/reference page, not a real specifier.

Additional release-readiness routing checks:

- `ReplicatedUsing`: routes to `UPROPERTY.ReplicatedUsing` and `recipes/replicated-property.md`; status `verified_UE5.8`; recommend for replicated property notify callbacks with `GetLifetimeReplicatedProps`.
- `Instanced`: routes to `UPROPERTY.Instanced` and `recipes/instanced-subobject.md`; status `verified_UE5.8`; recommend only for inline UObject subobject ownership/editing scenarios.
- `AllowedClasses`: routes to `meta.AllowedClasses`; status `verified_UE5.8`; recommend for type/object picker filtering with class constraints.
- Cold-start routing assertion script checked 12 representative rows across `sources.index.md`, `specifiers.index.md`, `metas.index.md`, and `recipes.index.md`; problems: 0.

Issues found:

- `SKILL.md` did not define recommendation gates for `changed_in_version` or `removed_or_deprecated`, so a future agent could cite them as normal options.
- `SKILL.md` treated focused indexes and generated `sources.index.md` as peers; focused indexes can be intentionally smaller and must not override source/frontmatter status.
- `metas.index.md` had stale statuses and non-canonical IDs for `DisplayName` and `ShortTooltip`.
- `specifiers.index.md` had stale statuses for curated entries.

Fixes made:

- Added status-gate rules to `SKILL.md`.
- Clarified that `sources.index.md` and source frontmatter are authoritative for routing/status conflicts.
- Clarified that indexes are read-only during ordinary usage but may be regenerated or synchronized during explicit audit/maintenance work.
- Synced curated index statuses for current entries.
- Changed `metas.index.md` entries to canonical IDs `meta.Blueprint.DisplayName` and `meta.ShortTooltip`.

Residual risk:

- `metas.index.md` and `specifiers.index.md` are curated summaries, not complete catalogs. Future agents should use them for quick orientation only and rely on `sources.index.md` for full routing.
- Some `verified_UE5.8` rows are internal, plugin-specific, NoExportTypes-only, or negative-reference pages. Status means the source path was verified, not that the item is suitable for ordinary project code.
- Reflection flag pages were removed from the publishable `ue-specifiers` skill. The completed semantic audit scope is specifiers and metadata.
