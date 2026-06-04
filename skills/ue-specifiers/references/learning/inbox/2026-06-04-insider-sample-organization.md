# Learning Note: Insider Sample Organization Convention

## Source Project

- Hello / Insider sample corpus

## Date

- 2026-06-04

## Related Symbols

- `UPROPERTY`
- `UFUNCTION`
- `meta=(...)`

## Problem

- Need a repeatable way to find concrete comparison examples for specifiers and metadata without relying on AI memory.

## Before

```text
Search the whole project for a specifier name.
```

## After

```text
D:/github/GitWorkspace/Hello/Source/Insider/Property/Editor/MyProperty_EditCondition.h
D:/github/GitWorkspace/Hello/Source/Insider/Property/Serialization/MyProperty_SaveGame.cpp
D:/github/GitWorkspace/Hello/Source/Insider/Property/Object/MyProperty_Instanced.h
D:/github/GitWorkspace/Hello/Source/Insider/Function/MyFunction_WorldContext.h
```

## Result

- The Insider sample corpus is organized by macro/domain and can provide targeted examples for learning notes and audit repro design.
- `Hello.uproject` is upgraded to UE5.8 and compiles on this machine, so the corpus is a useful starting point for UE5.8 validation work.

## Lesson

- For local development, search `Hello/Source/Insider` before drafting sample-based explanations or UE5.8 validation candidates. Keep the published skill independent from this local path.

## Generality

- project_convention

## Confidence

- high

## Needs Verification

- no

## Candidate Updates

- references/sample-corpus.md

## Do Not Promote Before

- Do not promote as general Unreal behavior; this is only a local sample organization convention.
