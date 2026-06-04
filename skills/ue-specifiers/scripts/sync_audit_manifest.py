"""Sync the semantic audit manifest from normalized source frontmatter."""

from __future__ import annotations

import argparse
import json
import re
from collections import Counter
from pathlib import Path

from build_index import AUDIT_ROOT, SKILL_ROOT, discover_records


MANIFEST = AUDIT_ROOT / "audit-manifest.jsonl"
TARGET_VERSION = "UE5.8"

HIGH_RISK_NAMES = {
    "AdvancedDisplay",
    "AllowPrivateAccess",
    "AutoCreateRefTerm",
    "ClampMax",
    "ClampMin",
    "DefaultToSelf",
    "DisplayName",
    "EditConditionHides",
    "ExpandEnumAsExecs",
    "HidePin",
    "InlineEditConditionToggle",
    "ShortToolTip",
    "ShortTooltip",
    "ToolTip",
    "UIMax",
    "UIMin",
}

P0_SPECIFIER_CATEGORIES = {
    "Blueprint",
    "Config",
    "DetailsPanel",
    "Instance",
    "Network",
    "Serialization",
}

P1_SPECIFIER_SCOPES = {
    "UCLASS",
    "UENUM",
    "UINTERFACE",
    "UPARAM",
    "UPROPERTY",
    "USTRUCT",
}

P1_META_CATEGORIES = {
    "Blueprint",
    "Config",
    "DetailsPanel",
    "Numeric",
    "Pin",
}

P2_META_CATEGORIES = {
    "Actor",
    "AnimationGraph",
    "Asset",
    "Component",
    "Container",
    "Development",
    "TypePicker",
    "Widget",
}

COLD_PATTERNS = re.compile(
    r"(Deprecated|Experimental|EarlyAccess|Internal|Hidden|Debug|UHT|DocumentationPolicy|CompilerGenerated)",
    re.IGNORECASE,
)


def read_manifest(path: Path = MANIFEST) -> dict[str, dict]:
    rows: dict[str, dict] = {}
    if not path.exists():
        return rows
    for line in path.read_text(encoding="utf-8").splitlines():
        if not line.strip():
            continue
        row = json.loads(line)
        rows[row["id"]] = row
    return rows


def safe_finding_name(item_id: str) -> str:
    return re.sub(r"[^A-Za-z0-9_.-]+", "_", item_id)


def infer_macro(record) -> str:
    candidates = [
        "UCLASS",
        "USTRUCT",
        "UENUM",
        "UINTERFACE",
        "UPROPERTY",
        "UFUNCTION",
        "UPARAM",
        "UMETA",
    ]
    if record.kind == "specifier":
        return record.scope or "specifier"
    usage = record.usage or ""
    found = [candidate for candidate in candidates if candidate in usage]
    if len(found) == 1:
        return found[0]
    if len(found) > 1:
        return "multiple"
    return record.scope or "meta"


def infer_priority(record, existing: dict | None) -> str:
    if existing and existing.get("priority"):
        return existing["priority"]

    text = f"{record.id} {record.rel} {record.category} {record.symbol}"
    if COLD_PATTERNS.search(text):
        return "P3"

    if record.kind == "specifier":
        if record.scope in {"UPROPERTY", "UFUNCTION"} and record.category in P0_SPECIFIER_CATEGORIES:
            return "P0"
        if record.scope in P1_SPECIFIER_SCOPES:
            return "P1"
        return "P2"

    if record.kind == "meta":
        if record.symbol in HIGH_RISK_NAMES:
            return "P0"
        if record.category in P1_META_CATEGORIES:
            return "P1"
        if record.category in P2_META_CATEGORIES:
            return "P2"
        return "P3"

    return "P3"


def manifest_row(record, existing: dict | None) -> dict:
    status = existing.get("status") if existing else record.source_status
    if status not in {"verified_UE5.8", "changed_in_version", "removed_or_deprecated"}:
        status = "audit_pending"

    finding_path = ""
    if existing and existing.get("finding_path"):
        finding_path = existing["finding_path"]
    elif status == "verified_UE5.8":
        finding_path = "references/audits/findings/backfilled-verification-needed.md"
    else:
        finding_path = f"references/audits/findings/{safe_finding_name(record.id)}.md"

    return {
        "id": record.id,
        "kind": record.kind,
        "macro": infer_macro(record),
        "name": record.symbol,
        "source_doc": record.rel,
        "priority": infer_priority(record, existing),
        "status": status,
        "target_versions": [TARGET_VERSION],
        "finding_path": finding_path,
    }


def sort_key(row: dict) -> tuple:
    priority_order = {"P0": 0, "P1": 1, "P2": 2, "P3": 3}
    kind_order = {"specifier": 0, "meta": 1}
    return (
        priority_order.get(row.get("priority"), 9),
        kind_order.get(row.get("kind"), 9),
        row.get("macro", ""),
        row.get("id", ""),
    )


def main() -> int:
    parser = argparse.ArgumentParser(description="Sync audit manifest with source specifier/meta docs.")
    parser.add_argument("--dry-run", action="store_true", help="Print counts without writing.")
    args = parser.parse_args()

    existing = read_manifest()
    records = [record for record in discover_records() if record.kind in {"specifier", "meta"}]
    rows = [manifest_row(record, existing.get(record.id)) for record in records]
    rows.sort(key=sort_key)

    if not args.dry_run:
        MANIFEST.write_text(
            "\n".join(json.dumps(row, ensure_ascii=False) for row in rows) + "\n",
            encoding="utf-8",
            newline="\n",
        )

    counts = Counter(row["status"] for row in rows)
    priorities = Counter(row["priority"] for row in rows)
    preserved_verified = sum(
        1
        for row in rows
        if row["status"] == "verified_UE5.8"
        and existing.get(row["id"], {}).get("status") == "verified_UE5.8"
    )
    print(f"manifest: {MANIFEST.relative_to(SKILL_ROOT).as_posix()}")
    print(f"source specifier/meta records: {len(records)}")
    print(f"manifest rows: {len(rows)}")
    for key, count in sorted(counts.items()):
        print(f"status.{key}: {count}")
    for key, count in sorted(priorities.items()):
        print(f"priority.{key}: {count}")
    print(f"preserved_verified: {preserved_verified}")
    print(f"mode: {'dry-run' if args.dry_run else 'write'}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
