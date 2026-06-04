# Learning Note: EditCondition Expressions In Insider Samples

## Source Project

- Hello / Insider sample corpus

## Date

- 2026-06-04

## Related Symbols

- `meta.EditCondition`
- `meta.EditConditionHides`
- `meta.InlineEditConditionToggle`
- `meta.HideEditConditionToggle`

## Problem

- Need concrete examples showing simple bool conditions, negated conditions, expression conditions, hidden conditional fields, and inline condition toggles.

## Before

```cpp
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)
bool MyBool;
```

## After

```cpp
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property, meta = (EditCondition = "MyBool"))
int32 MyInt_EditCondition = 123;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PropertyExpression, meta = (EditCondition = "(MyFirstInt+MySecondInt)==500"))
int32 MyInt_EditConditionExpression = 123;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InlineEditConditionToggle, meta = (InlineEditConditionToggle))
bool MyBool_Inline;
```

## Result

- Local sample file demonstrates multiple EditCondition forms in one class.
- `Hello.uproject` is upgraded to UE5.8 and compiles on this machine.
- This note has not verified the specific Details Panel behavior by running the editor workflow or checking UE source.

## Lesson

- `EditCondition` examples should include both simple bool and expression forms, but expression behavior must remain version-sensitive until audited.

## Generality

- uncertain

## Confidence

- medium

## Needs Verification

- yes

## Candidate Updates

- references/recipes/edit-condition.md
- references/audits/findings/meta.EditCondition.md

## Do Not Promote Before

- Verify behavior in UE5.8 or tie the note to a completed audit finding.

## Source Path

- `D:/github/GitWorkspace/Hello/Source/Insider/Property/Editor/MyProperty_EditCondition.h`
