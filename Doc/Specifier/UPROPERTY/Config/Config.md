# Config

- **功能描述：**指定该属性是一个配置属性，该属性可以被序列化读写到ini文件（路径由uclass的config标签指定）中。
- **元数据类型：**bool
- **引擎模块：**Config
- **作用机制：**[CPF_Config](../../../Flags/EPropertyFlags/CPF_Config.md)
- **常用程度：**★★★

指定该属性是一个配置属性，该属性可以被序列化读写到ini文件（路径由uclass的config标签指定）中。

在载入的时候会自动从ini中加载。如果没再加写标记，则会隐含该属性为ReadOnly。

参见UCLASS中的config标记的示例代码和效果。