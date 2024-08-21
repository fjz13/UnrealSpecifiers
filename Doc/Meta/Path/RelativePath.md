# RelativePath

- **功能描述：** 使得系统目录选择对话框的结果为当前运行exe的相对路径。
- **使用位置：** UPROPERTY
- **引擎模块：** Path Property
- **元数据类型：** bool
- **限制类型：** FDirectoryPath 
- **关联项：** [ContentDir](ContentDir/ContentDir.md)

当前目录为：D:\github\GitWorkspace\Hello\Binaries\Win64，就是exe所在的工作目录。选择的目录会被转换为相对路径。

```cpp
Directory = IFileManager::Get().ConvertToRelativePath(*Directory);
```
