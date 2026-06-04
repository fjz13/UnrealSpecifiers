"""Inspect ue-specifiers audit manifest."""

import argparse
import json
from collections import Counter
from pathlib import Path


SKILL_ROOT = Path(__file__).resolve().parents[1]
MANIFEST = SKILL_ROOT / "references" / "audits" / "audit-manifest.jsonl"


def read_manifest() -> list[dict]:
    if not MANIFEST.exists():
        raise SystemExit(f"Missing manifest: {MANIFEST}")
    rows = []
    for lineno, line in enumerate(MANIFEST.read_text(encoding="utf-8").splitlines(), 1):
        if not line.strip():
            continue
        try:
            rows.append(json.loads(line))
        except json.JSONDecodeError as exc:
            raise SystemExit(f"{MANIFEST}:{lineno}: invalid JSONL: {exc}") from exc
    return rows


def filter_rows(rows: list[dict], priority: str | None, status: str | None) -> list[dict]:
    if priority:
        rows = [row for row in rows if row.get("priority") == priority]
    if status:
        rows = [row for row in rows if row.get("status") == status]
    return rows


def finding_exists(row: dict) -> bool:
    path = row.get("finding_path")
    return bool(path and (SKILL_ROOT / path).exists())


def evidence_expected(row: dict) -> bool:
    return row.get("status") not in {"audit_pending", "needs_manual_check"}


def print_row(row: dict) -> None:
    marker = "finding" if finding_exists(row) else "missing-finding"
    print(f"{row['priority']} {row['status']} {row['id']} [{marker}] {row['source_doc']}")


def main() -> int:
    parser = argparse.ArgumentParser(description="Inspect ue-specifiers audit manifest.")
    parser.add_argument("command", nargs="?", default="status", choices=["list", "next", "status"], help="Audit command.")
    parser.add_argument("--priority", help="Filter by priority, such as P0.")
    parser.add_argument("--status", help="Filter by audit status.")
    parser.add_argument("--limit", type=int, default=10, help="Maximum items to show.")
    args = parser.parse_args()

    rows = read_manifest()
    filtered = filter_rows(rows, args.priority, args.status)

    if args.command == "status":
        print(f"manifest: {MANIFEST.relative_to(SKILL_ROOT).as_posix()}")
        print(f"total: {len(rows)}")
        for key, count in sorted(Counter(row.get("status", "unknown") for row in rows).items()):
            print(f"status.{key}: {count}")
        evidence_rows = [row for row in rows if evidence_expected(row)]
        print(f"evidence_expected: {len(evidence_rows)}")
        print(f"with_evidence: {sum(1 for row in evidence_rows if finding_exists(row))}")
        print(f"missing_evidence: {sum(1 for row in evidence_rows if not finding_exists(row))}")
        return 0

    if args.command == "next":
        filtered = [row for row in filtered if row.get("status") in {"audit_pending", "needs_manual_check"}]

    for row in filtered[: args.limit]:
        print_row(row)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
