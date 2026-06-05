# Ambiguous Symbols Index

> Use this when a bare symbol name matches multiple source docs and the user did not provide enough macro/context. `Doc` is relative to `references/sources/`.

| Symbol | Choose when | Usage | Doc |
|---|---|---|---|
| `Abstract` | 标识该FRigUnit为抽象类，不用实现Execute | USTRUCT | `Meta/RigVM/Abstract.md` |
| `Abstract` | 指定此类为抽象基类。可被继承，但不可生成对象 | UCLASS / Blueprint | `Specifier/UCLASS/Blueprint/Abstract.md` |
| `AdvancedClassDisplay` | 指定该类型的变量在高级显示里显示 | UCLASS | `Meta/DetailsPanel/AdvancedClassDisplay.md` |
| `AdvancedClassDisplay` | 把该类下的所有属性都默认显示在高级目录下 | UCLASS / Category | `Specifier/UCLASS/Category/AdvancedClassDisplay.md` |
| `AdvancedDisplay` | 把函数的一些参数折叠起来不显示，需要手动点开下拉箭头来展开编辑 | UFUNCTION | `Meta/Blueprint/AdvancedDisplay.md` |
| `AdvancedDisplay` | 被折叠到高级栏下，要手动打开。一般用在不太常用的属性上面 | UPROPERTY / DetailsPanel | `Specifier/UPROPERTY/DetailsPanel/AdvancedDisplay.md` |
| `AutoCollapseCategories` | 指定类内部的属性目录自动折叠起来 | UCLASS | `Meta/DetailsPanel/AutoCollapseCategories.md` |
| `AutoCollapseCategories` | AutoCollapseCategories说明符使父类上的 AutoExpandCategories 说明符的列出类别的效果无效 | UCLASS / Category | `Specifier/UCLASS/Category/AutoCollapseCategories.md` |
| `AutoExpandCategories` | 指定类内部的属性目录自动展开起来 | UCLASS | `Meta/DetailsPanel/AutoExpandCategories.md` |
| `AutoExpandCategories` | 指定此类的对象在细节面板中应该自动展开的Category | UCLASS / Category | `Specifier/UCLASS/Category/AutoExpandCategories.md` |
| `Blueprintable` | 可以在蓝图里被继承，隐含的作用也可当变量类型 | UCLASS / Blueprint | `Specifier/UCLASS/Blueprint/Blueprintable.md` |
| `Blueprintable` | 可以在蓝图中实现 | UINTERFACE / Blueprint | `Specifier/UINTERFACE/Blueprint/Blueprintable.md` |
| `BlueprintAuthorityOnly` | 这个函数只能在拥有网络权限的端上运行 | UFUNCTION / Network | `Specifier/UFUNCTION/Network/BlueprintAuthorityOnly.md` |
| `BlueprintAuthorityOnly` | 只能绑定为BlueprintAuthorityOnly的事件，让该多播委托只接受在服务端运行的事件 | UPROPERTY / Blueprint | `Specifier/UPROPERTY/Blueprint/BlueprintAuthorityOnly.md` |
| `BlueprintCallable` | 暴露到蓝图中可被调用 | UFUNCTION / Blueprint | `Specifier/UFUNCTION/Blueprint/BlueprintCallable.md` |
| `BlueprintCallable` | 在蓝图中可以调用这个多播委托 | UPROPERTY / Blueprint | `Specifier/UPROPERTY/Blueprint/BlueprintCallable.md` |
| `BlueprintGetter` | 采用一个自定义的get函数来读取 | UFUNCTION, UPROPERTY | `Meta/Blueprint/BlueprintGetter.md` |
| `BlueprintGetter` | 指定该函数作为属性的自定义Get函数 | UFUNCTION / Blueprint | `Specifier/UFUNCTION/Blueprint/BlueprintGetter.md` |
| `BlueprintGetter` | 为属性定义一个自定义的Get函数来读取 | UPROPERTY / Blueprint | `Specifier/UPROPERTY/Blueprint/BlueprintGetter.md` |
| `BlueprintInternalUseOnly` | 标明该元素是作为蓝图系统的内部调用或使用，不暴露出来在用户层面直接定义或使用 | UFUNCTION, USTRUCT | `Meta/Blueprint/BlueprintInternalUseOnly.md` |
| `BlueprintInternalUseOnly` | 指示不应向最终用户公开此函数。蓝图内部调用，不暴露给用户 | UFUNCTION / UHT | `Specifier/UFUNCTION/UHT/BlueprintInternalUseOnly.md` |
| `BlueprintInternalUseOnly` | 不可定义新BP变量，但可作为别的类的成员变量暴露和变量传递 | USTRUCT / Blueprint | `Specifier/USTRUCT/Blueprint/BlueprintInternalUseOnly.md` |
| `BlueprintInternalUseOnlyHierarchical` | 标明该结构及其子类都不暴露给用户定义和使用，均只能在蓝图系统内部使用 | USTRUCT | `Meta/Blueprint/BlueprintInternalUseOnlyHierarchical.md` |
| `BlueprintInternalUseOnlyHierarchical` | 在BlueprintInternalUseOnly的基础上，增加了子类也不能定义新BP变量的限制 | USTRUCT / Blueprint | `Specifier/USTRUCT/Blueprint/BlueprintInternalUseOnlyHierarchical.md` |
| `BlueprintSetter` | 采用一个自定义的set函数来读取 | UFUNCTION, UPROPERTY | `Meta/Blueprint/BlueprintSetter.md` |
| `BlueprintSetter` | 指定该函数作为属性的自定义Set函数 | UFUNCTION / Blueprint | `Specifier/UFUNCTION/Blueprint/BlueprintSetter.md` |
| `BlueprintSetter` | 采用一个自定义的set函数来读取 | UPROPERTY / Blueprint | `Specifier/UPROPERTY/Blueprint/BlueprintSetter.md` |
| `BlueprintType` | 表明可以作为一个蓝图变量 | UCLASS, UENUM, UINTERFACE, USTRUCT | `Meta/Blueprint/BlueprintType.md` |
| `BlueprintType` | 可当做变量类型 | UCLASS / Blueprint | `Specifier/UCLASS/Blueprint/BlueprintType.md` |
| `BlueprintType` | 可以作为蓝图变量 | UENUM / BlueprintType | `Specifier/UENUM/BlueprintType.md` |
| `BlueprintType` | 允许这个结构在蓝图中声明变量 | USTRUCT / Blueprint | `Specifier/USTRUCT/Blueprint/BlueprintType.md` |
| `CallInEditor` | 可以在Actor的细节面板上作为一个按钮来调用该函数 | UFUNCTION | `Meta/Blueprint/CallInEditor.md` |
| `CallInEditor` | 可以在属性细节面板上作为一个按钮来调用该函数 | UFUNCTION / Blueprint | `Specifier/UFUNCTION/Blueprint/CallInEditor.md` |
| `Category` | 指定属性在细节面板中的分类 | UFUNCTION, UPROPERTY | `Meta/DetailsPanel/Category.md` |
| `Category` | 在蓝图的右键菜单中为该函数指定类别分组，可以嵌套多级 | UFUNCTION / Category | `Specifier/UFUNCTION/Category.md` |
| `Category` | 指定属性的类别，使用 &#124; 运算符定义嵌套类目 | UPROPERTY / DetailsPanel | `Specifier/UPROPERTY/DetailsPanel/Category.md` |
| `Config` | 指定配置文件的名字，把该对象的值保存到ini配置文件中 | UCLASS / Config | `Specifier/UCLASS/Config/Config.md` |
| `Config` | 指定该属性是一个配置属性，该属性可以被序列化读写到ini文件（路径由uclass的config标签指定）中 | UPROPERTY / Config | `Specifier/UPROPERTY/Config/Config.md` |
| `Const` | 表示本类的内部属性不可在蓝图中被修改，只读不可写 | UCLASS / Blueprint | `Specifier/UCLASS/Blueprint/Const.md` |
| `Const` | 指定该函数参数不可更改 | UPARAM / Blueprint | `Specifier/UPARAM/Blueprint/Const.md` |
| `ConversionRoot` | 在场景编辑器里允许Actor在自身以及子类之间做转换 | UCLASS / Scene | `Specifier/UCLASS/Scene/ConversionRoot.md` |
| `ConversionRoot` | Sets IsConversionRoot metadata flag for this interface. | UINTERFACE / UHT | `Specifier/UINTERFACE/UHT/ConversionRoot.md` |
| `CustomThunk` | 指定UHT不为该函数生成蓝图调用的辅助函数，而需要用户自定义编写 | UFUNCTION | `Meta/UHT/CustomThunk.md` |
| `CustomThunk` | 指定UHT不为该函数生成蓝图调用的辅助函数，而需要用户自定义编写 | UFUNCTION / UHT | `Specifier/UFUNCTION/UHT/CustomThunk.md` |
| `CustomWidget` | 也可以放在属性上 | UFUNCTION, UPROPERTY | `Meta/AnimationGraph/CustomWidget.md` |
| `CustomWidget` | 指定该FRigUnit里的属性要用自定义的控件来编辑 | UPROPERTY | `Meta/RigVM/CustomWidget.md` |
| `Deprecated` | 指定该元素要废弃的引擎版本号 | Any | `Meta/Development/Deprecated.md` |
| `Deprecated` | 标识该FRigUnit为弃用状态，不在蓝图右键菜单中显示 | USTRUCT | `Meta/RigVM/Deprecated.md` |
| `Deprecated` | 标明该类已经弃用 | UCLASS / Development | `Specifier/UCLASS/Development/Deprecated.md` |
| `DisplayName` | 此节点在蓝图中的命名将被此处提供的值所取代，而非代码生成的命名 | UCLASS, UENUM::UMETA, UFUNCTION, UPARAM, UPROPERTY | `Meta/Blueprint/DisplayName.md` |
| `DisplayName` | 改变枚举值的显示名称 | UENUM::UMETA | `Meta/Enum/UMETA/DisplayName.md` |
| `DisplayName` | 更改函数参数在蓝图节点上的显示名字 | UPARAM / Blueprint | `Specifier/UPARAM/Blueprint/DisplayName.md` |
| `EditorConfig` | 保存编辑器的配置 | UCLASS | `Meta/Config/EditorConfig.md` |
| `EditorConfig` | 用来在编辑器状态下保存信息 | UCLASS / Config | `Specifier/UCLASS/Config/EditorConfig.md` |
| `FieldNotify` | 为该函数创建一个FieldNotify的绑定点 | UFUNCTION / UHT | `Specifier/UFUNCTION/UHT/FieldNotify.md` |
| `FieldNotify` | 在打开MVVM插件后，使得该属性变成支持FieldNotify的属性 | UPROPERTY / UHT | `Specifier/UPROPERTY/UHT/FieldNotify.md` |
| `Hidden` | 隐藏UENUM的某个值 | UENUM::UMETA | `Meta/Enum/UMETA/Hidden.md` |
| `Hidden` | 指定FRigUnit下的该属性隐藏 | UPROPERTY | `Meta/RigVM/Hidden.md` |
| `HideCategories` | 隐藏的类别 | UCLASS | `Meta/DetailsPanel/HideCategories.md` |
| `HideCategories` | 在类的ClassDefaults属性面板里隐藏某些Category的属性 | UCLASS / Category | `Specifier/UCLASS/Category/HideCategories.md` |
| `HideFunctions` | 在属性查看器中不显示指定类别中的所有函数 | UCLASS | `Meta/Blueprint/HideFunctions.md` |
| `HideFunctions` | 在子类的函数覆盖列表里隐藏掉某些函数 | UCLASS / Blueprint | `Specifier/UCLASS/Blueprint/HideFunctions.md` |
| `Keywords` | 指定一系列关键字用于在蓝图内右键找到该函数 | UFUNCTION | `Meta/Blueprint/Keywords.md` |
| `Keywords` | 设定FRigUnit蓝图节点在右键菜单中的关键字，方便输入查找 | USTRUCT | `Meta/RigVM/Keywords.md` |
| `MatchedSerializers` | 只在NoExportTypes.h中使用，标明采用结构序列化器。是否支持文本导入导出 | UCLASS | `Meta/Serialization/MatchedSerializers.md` |
| `MatchedSerializers` | UE5.8 中只允许 NoExportTypes.h 使用的内部 class specifier；普通项目 UCLASS 不应使用 | UCLASS / Serialization | `Specifier/UCLASS/Serialization/MatchedSerializers.md` |
| `MinimalAPI` | 不dll导出该类的函数，只导出类型信息当作变量 | UCLASS / UHT | `Specifier/UCLASS/UHT/MinimalAPI.md` |
| `MinimalAPI` | 指定该UInterface对象不导出到别的模块 | UINTERFACE / UHT | `Specifier/UINTERFACE/UHT/MinimalAPI.md` |
| `NoExport` | 指定UHT不要用来自动生成注册的代码，而只是进行词法分析提取元数据 | UCLASS / UHT | `Specifier/UCLASS/UHT/NoExport.md` |
| `NoExport` | 指定UHT不要用来自动生成注册的代码，而只是进行词法分析提取元数据 | USTRUCT / UHT | `Specifier/USTRUCT/UHT/NoExport.md` |
| `NotBlueprintable` | 不可在蓝图里继承，隐含作用也不可当作变量 | UCLASS / Blueprint | `Specifier/UCLASS/Blueprint/NotBlueprintable.md` |
| `NotBlueprintable` | 指定不可以在蓝图中实现 | UINTERFACE / Blueprint | `Specifier/UINTERFACE/Blueprint/NotBlueprintable.md` |
| `NotReplicated` | 只用于 ServiceRequest 产生的 replicated parameter，可把该参数标记为不参与 service request 参数复制 | UPARAM / Network | `Specifier/UPARAM/NotReplicated.md` |
| `NotReplicated` | 跳过复制。这只会应用到服务请求函数中的结构体成员和参数 | UPROPERTY / Network | `Specifier/UPROPERTY/Network/NotReplicated.md` |
| `PrioritizeCategories` | 把指定的属性目录优先显示在前面 | UCLASS | `Meta/DetailsPanel/PrioritizeCategories.md` |
| `PrioritizeCategories` | 把指定的属性目录优先显示在细节面板的前面 | UCLASS / Category | `Specifier/UCLASS/Category/PrioritizeCategories.md` |
| `ShowCategories` | 显示类别 | UCLASS | `Meta/DetailsPanel/ShowCategories.md` |
| `ShowCategories` | 在类的ClassDefaults属性面板里显示某些Category的属性 | UCLASS / Category | `Specifier/UCLASS/Category/ShowCategories.md` |
| `Transient` | 指定该类的所有对象都略过序列化 | UCLASS / Serialization | `Specifier/UCLASS/Serialization/Transient.md` |
| `Transient` | 不序列化该属性，该属性初始化时候会被0填充 | UPROPERTY / Serialization | `Specifier/UPROPERTY/Serialization/Transient.md` |
| `Variadic` | 指定该函数接受多个参数 | UFUNCTION | `Meta/Blueprint/Variadic.md` |
| `Variadic` | 标识一个函数可以接受任意类型的多个参数（包括input/output)． | UFUNCTION / UHT | `Specifier/UFUNCTION/UHT/Variadic.md` |
