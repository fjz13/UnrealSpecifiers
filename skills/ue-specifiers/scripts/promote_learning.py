"""Preview promotion of reviewed ue-specifiers learning notes."""

import argparse
from pathlib import Path


CANDIDATE_MARKERS = {
    "references/recipes/": "recipe update",
    "references/pitfalls/": "pitfall update",
    "references/conflicts/": "conflict update",
    "references/indexes/": "index update",
    "references/sample-corpus.md": "sample corpus update",
}


def main() -> int:
    parser = argparse.ArgumentParser(description="Preview promotion of a reviewed learning note.")
    parser.add_argument("note", help="Reviewed learning note path.")
    args = parser.parse_args()

    path = Path(args.note)
    if not path.exists():
        raise SystemExit(f"Learning note not found: {path}")
    text = path.read_text(encoding="utf-8", errors="ignore")
    print(f"Promotion preview for: {path}")
    print("This script is read-only and does not modify canonical references.")
    found = False
    for marker, label in CANDIDATE_MARKERS.items():
        if marker in text:
            print(f"- Candidate {label}: {marker}")
            found = True
    if not found:
        print("- No explicit candidate update paths found; inspect note manually.")
    if "Needs Verification\n\n- yes" in text:
        print("- Blocker: note still says Needs Verification = yes.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
