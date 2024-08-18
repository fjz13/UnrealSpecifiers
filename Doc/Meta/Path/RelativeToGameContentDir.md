# RelativeToGameContentDir

功能描述: 使得系统目录选择对话框的结果为相对Content的相对路径。
使用位置: UPROPERTY
Feature: Editor
引擎模块: Path Property
元数据类型: bool
限制类型: FDirectoryPath 
Status: Linked
Parent item: ContentDir (ContentDir.md)

限制目录选择的结果必须是Conent目录或其子目录，否则会弹出报错信息。转换的逻辑为把左侧的Content路径裁切掉。

```cpp
Directory.RightChopInline(AbsoluteGameContentDir.Len(), EAllowShrinking::No);
```