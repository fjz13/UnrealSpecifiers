# RelativePath

Usage: UPROPERTY
Feature: Editor
Type: bool
Description: 使得系统目录选择对话框的结果为当前运行exe的相对路径。
LimitedType: FDirectoryPath 
Status: Linked
Group: Path Property
Parent item: ContentDir (ContentDir.md)

当前目录为：D:\github\GitWorkspace\Hello\Binaries\Win64，就是exe所在的工作目录。选择的目录会被转换为相对路径。

```cpp
Directory = IFileManager::Get().ConvertToRelativePath(*Directory);
```