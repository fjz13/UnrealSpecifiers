# RelativeToGameContentDir

Usage: UPROPERTY
Feature: Editor
Type: bool
Description: 使得系统目录选择对话框的结果为相对Content的相对路径。
LimitedType: FDirectoryPath 
Status: Linked
Group: Path Property
Parent item: ContentDir (ContentDir.md)

限制目录选择的结果必须是Conent目录或其子目录，否则会弹出报错信息。转换的逻辑为把左侧的Content路径裁切掉。

```cpp
Directory.RightChopInline(AbsoluteGameContentDir.Len(), EAllowShrinking::No);
```