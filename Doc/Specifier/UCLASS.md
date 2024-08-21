## UHT

| Name                                                         | 引擎模块         | 功能描述                                                     | 常用程度 |
| ------------------------------------------------------------ | ---------------- | ------------------------------------------------------------ | -------- |
| [NoExport](UCLASS/UHT/NoExport.md)                              | UHT              | 指定UHT不要用来自动生成注册的代码，而只是进行词法分析提取元数据。 | 0        |
| [Intrinsic](UCLASS/UHT/Intrinsic.md)                            | UHT              | 指定UHT完全不为此类生成代码，需要自己手写。                  | 0        |
| [Interface](UCLASS/UHT/Interface.md)                         | UHT              | 标识这个Class是个Interface。                                 | 0        |
| [UCLASS()](UCLASS/UHT/UCLASS().md)                           | UHT              | 留空的默认行为是不能在蓝图中被继承，不能在蓝图中定义变量，但拥有反射的功能。 | 5        |
| [不写UCLASS()](UCLASS/UHT/不写UCLASS().md)                   | UHT              | 只是作为一个普通的C++对象，没有反射功能。                    | 1        |
| [CustomThunkTemplates](UCLASS/UHT/CustomThunkTemplates.md)   | UHT              | Specifies the struct that contains the CustomThunk implementations |          |
| [CustomConstructor](UCLASS/UHT/CustomConstructor.md)         | UHT              | 阻止构造函数声明自动生成。                                   |          |
| [CustomFieldNotify](UCLASS/UHT/CustomFieldNotify.md)         | UHT              | 阻止UHT为该类生成FieldNotify的相关代码。                     | 0        |


## Blueprint

| Name                                                         | 引擎模块         | 功能描述                                                     | 常用程度 |
| ------------------------------------------------------------ | ---------------- | ------------------------------------------------------------ | -------- |
| [Blueprintable](UCLASS/Blueprint/Blueprintable/Blueprintable.md) | Blueprint        | 可以在蓝图里被继承，隐含的作用也可当变量类型                 | 5        |
| [NotBlueprintable](UCLASS/Blueprint/NotBlueprintable.md)        | Blueprint        | 不可在蓝图里继承，隐含作用也不可当作变量                     | 4        |
| [BlueprintType](UCLASS/Blueprint/BlueprintType/BlueprintType.md) | Blueprint        | 可当做变量类型                                               | 5        |
| [NotBlueprintType](UCLASS/Blueprint/NotBlueprintType.md)        | Blueprint        | 不可当做变量类型                                             | 4        |
| [Abstract](UCLASS/Blueprint/Abstract/Abstract.md)            | Blueprint        | 指定此类为抽象基类。可被继承，但不可生成对象。               | 5        |
| [Const](UPARAM/Blueprint/Const/Const.md)                     | Blueprint        | 表示本类的内部属性不可在蓝图中被修改，只读不可写。           | 3        |
| [ShowFunctions](UCLASS/Blueprint/ShowFunctions.md)           | Blueprint        | 在子类的函数覆盖列表里重新打开某些函数。                     | 2        |
| [HideFunctions](UCLASS/Blueprint/HideFunctions/HideFunctions.md) | Blueprint        | 在子类的函数覆盖列表里隐藏掉某些函数。                       | 2        |
| [SparseClassDataType](UCLASS/Blueprint/SparseClassDataType/SparseClassDataType.md) | Blueprint        | 让Actor的一些重复不变的数据存放在一个共同的结构里，以达到减少内容使用量的目的 | 3        |
| [NeedsDeferredDependencyLoading](UCLASS/Blueprint/NeedsDeferredDependencyLoading.md) | Blueprint        |                                                              |          |


## DllExport

| Name                                                         | 引擎模块         | 功能描述                                                     | 常用程度 |
| ------------------------------------------------------------ | ---------------- | ------------------------------------------------------------ | -------- |
| [MinimalAPI](UINTERFACE/UHT/MinimalAPI.md)                   | DllExport        | 不dll导出该类的函数，只导出类型信息当作变量。                | 3        |


## Category

| Name                                                         | 引擎模块         | 功能描述                                                     | 常用程度 |
| ------------------------------------------------------------ | ---------------- | ------------------------------------------------------------ | -------- |
| [ClassGroup](UCLASS/Category/ClassGroup/ClassGroup.md)       | Category | 指定组件在Actor的AddComponent面板里的分组，以及在蓝图右键菜单中的分组。 | 3        |
| [ShowCategories](UCLASS/Category/ShowCategories/ShowCategories.md) | Category         | 在类的ClassDefaults属性面板里显示某些Category的属性。        | 3        |
| [HideCategories](UCLASS/Category/HideCategories/HideCategories.md) | Category         | 在类的ClassDefaults属性面板里隐藏某些Category的属性。        | 4        |
| [CollapseCategories](UCLASS/Category/CollapseCategories/CollapseCategories.md) | Category         | 在类的属性面板里隐藏所有带Category的属性，但是只对带有多个嵌套Category的属性才起作用。 | 2        |
| [DontCollapseCategories](UCLASS/Category/DontCollapseCategories.md) | Category         | 使继承自基类的CollapseCatogories说明符无效。                 | 2        |
| [AutoExpandCategories](UCLASS/Category/AutoExpandCategories/AutoExpandCategories.md) | Category         | 指定此类的对象在细节面板中应该自动展开的Category。           | 1        |
| [AutoCollapseCategories](UCLASS/Category/AutoCollapseCategories/AutoCollapseCategories.md) | Category         | AutoCollapseCategories说明符使父类上的 AutoExpandCategories 说明符的列出类别的效果无效。 | 1        |
| [DontAutoCollapseCategories](UCLASS/Category/DontAutoCollapseCategories.md) | Category         | 使列出的类别的继承自父类的AutoCollapseCategories说明符无效。 | 1        |
| [PrioritizeCategories](UCLASS/Category/PrioritizeCategories/PrioritizeCategories.md) | Category         | 把指定的属性目录优先显示在细节面板的前面。                   | 3        |
| [ComponentWrapperClass](UCLASS/Category/ComponentWrapperClass/ComponentWrapperClass.md) | Category         | 指定该类为一个简单的封装类，忽略掉子类的Category相关设置。   | 2        |
| [AdvancedClassDisplay](UCLASS/Category/AdvancedClassDisplay/AdvancedClassDisplay.md) | Category         | 把该类下的所有属性都默认显示在高级目录下                     | 4        |


## TypePicker

| Name                                                         | 引擎模块         | 功能描述                                                     | 常用程度 |
| ------------------------------------------------------------ | ---------------- | ------------------------------------------------------------ | -------- |
| [HideDropDown](UCLASS/TypePicker/HideDropDown/HideDropDown.md) | TypePicker       | 在类选择器中隐藏此类                                         | 2        |



## Development

| Name                                                         | 引擎模块         | 功能描述                                                     | 常用程度 |
| ------------------------------------------------------------ | ---------------- | ------------------------------------------------------------ | -------- |
| [Deprecated](UCLASS/Development/Deprecated/Deprecated.md)    | Development      | 标明该类已经弃用。                                           | 3        |
| [Experimental](UCLASS/Development/Experimental/Experimental.md) | Development      | 标明该类是试验性版本，当前没有文档描述，之后有可能废弃掉。   | 3        |
| [EarlyAccessPreview](UCLASS/Development/EarlyAccessPreview/EarlyAccessPreview.md) | Development      | 标明该类是早期预览版，比试验版要更完善一些，但还是没到产品级。 | 3        |



## Instance

| Name                                                         | 引擎模块         | 功能描述                                                     | 常用程度 |
| ------------------------------------------------------------ | ---------------- | ------------------------------------------------------------ | -------- |
| [Within](UCLASS/Instance/Within.md)                          | Instance         | 指定对象创建的时候必须依赖于OuterClassName的对象作为Outer。  | 3        |
| [DefaultToInstanced](UCLASS/Instance/DefaultToInstanced/DefaultToInstanced.md) | Instance         | 指定该类的所有实例属性都默认是UPROPERTY(instanced)，即都默认创建新的实例，而不是对对象的引用。 | 4        |
| [EditInlineNew](UCLASS/Instance/EditInlineNew/EditInlineNew.md) | Instance         | 指定该类的对象可以在属性细节面板里直接内联创建，要和属性的Instanced配合。 | 5        |
| [NotEditInlineNew](UCLASS/Instance/NotEditInlineNew.md)      | Instance         | 不能通过EditInline按钮创建                                   | 1        |


## Scene

| Name                                                         | 引擎模块         | 功能描述                                                     | 常用程度 |
| ------------------------------------------------------------ | ---------------- | ------------------------------------------------------------ | -------- |
| [NotPlaceable](UCLASS/Scene/NotPlaceable/NotPlaceable.md)    | Scene         | 标明该Actor不可被放置在关卡里                                | 3        |
| [Placeable](UCLASS/Scene/Placeable/Placeable.md)             | Scene            | 标明该Actor可以放置在关卡里。                                | 3        |
| [ConversionRoot](UCLASS/Scene/ConversionRoot/ConversionRoot.md) | Scene            | 在场景编辑器里允许Actor在自身以及子类之间做转换              | 1        |



## Config

| Name                                                         | 引擎模块         | 功能描述                                                     | 常用程度 |
| ------------------------------------------------------------ | ---------------- | ------------------------------------------------------------ | -------- |
| [Config](UCLASS/Config/Config.md)                            | Config           | 指定配置文件的名字，把该对象的值保存到ini配置文件中。        | 5        |
| [PerObjectConfig](UCLASS/Config/PerObjectConfig.md)          | Config           | 在已经有config配置文件名字的情况下，指定应该按每个对象实例来存储值，而不是一个类一个存储值。 | 5        |
| [ConfigDoNotCheckDefaults](UCLASS/Config/ConfigDoNotCheckDefaults.md) | Config           | 指定在保存配置值的时候忽略上一级的配置值的一致性检查。       | 1        |
| [DefaultConfig](UCLASS/Config/DefaultConfig/DefaultConfig.md) | Config           | 指定保存到的配置文件层级是Project/Config/DefaultXXX.ini。    | 3        |
| [GlobalUserConfig](UCLASS/Config/GlobalUserConfig/GlobalUserConfig.md) | Config           | 指定保存到的配置文件层级是全局用户设置 Engine/Config/UserXXX.ini。 | 3        |
| [ProjectUserConfig](UCLASS/Config/ProjectUserConfig/ProjectUserConfig.md) | Config           | 指定保存到的配置文件层级是项目用户设置 Project/Config/UserXXX.ini。 | 3        |
| [EditorConfig](UCLASS/Config/EditorConfig/EditorConfig.md)   | Config   | 用来在编辑器状态下保存信息。                                 | 1        |


## Serialization

| Name                                                         | 引擎模块         | 功能描述                                                     | 常用程度 |
| ------------------------------------------------------------ | ---------------- | ------------------------------------------------------------ | -------- |
| [Transient](UCLASS/Serialization/Transient/Transient.md)     | Serialization    | 指定该类的所有对象都略过序列化。                             | 3        |
| [NonTransient](UCLASS/Serialization/NonTransient.md)         | Serialization    | 使继承自基类的Transient说明符无效。                          | 3        |
| [Optional](UCLASS/Serialization/Optional/Optional.md)        | Serialization    | 标记该类的对象是可选的，在Cooking的时候可以选择是否要忽略保存它们。 | 1        |
| [MatchedSerializers](UCLASS/Serialization/MatchedSerializers/MatchedSerializers.md) | Serialization    | 指定类支持文本结构序列化                                     | 0        |
