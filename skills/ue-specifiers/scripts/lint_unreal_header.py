"""Lint obvious Unreal Engine C++ header specifier mistakes."""

import argparse
import re
from pathlib import Path


EDIT_SPECIFIERS = {"EditAnywhere", "EditDefaultsOnly", "EditInstanceOnly"}
VISIBLE_SPECIFIERS = {"VisibleAnywhere", "VisibleDefaultsOnly", "VisibleInstanceOnly"}
KNOWN_META = {
    "DisplayName",
    "ToolTip",
    "ShortToolTip",
    "ClampMin",
    "ClampMax",
    "UIMin",
    "UIMax",
    "EditCondition",
    "EditConditionHides",
    "InlineEditConditionToggle",
    "HideEditConditionToggle",
    "AllowPrivateAccess",
    "WorldContext",
    "HidePin",
    "DefaultToSelf",
    "AutoCreateRefTerm",
    "AdvancedDisplay",
    "ExpandEnumAsExecs",
}


def split_args(arg_text: str) -> list[str]:
    return [part.strip() for part in re.split(r",(?![^()]*\))", arg_text) if part.strip()]


def extract_meta_keys(arg_text: str) -> set[str]:
    match = re.search(r"meta\s*=\s*\((.*?)\)", arg_text)
    if not match:
        return set()
    keys = set()
    for part in split_args(match.group(1)):
        key = part.split("=", 1)[0].strip()
        if key:
            keys.add(key)
    return keys


def collect_functions(text: str) -> set[str]:
    return set(re.findall(r"\bvoid\s+(OnRep_\w+)\s*\(", text))


def lint_file(path: Path) -> list[str]:
    text = path.read_text(encoding="utf-8", errors="ignore")
    lines = text.splitlines()
    functions = collect_functions(text)
    findings = []

    for index, line in enumerate(lines, 1):
        prop = re.search(r"UPROPERTY\s*\((.*?)\)", line)
        if prop:
            args = prop.group(1)
            tokens = set(split_args(args))
            edit = tokens & EDIT_SPECIFIERS
            visible = tokens & VISIBLE_SPECIFIERS
            if edit and visible:
                findings.append(f"{path}:{index}: UPROPERTY mixes Edit* and Visible*: {sorted(edit | visible)}")
            if "BlueprintReadOnly" in tokens and "BlueprintReadWrite" in tokens:
                findings.append(f"{path}:{index}: UPROPERTY mixes BlueprintReadOnly and BlueprintReadWrite")
            if ("BlueprintReadOnly" in tokens or "BlueprintReadWrite" in tokens) and "Category" not in args:
                findings.append(f"{path}:{index}: Blueprint-exposed UPROPERTY is missing Category")
            rep = re.search(r"ReplicatedUsing\s*=\s*(\w+)", args)
            if rep and rep.group(1) not in functions:
                findings.append(f"{path}:{index}: ReplicatedUsing references missing function {rep.group(1)}")
            for key in extract_meta_keys(args):
                if key not in KNOWN_META:
                    findings.append(f"{path}:{index}: unknown or unindexed meta key: {key}")

        func = re.search(r"UFUNCTION\s*\((.*?)\)", line)
        if func:
            args = func.group(1)
            tokens = set(split_args(args))
            if "BlueprintCallable" in tokens and "BlueprintPure" in tokens:
                findings.append(f"{path}:{index}: UFUNCTION mixes BlueprintCallable and BlueprintPure")
            for key in extract_meta_keys(args):
                if key not in KNOWN_META and not key.startswith("CPP_Default_"):
                    findings.append(f"{path}:{index}: unknown or unindexed meta key: {key}")

    return findings


def main() -> int:
    parser = argparse.ArgumentParser(description="Lint Unreal Engine C++ header specifier usage.")
    parser.add_argument("headers", nargs="*", help="Header files to inspect.")
    args = parser.parse_args()
    if not args.headers:
        parser.error("provide at least one header file")

    all_findings = []
    for header in args.headers:
        path = Path(header)
        if not path.exists():
            all_findings.append(f"{path}: file not found")
            continue
        all_findings.extend(lint_file(path))

    if not all_findings:
        print("No obvious specifier issues found.")
        return 0
    for finding in all_findings:
        print(finding)
    return 1


if __name__ == "__main__":
    raise SystemExit(main())
