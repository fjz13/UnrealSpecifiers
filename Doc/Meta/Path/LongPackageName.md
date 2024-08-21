# LongPackageName

- **功能描述：** 使用UE的风格来选择Content以及子目录，或者把文件路径转换为长包名。
- **使用位置：** UPROPERTY
- **引擎模块：** Path Property
- **元数据类型：** bool
- **限制类型：** FDirectoryPath，FFilePath
- **常用程度：** ★★★

LongPackageName可以同时用在FDirectoryPath和FFilePath，都限制选取范围在Content目录内。

用在FDirectoryPath上的时候，限制目录为Content或其子目录。

用在FFilePath的时候，限制选择范围为Content里的资产，最终把选取的文件路径转换为“/Game/ObjectPath”这种对象的路径名。
