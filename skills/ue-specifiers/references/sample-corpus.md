# Optional Local Sample Corpus

The canonical published skill does not depend on local machine paths. During local development, this machine also has a historical Unreal specifier test/sample project. `Hello.uproject` is upgraded to UE5.8 and has compiled successfully on this machine:

```text
D:/github/GitWorkspace/Hello/Source/Insider
```

Use this path only when it exists. Treat it as a sample corpus, not as canonical truth.

`Insider` is not an automation test suite. It contains sample and comparison code that should be opened in the UE editor and inspected through Details Panel, Blueprint, asset, or runtime behavior as appropriate.

## Suggested Use

- Search it for concrete examples before writing learning notes.
- Use `bat/build-hello.bat` before relying on samples for UE5.8 validation.
- Use `bat/editor-hello.bat` to open the project for visual behavior comparison.
- Use `bat/inspect-hello-log.bat` after editor observation to extract recent errors and reflection/specifier-related log markers.
- Compare sample code against `references/sources` and audit findings.
- Record sample-derived lessons in `references/learning/inbox/`.
- Mark sample-derived notes as `project_observation_only`, `project_convention`, or `uncertain` unless verified by UE source or a repro.

## Known Useful Areas

| Topic | Local sample path |
|---|---|
| EditCondition expressions and inline toggles | `Property/Editor/MyProperty_EditCondition.h` |
| SaveGame archive behavior | `Property/Serialization/MyProperty_SaveGame.cpp` |
| Instanced object property flags | `Property/Object/MyProperty_Instanced.h` |
| WorldContext function library patterns | `Function/MyFunction_WorldContext.h` |
| ToolTip and ShortToolTip examples | `Any/ToolTip_Test.h` |

## Rule

Do not hard-require this path in scripts or published workflows. External users should be able to use `skills/ue-specifiers` without the `Hello` project.

