"""Extract candidate ue-specifiers learning notes from diffs."""

import argparse
from datetime import date
from pathlib import Path


TRIGGERS = ("UCLASS", "USTRUCT", "UENUM", "UINTERFACE", "UPROPERTY", "UFUNCTION", "UPARAM", "UMETA", "meta=")


def candidate_lines(diff_text: str) -> tuple[list[str], list[str]]:
    before = []
    after = []
    for line in diff_text.splitlines():
        if not line.startswith(("+", "-")) or line.startswith(("+++", "---")):
            continue
        if any(trigger in line for trigger in TRIGGERS):
            if line.startswith("-"):
                before.append(line)
            else:
                after.append(line)
    return before, after


def render_note(project: str, diff_file: str, before: list[str], after: list[str]) -> str:
    before_body = "\n".join(before[:40]) if before else "(no removed reflection macro lines found)"
    after_body = "\n".join(after[:40]) if after else "(no added reflection macro lines found)"
    return f"""# Learning Note: Candidate Reflection Macro Change

## Source Project

- {project}

## Date

- {date.today().isoformat()}

## Related Symbols

- uncertain

## Problem

- Candidate change touches Unreal reflection macros or metadata.

## Before

```diff
{before_body}
```

## After

```diff
{after_body}
```

## Result

- Not verified by this script.

## Lesson

- Review the diff manually and decide whether it is general Unreal behavior, version-specific behavior, or project convention.

## Generality

- uncertain

## Confidence

- low

## Needs Verification

- yes

## Candidate Updates

- references/recipes/
- references/pitfalls/
- references/conflicts/
- references/indexes/

## Do Not Promote Before

- Manual review of `{diff_file}`.
"""


def main() -> int:
    parser = argparse.ArgumentParser(description="Extract candidate learning notes from a patch.")
    parser.add_argument("--diff-file", required=True, help="Diff file to inspect.")
    parser.add_argument("--project", required=True, help="Source project name.")
    args = parser.parse_args()

    path = Path(args.diff_file)
    if not path.exists():
        raise SystemExit(f"Diff file not found: {path}")
    text = path.read_text(encoding="utf-8", errors="ignore")
    before, after = candidate_lines(text)
    print(render_note(args.project, str(path), before, after))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
