# Specifier UCLASS

> Category source index. Use targeted search in this file, then open only the listed `Doc`.
> Resolve `Doc` relative to the nearest preceding `Doc root`; each `Doc root` is relative to `references/sources/`.

## Specifier - UCLASS

> Doc root: `Specifier/UCLASS/`

| ID | Summary | Usage | Doc |
|---|---|---|---|
| `Abstract` | 指定此类为抽象基类。可被继承，但不可生成对象 | UCLASS / Blueprint | `Blueprint/Abstract.md` |
| `AdvancedClassDisplay` | 把该类下的所有属性都默认显示在高级目录下 | UCLASS / Category | `Category/AdvancedClassDisplay.md` |
| `AutoCollapseCategories` | AutoCollapseCategories说明符使父类上的 AutoExpandCategories 说明符的列出类别的效果无效 | UCLASS / Category | `Category/AutoCollapseCategories.md` |
| `AutoExpandCategories` | 指定此类的对象在细节面板中应该自动展开的Category | UCLASS / Category | `Category/AutoExpandCategories.md` |
| `BlueprintType` | 可当做变量类型 | UCLASS / Blueprint | `Blueprint/BlueprintType.md` |
| `Blueprintable` | 可以在蓝图里被继承，隐含的作用也可当变量类型 | UCLASS / Blueprint | `Blueprint/Blueprintable.md` |
| `ClassGroup` | 指定组件在Actor的AddComponent面板里的分组，以及在蓝图右键菜单中的分组 | UCLASS / Category | `Category/ClassGroup.md` |
| `CollapseCategories` | 在类的属性面板里隐藏所有带Category的属性，但是只对带有多个嵌套Category的属性才起作用 | UCLASS / Category | `Category/CollapseCategories.md` |
| `ComponentWrapperClass` | 指定该类为一个简单的封装类，忽略掉子类的Category相关设置 | UCLASS / Category | `Category/ComponentWrapperClass.md` |
| `Config` | 指定配置文件的名字，把该对象的值保存到ini配置文件中 | UCLASS / Config | `Config/Config.md` |
| `ConfigDoNotCheckDefaults` | 指定在保存配置值的时候忽略上一级的配置值的一致性检查 | UCLASS / Config | `Config/ConfigDoNotCheckDefaults.md` |
| `Const` | 表示本类的内部属性不可在蓝图中被修改，只读不可写 | UCLASS / Blueprint | `Blueprint/Const.md` |
| `ConversionRoot` | 在场景编辑器里允许Actor在自身以及子类之间做转换 | UCLASS / Scene | `Scene/ConversionRoot.md` |
| `CustomConstructor` | 阻止构造函数声明自动生成 | UCLASS / UHT | `UHT/CustomConstructor.md` |
| `CustomFieldNotify` | 阻止UHT为该类生成FieldNotify的相关代码 | UCLASS / UHT | `UHT/CustomFieldNotify.md` |
| `CustomThunkTemplates` | Specifies the struct that contains the CustomThunk implementations | UCLASS / UHT | `UHT/CustomThunkTemplates.md` |
| `DefaultConfig` | 指定保存到的配置文件层级是Project/Config/DefaultXXX.ini | UCLASS / Config | `Config/DefaultConfig.md` |
| `DefaultToInstanced` | 指定该类的所有实例属性都默认是UPROPERTY(instanced)，即都默认创建新的实例，而不是对对象的引用 | UCLASS / Instance | `Instance/DefaultToInstanced.md` |
| `Deprecated` | 标明该类已经弃用 | UCLASS / Development | `Development/Deprecated.md` |
| `DontAutoCollapseCategories` | 使列出的类别的继承自父类的AutoCollapseCategories说明符无效 | UCLASS / Category | `Category/DontAutoCollapseCategories.md` |
| `DontCollapseCategories` | 使继承自基类的CollapseCatogories说明符无效 | UCLASS / Category | `Category/DontCollapseCategories.md` |
| `EarlyAccessPreview` | 标明该类是早期预览版，比试验版要更完善一些，但还是没到产品级 | UCLASS / Development | `Development/EarlyAccessPreview.md` |
| `EditInlineNew` | 指定该类的对象可以在属性细节面板里直接内联创建，要和属性的Instanced配合 | UCLASS / Instance | `Instance/EditInlineNew.md` |
| `EditorConfig` | 用来在编辑器状态下保存信息 | UCLASS / Config | `Config/EditorConfig.md` |
| `Experimental` | 标明该类是试验性版本，当前没有文档描述，之后有可能废弃掉 | UCLASS / Development | `Development/Experimental.md` |
| `GlobalUserConfig` | 指定保存到的配置文件层级是全局用户设置 Engine/Config/UserXXX.ini | UCLASS / Config | `Config/GlobalUserConfig.md` |
| `HideCategories` | 在类的ClassDefaults属性面板里隐藏某些Category的属性 | UCLASS / Category | `Category/HideCategories.md` |
| `HideDropDown` | 在类选择器中隐藏此类 | UCLASS / TypePicker | `HideDropDown.md` |
| `HideFunctions` | 在子类的函数覆盖列表里隐藏掉某些函数 | UCLASS / Blueprint | `Blueprint/HideFunctions.md` |
| `Interface` | 标识这个Class是个Interface | UCLASS / UHT | `UHT/Interface.md` |
| `Intrinsic` | 指定UHT完全不为此类生成代码，需要自己手写 | UCLASS / UHT | `UHT/Intrinsic.md` |
| `MatchedSerializers` | UE5.8 中只允许 NoExportTypes.h 使用的内部 class specifier；普通项目 UCLASS 不应使用 | UCLASS / Serialization | `Serialization/MatchedSerializers.md` |
| `MinimalAPI` | 不dll导出该类的函数，只导出类型信息当作变量 | UCLASS / UHT | `UHT/MinimalAPI.md` |
| `NeedsDeferredDependencyLoading` | UCLASS(NeedsDeferredDependencyLoading, MinimalAPI) | UCLASS / Blueprint | `Blueprint/NeedsDeferredDependencyLoading.md` |
| `NoExport` | 指定UHT不要用来自动生成注册的代码，而只是进行词法分析提取元数据 | UCLASS / UHT | `UHT/NoExport.md` |
| `NonTransient` | 使继承自基类的Transient说明符无效 | UCLASS / Serialization | `Serialization/NonTransient.md` |
| `NotBlueprintType` | 不可当做变量类型 | UCLASS / Blueprint | `Blueprint/NotBlueprintType.md` |
| `NotBlueprintable` | 不可在蓝图里继承，隐含作用也不可当作变量 | UCLASS / Blueprint | `Blueprint/NotBlueprintable.md` |
| `NotEditInlineNew` | 不能通过EditInline按钮创建 | UCLASS / Instance | `Instance/NotEditInlineNew.md` |
| `NotPlaceable` | 标明该Actor不可被放置在关卡里 | UCLASS / Scene | `Scene/NotPlaceable.md` |
| `Optional` | 标记该类的对象是可选的，在Cooking的时候可以选择是否要忽略保存它们 | UCLASS / Serialization | `Serialization/Optional.md` |
| `PerObjectConfig` | 在已经有config配置文件名字的情况下，指定应该按每个对象实例来存储值，而不是一个类一个存储值 | UCLASS / Config | `Config/PerObjectConfig.md` |
| `Placeable` | 标明该Actor可以放置在关卡里 | UCLASS / Scene | `Scene/Placeable.md` |
| `PrioritizeCategories` | 把指定的属性目录优先显示在细节面板的前面 | UCLASS / Category | `Category/PrioritizeCategories.md` |
| `ProjectUserConfig` | 指定保存到的配置文件层级是项目用户设置 Project/Config/UserXXX.ini | UCLASS / Config | `Config/ProjectUserConfig.md` |
| `ShowCategories` | 在类的ClassDefaults属性面板里显示某些Category的属性 | UCLASS / Category | `Category/ShowCategories.md` |
| `ShowFunctions` | 在子类的函数覆盖列表里重新打开某些函数 | UCLASS / Blueprint | `Blueprint/ShowFunctions.md` |
| `SparseClassDataType` | 让Actor的一些重复不变的数据存放在一个共同的结构里，以达到减少内容使用量的目的 | UCLASS / Blueprint | `Blueprint/SparseClassDataType.md` |
| `Transient` | 指定该类的所有对象都略过序列化 | UCLASS / Serialization | `Serialization/Transient.md` |
| `UCLASS()` | 留空的默认行为是不能在蓝图中被继承，不能在蓝图中定义变量，但拥有反射的功能 | UCLASS / UHT | `UHT/UCLASS_Empty.md` |
| `UCLASS(标识符)` | UE5.8 UHT 通过 UhtClassParser 识别 UCLASS，创建 class 类型并使用 UhtTableNames.Class 的 keyword/specifier table 解析 specifier。该页是 UCLA | UCLASS | `../UCLASS.md` |
| `Within` | 指定对象创建的时候必须依赖于OuterClassName的对象作为Outer | UCLASS / Instance | `Instance/Within.md` |
| `Without_UCLASS` | 只是作为一个普通的C++对象，没有反射功能 | UCLASS / UHT | `UHT/Without_UCLASS.md` |



