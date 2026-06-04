"""Normalize source markdown files and record source-level audit progress."""

from __future__ import annotations

import argparse
import json
from dataclasses import asdict
from datetime import date
from pathlib import Path

from build_index import (
    AUDIT_ROOT,
    SKILL_ROOT,
    discover_records,
    posix_rel,
    read_text,
    split_frontmatter,
    write_sources_index,
)


NORMALIZED_AT = "2026-06-04"


def yaml_scalar(value: str) -> str:
    return json.dumps(value, ensure_ascii=False)


def render_frontmatter(record) -> str:
    fields = [
        ("title", record.title),
        ("id", record.id),
        ("kind", record.kind),
        ("symbol", record.symbol),
        ("scope", record.scope),
        ("category", record.category),
        ("source_status", record.source_status),
        ("target_ue_version", record.target_ue_version),
        ("normalization_status", record.normalization_status),
        ("normalized_at", NORMALIZED_AT),
        ("summary", record.summary),
        ("usage", record.usage),
    ]
    lines = ["---"]
    for key, value in fields:
        if value:
            lines.append(f"{key}: {yaml_scalar(str(value))}")
    lines.append("---")
    return "\n".join(lines) + "\n\n"


def normalized_text(record) -> str:
    text = read_text(record.path)
    _, body = split_frontmatter(text)
    return render_frontmatter(record) + body.lstrip()


def status_record(record) -> dict:
    return {
        "id": record.id,
        "kind": record.kind,
        "symbol": record.symbol,
        "scope": record.scope,
        "category": record.category,
        "source_doc": record.rel,
        "source_status": record.source_status,
        "summary": record.summary,
        "usage": record.usage,
        "normalization_status": record.normalization_status,
        "target_ue_version": record.target_ue_version,
        "normalized_at": NORMALIZED_AT,
        "checks": {
            "frontmatter": True,
            "has_code": record.has_code,
            "has_test_section": record.has_test_section,
            "has_principle_section": record.has_principle_section,
            "has_media": record.has_images,
            "legacy_metadata_labels": record.metadata_labels,
        },
    }


def write_status(records, dry_run: bool) -> tuple[Path, bool]:
    target = AUDIT_ROOT / "source-normalization-status.jsonl"
    lines = [json.dumps(status_record(record), ensure_ascii=False) for record in records]
    text = "\n".join(lines) + "\n"
    changed = not target.exists() or target.read_text(encoding="utf-8") != text
    if changed and not dry_run:
        target.write_text(text, encoding="utf-8", newline="\n")
    return target, changed


def write_summary(records, dry_run: bool) -> tuple[Path, bool]:
    target = AUDIT_ROOT / "source-normalization-2026-06-04.md"
    by_kind: dict[str, int] = {}
    with_code = with_test = with_principle = with_media = 0
    for record in records:
        by_kind[record.kind] = by_kind.get(record.kind, 0) + 1
        with_code += int(record.has_code)
        with_test += int(record.has_test_section)
        with_principle += int(record.has_principle_section)
        with_media += int(record.has_images)

    lines = [
        "# Source Normalization Audit - 2026-06-04",
        "",
        "Target version label: `UE5.8`.",
        "",
        "Scope:",
        "",
        f"- Normalized Markdown source documents: {len(records)}",
        "- Added machine-readable frontmatter to each source document.",
        "- Regenerated `references/indexes/sources.index.md` as a navigation-only catalog.",
        "- Recorded per-source progress in `references/audits/source-normalization-status.jsonl`.",
        "",
        "Important distinction:",
        "",
        "- `normalization_status=normalized` means the document has the standard source metadata block.",
        "- `source_status=verified_UE5.8` only applies to items already backed by semantic audit evidence.",
        "- Future imported items should remain `imported_from_unreal_specifiers` until semantic UE5.8 evidence is added.",
        "",
        "Counts:",
        "",
    ]
    for kind, count in sorted(by_kind.items()):
        lines.append(f"- {kind}: {count}")
    lines.extend(
        [
            f"- with code blocks: {with_code}",
            f"- with test/example sections: {with_test}",
            f"- with principle sections: {with_principle}",
            f"- with media references: {with_media}",
            "",
            "Next maintenance pass:",
            "",
            "- Re-run `references/audits/audit-manifest.jsonl` sync when source documents are added or removed.",
            "- Promote verified findings into source documents only when the finding changes or clarifies the canonical explanation.",
            "- Keep full explanations in `references/sources/`; keep indexes concise.",
            "",
        ]
    )
    text = "\n".join(lines)
    changed = not target.exists() or target.read_text(encoding="utf-8") != text
    if changed and not dry_run:
        target.write_text(text, encoding="utf-8", newline="\n")
    return target, changed


def main() -> int:
    parser = argparse.ArgumentParser(description="Normalize ue-specifiers source documents.")
    parser.add_argument("--dry-run", action="store_true", help="Preview work without writing files.")
    args = parser.parse_args()

    records = discover_records()
    changed = 0
    for record in records:
        new_text = normalized_text(record)
        if new_text != read_text(record.path):
            changed += 1
            if not args.dry_run:
                record.path.write_text(new_text, encoding="utf-8", newline="\n")

    status_path, status_changed = write_status(records, args.dry_run)
    summary_path, summary_changed = write_summary(records, args.dry_run)
    index_path, index_changed = write_sources_index(records, args.dry_run)

    pending_prefix = "would update" if args.dry_run else "updated"
    clean_prefix = "up to date" if args.dry_run else "unchanged"
    print(f"{pending_prefix if changed else clean_prefix} source markdown files: {changed}")
    print(f"{pending_prefix if status_changed else clean_prefix}: {posix_rel(status_path)}")
    print(f"{pending_prefix if summary_changed else clean_prefix}: {posix_rel(summary_path)}")
    print(f"{pending_prefix if index_changed else clean_prefix}: {posix_rel(index_path)}")
    print(f"source markdown files scanned: {len(records)}")
    print(f"run_date: {date.today().isoformat()}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
