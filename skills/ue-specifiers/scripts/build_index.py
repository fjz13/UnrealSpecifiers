"""Build generated indexes for the ue-specifiers skill."""

from __future__ import annotations

import argparse
import json
import re
from collections import Counter, defaultdict
from dataclasses import dataclass, field
from datetime import date
from pathlib import Path


SKILL_ROOT = Path(__file__).resolve().parents[1]
SOURCES_ROOT = SKILL_ROOT / "references" / "sources"
INDEX_ROOT = SKILL_ROOT / "references" / "indexes"
AUDIT_ROOT = SKILL_ROOT / "references" / "audits"


@dataclass
class SourceRecord:
    path: Path
    rel: str
    title: str
    symbol: str
    base_id: str
    id: str
    kind: str
    scope: str = ""
    category: str = ""
    source_status: str = "imported_from_unreal_specifiers"
    normalization_status: str = "normalized"
    target_ue_version: str = "UE5.8"
    summary: str = ""
    usage: str = ""
    has_code: bool = False
    has_images: bool = False
    has_test_section: bool = False
    has_principle_section: bool = False
    metadata_labels: list[str] = field(default_factory=list)


def posix_rel(path: Path, root: Path = SKILL_ROOT) -> str:
    return path.relative_to(root).as_posix()


def read_text(path: Path) -> str:
    return path.read_text(encoding="utf-8-sig")


def split_frontmatter(text: str) -> tuple[str, str]:
    if not text.startswith("---"):
        return "", text
    match = re.match(r"^---\s*\r?\n(.*?)\r?\n---\s*\r?\n?", text, re.S)
    if not match:
        return "", text
    return match.group(1), text[match.end() :]


def first_heading(text: str, fallback: str) -> str:
    _, body = split_frontmatter(text)
    match = re.search(r"^#\s+(.+?)\s*$", body, re.M)
    return match.group(1).strip() if match else fallback


def clean_inline_markdown(value: str) -> str:
    value = re.sub(r"!\[[^\]]*\]\([^)]+\)", "", value)
    value = re.sub(r"\[([^\]]+)\]\([^)]+\)", r"\1", value)
    value = re.sub(r"`([^`]+)`", r"\1", value)
    value = re.sub(r"\s+", " ", value)
    return value.strip(" \t\r\n。")


def clean_symbol(value: str) -> str:
    return value.strip().rstrip(" :：").strip()


def parse_legacy_metadata(text: str) -> dict[str, str]:
    metadata: dict[str, str] = {}
    for label, value in re.findall(r"^-\s+\*\*(.+?)：\*\*\s*(.+?)\s*$", text, re.M):
        metadata[label.strip()] = clean_inline_markdown(value.strip())
    for label, value in re.findall(r"^(Description|Feature|Value):\s*(.+?)\s*$", text, re.M):
        metadata[label.strip()] = clean_inline_markdown(value.strip())
    return metadata


def first_body_sentence(text: str, title: str) -> str:
    _, body = split_frontmatter(text)
    body = re.sub(r"^#\s+.+?$", "", body, count=1, flags=re.M)
    body = re.sub(r"^-\s+\*\*.+?$", "", body, flags=re.M)
    for line in body.splitlines():
        line = line.strip()
        if not line or line.startswith(("##", "```", "![", "|")):
            continue
        cleaned = clean_inline_markdown(line)
        if cleaned and cleaned != title:
            return cleaned[:120]
    return ""


def infer_summary_usage(
    text: str,
    title: str,
    kind: str,
    scope: str,
    category: str,
    metadata: dict[str, str],
) -> tuple[str, str]:
    summary = (
        metadata.get("功能描述")
        or metadata.get("Description")
        or first_body_sentence(text, title)
        or title
    )
    if len(summary) > 120:
        summary = summary[:117].rstrip() + "..."

    usage = metadata.get("使用位置") or metadata.get("Feature") or ""
    if not usage:
        if kind == "specifier":
            usage = " / ".join(item for item in [scope, category] if item)
        elif kind == "meta":
            usage = " / ".join(item for item in [scope, category] if item) or "meta=(...)"
        elif kind == "flag":
            usage = scope or category or "Reflection flags"
        else:
            usage = category or scope or "General"
    return summary, usage


def source_parts(path: Path) -> list[str]:
    rel = path.relative_to(SOURCES_ROOT)
    parts = list(rel.parts)
    parts[-1] = Path(parts[-1]).stem
    if len(parts) >= 2 and parts[-1].lower() == parts[-2].lower():
        parts.pop()
    return parts


def normalized_label(value: str) -> str:
    aliases = {
        "DetaisPanel": "DetailsPanel",
    }
    return aliases.get(value, value)


def path_id(kind: str, parts: list[str]) -> str:
    terms = [kind]
    if parts and parts[0].lower() in {"specifier", "meta", "flags"}:
        terms.extend(parts[1:])
    else:
        terms.extend(parts)
    return ".".join(term for term in terms if term)


def infer_record(path: Path, text: str, verified_statuses: dict[str, str]) -> SourceRecord:
    parts = source_parts(path)
    title = clean_symbol(first_heading(text, path.stem))
    top = parts[0] if parts else "Source"

    if top == "Specifier":
        kind = "specifier"
        symbol = title
        scope = parts[1] if len(parts) > 1 else ""
        category = normalized_label(parts[2]) if len(parts) > 2 else ""
        base_id = f"{scope}.{symbol}" if scope else f"specifier.{symbol}"
    elif top == "Meta":
        kind = "meta"
        symbol = title
        scope = parts[2] if len(parts) > 2 and parts[1] in {"Class", "Enum", "Function", "Interface", "Property", "Struct"} else ""
        category = normalized_label(parts[1]) if len(parts) > 1 else ""
        base_id = f"meta.{symbol}"
    elif top == "Flags":
        kind = "flag"
        scope = parts[1] if len(parts) > 1 else ""
        category = normalized_label(parts[1]) if len(parts) > 1 else ""
        symbol = scope if len(parts) == 2 else title
        title = symbol
        base_id = f"{scope}.{symbol}" if scope else f"flags.{symbol}"
    else:
        kind = "source"
        symbol = title
        scope = top
        category = ""
        base_id = f"source.{symbol}"

    source_status = verified_statuses.get(base_id, "imported_from_unreal_specifiers")
    metadata = parse_legacy_metadata(text)
    summary, usage = infer_summary_usage(text, title, kind, scope, category, metadata)
    metadata_labels = re.findall(r"^-\s+\*\*(.+?)：\*\*", text, re.M)

    return SourceRecord(
        path=path,
        rel=posix_rel(path),
        title=title,
        symbol=symbol,
        base_id=base_id,
        id=base_id,
        kind=kind,
        scope=scope,
        category=category,
        source_status=source_status,
        summary=summary,
        usage=usage,
        has_code="```" in text,
        has_images=bool(re.search(r"!\[[^\]]*\]\([^)]+\)", text)),
        has_test_section=bool(re.search(r"^##\s*(测试代码|示例代码|测试结果)", text, re.M)),
        has_principle_section=bool(re.search(r"^##\s*原理", text, re.M)),
        metadata_labels=metadata_labels,
    )


def load_verified_statuses() -> dict[str, str]:
    status_path = AUDIT_ROOT / "audit-status.jsonl"
    statuses: dict[str, str] = {}
    if not status_path.exists():
        return statuses
    for line in status_path.read_text(encoding="utf-8").splitlines():
        if not line.strip():
            continue
        item = json.loads(line)
        statuses[item["id"]] = item["status"]
    return statuses


def discover_records() -> list[SourceRecord]:
    verified_statuses = load_verified_statuses()
    records = [
        infer_record(path, read_text(path), verified_statuses)
        for path in sorted(SOURCES_ROOT.rglob("*.md"))
    ]
    counts = Counter(record.base_id for record in records)
    for record in records:
        if counts[record.base_id] > 1:
            parts = source_parts(record.path)
            record.id = path_id(record.kind, parts)
            record.source_status = verified_statuses.get(record.id, record.source_status)
    return records


def signal_text(record: SourceRecord) -> str:
    signals: list[str] = []
    if record.has_code:
        signals.append("code")
    if record.has_test_section:
        signals.append("test")
    if record.has_principle_section:
        signals.append("principle")
    if record.has_images:
        signals.append("media")
    if not signals:
        signals.append("text")
    return ", ".join(signals)


def table_cell(value: str) -> str:
    return value.replace("\n", " ").replace("|", "\\|").strip() or "-"


def render_sources_index(records: list[SourceRecord]) -> str:
    lines: list[str] = [
        "# Sources Index",
        "",
        "> Generated by `scripts/build_index.py`. This is a navigation catalog only; canonical explanations remain in `references/sources/`.",
        "",
    ]
    kind_counts = Counter(record.kind for record in records)
    lines.append(
        "Total source markdown files: "
        f"{len(records)}; "
        + ", ".join(f"{kind}={count}" for kind, count in sorted(kind_counts.items()))
    )
    lines.append("")

    groups: dict[tuple[str, str], list[SourceRecord]] = defaultdict(list)
    for record in records:
        group_name = record.scope or record.category or "General"
        groups[(record.kind, group_name)].append(record)

    for (kind, group_name), group_records in sorted(groups.items()):
        lines.append(f"## {kind.title()} - {group_name}")
        lines.append("")
        lines.append("| ID | Summary | Usage | Status | Signals | source_doc |")
        lines.append("|---|---|---|---|---|---|")
        for record in sorted(group_records, key=lambda item: item.id):
            lines.append(
                "| "
                f"`{record.id}` | "
                f"{table_cell(record.summary)} | "
                f"{table_cell(record.usage)} | "
                f"`{record.source_status}` | "
                f"{signal_text(record)} | "
                f"`{record.rel}` |"
            )
        lines.append("")

    return "\n".join(lines).rstrip() + "\n"


def write_sources_index(records: list[SourceRecord], dry_run: bool) -> Path:
    target = INDEX_ROOT / "sources.index.md"
    text = render_sources_index(records)
    if not dry_run:
        target.write_text(text, encoding="utf-8", newline="\n")
    return target


def main() -> int:
    parser = argparse.ArgumentParser(description="Build ue-specifiers indexes.")
    parser.add_argument("--dry-run", action="store_true", help="Preview work without writing files.")
    args = parser.parse_args()

    records = discover_records()
    target = write_sources_index(records, args.dry_run)
    prefix = "would write" if args.dry_run else "wrote"
    print(f"{prefix}: {posix_rel(target)}")
    print(f"source markdown files: {len(records)}")
    print(f"generated_at: {date.today().isoformat()}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
