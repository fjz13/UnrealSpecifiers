# USTRUCT(标识符)

 ## UHT

| Name                                                         | 引擎模块      | 功能描述                                                     | 常用程度 |
| ------------------------------------------------------------ | ------------- | ------------------------------------------------------------ | -------- |
| [NoExport](USTRUCT/UHT/NoExport/NoExport.md)                 | UHT           | 指定UHT不要用来自动生成注册的代码，而只是进行词法分析提取元数据。 | ★        |
| [Atomic](USTRUCT/UHT/Atomic/Atomic.md)                       | UHT           | 指定该结构在序列化的时候总是一整个输出全部属性，而不是只输出改变的属性。 | ★        |
| [IsAlwaysAccessible](USTRUCT/UHT/IsAlwaysAccessible.md)      | UHT           | 指定UHT在生成文件的时候总是可以访问到改结构的声明，否则要在gen.cpp里生成镜像结构定义 | 💀        |
| [HasDefaults](USTRUCT/UHT/HasDefaults.md)                    | UHT           | 指定该结构的字段拥有默认值。这样如果本结构作为函数参数或返回值时候，函数则可以为其提供默认值。 | 💀        |
| [HasNoOpConstructor](USTRUCT/UHT/HasNoOpConstructor.md)      | UHT           | 指定该结构拥有ForceInit的构造函数，这样在作为BP function返回值的时候，可以调用来初始化 | 💀        |
| [IsCoreType](USTRUCT/UHT/IsCoreType.md)                      | UHT           | 指定该结构是核心类，UHT在用它的时候不需要前向声明。          | 💀        |


 ## Blueprint

| Name                                                         | 引擎模块      | 功能描述                                                     | 常用程度 |
| ------------------------------------------------------------ | ------------- | ------------------------------------------------------------ | -------- |
| [BlueprintType](USTRUCT/Blueprint/BlueprintType/BlueprintType.md) | Blueprint     | 允许这个结构在蓝图中声明变量                                 | ★★★★★    |
| [BlueprintInternalUseOnly](USTRUCT/Blueprint/BlueprintInternalUseOnly/BlueprintInternalUseOnly.md) | Blueprint     | 不可定义新BP变量，但可作为别的类的成员变量暴露和变量传递     | ★★       |
| [BlueprintInternalUseOnlyHierarchical](USTRUCT/Blueprint/BlueprintInternalUseOnlyHierarchical.md) | Blueprint     | 在BlueprintInternalUseOnly的基础上，增加了子类也不能定义新BP变量的限制。 | ★        |


 ## Serialization

| Name                                                         | 引擎模块      | 功能描述                                                     | 常用程度 |
| ------------------------------------------------------------ | ------------- | ------------------------------------------------------------ | -------- |
| [immutable](USTRUCT/Serialization/immutable.md)              | Serialization | Immutable is only legal in Object.h and is being phased out, do not use on new structs! | 💀        |
