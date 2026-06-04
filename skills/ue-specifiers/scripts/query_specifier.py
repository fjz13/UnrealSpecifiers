"""Query ue-specifiers indexes, recipes, pitfalls, and conflicts."""

import argparse
from pathlib import Path


SKILL_ROOT = Path(__file__).resolve().parents[1]
SEARCH_DIRS = [
    SKILL_ROOT / "references" / "indexes",
    SKILL_ROOT / "references" / "recipes",
    SKILL_ROOT / "references" / "pitfalls",
    SKILL_ROOT / "references" / "conflicts",
]


def iter_markdown_files():
    for directory in SEARCH_DIRS:
        if directory.exists():
            yield from sorted(directory.glob("*.md"))


def score_line(line: str, terms: list[str], macro: str | None, name: str | None) -> int:
    lowered = line.lower()
    score = 0
    for term in terms:
        if term.lower() in lowered:
            score += 2
    if macro and macro.lower() in lowered:
        score += 3
    if name and name.lower() in lowered:
        score += 5
    return score


def search(terms: list[str], macro: str | None, name: str | None, limit: int):
    results = []
    for path in iter_markdown_files():
        try:
            lines = path.read_text(encoding="utf-8").splitlines()
        except UnicodeDecodeError:
            lines = path.read_text(errors="ignore").splitlines()
        for lineno, line in enumerate(lines, 1):
            score = score_line(line, terms, macro, name)
            if score:
                rel = path.relative_to(SKILL_ROOT).as_posix()
                results.append((score, rel, lineno, line.strip()))
    results.sort(key=lambda item: (-item[0], item[1], item[2]))
    return results[:limit]


def main() -> int:
    parser = argparse.ArgumentParser(description="Query ue-specifiers indexes and recipes.")
    parser.add_argument("query", nargs="*", help="Specifier, meta, or search text.")
    parser.add_argument("--macro", help="Filter by macro, such as UPROPERTY.")
    parser.add_argument("--name", help="Filter by specifier or meta name.")
    parser.add_argument("--limit", type=int, default=20, help="Maximum matches to print.")
    args = parser.parse_args()

    terms = list(args.query)
    if args.name:
        terms.append(args.name)
    if args.macro:
        terms.append(args.macro)
    if not terms:
        parser.error("provide a query term, --macro, or --name")

    matches = search(terms, args.macro, args.name, args.limit)
    if not matches:
        print("No matches.")
        return 1

    for score, rel, lineno, snippet in matches:
        print(f"{rel}:{lineno}: score={score}: {snippet}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
