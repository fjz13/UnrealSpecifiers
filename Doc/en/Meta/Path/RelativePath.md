# RelativePath

- **Function Description:** Ensures that the result of the system directory selection dialog is the relative path to the current executing exe.
- **Usage Location:** UPROPERTY
- **Engine Module:** Path Property
- **Metadata Type:** bool
- **Restriction Type:** FDirectoryPath
- **Associated Item:** [ContentDir](ContentDir/ContentDir.md)

The current directory is: D:\github\GitWorkspace\Hello\Binaries\Win64, which is the working directory of the exe. Any selected directory will be converted to a relative path.

```cpp
Directory = IFileManager::Get().ConvertToRelativePath(*Directory);
```