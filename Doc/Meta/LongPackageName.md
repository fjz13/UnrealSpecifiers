# LongPackageName

Description: 使用UE的风格来选择Content以及子目录，或者把文件路径转换为长包名。
Usage: UPROPERTY
Feature: Editor
Group: Path Property
Type: bool
LimitedType: FDirectoryPath，FFilePath
Status: Linked

LongPackageName可以同时用在FDirectoryPath和FFilePath，都限制选取范围在Content目录内。

用在FDirectoryPath上的时候，限制目录为Content或其子目录。

用在FFilePath的时候，限制选择范围为Content里的资产，最终把选取的文件路径转换为“/Game/ObjectPath”这种对象的路径名。