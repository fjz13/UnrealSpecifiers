# RelativeToGameContentDir

- **Function Description:** Ensures that the result of the system directory selection dialog is a relative path to the Content directory.
- **Usage Location:** UPROPERTY
- **Engine Module:** Path Property
- **Metadata Type:** bool
- **Restriction Type:** FDirectoryPath
- **Associated Item:** [ContentDir](ContentDir/ContentDir.md)

Restricts the directory selection result to the Content directory or its subdirectories; otherwise, an error message will be displayed. The logic for conversion involves truncating the left part of the Content path.

```cpp
Directory.RightChopInline(AbsoluteGameContentDir.Len(), EAllowShrinking::No);
```