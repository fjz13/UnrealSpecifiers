# Common Index

> 高频 specifier/meta 快速索引，由 Doc 中的 `常用程度` 生成：`★★★★★` 和 `★★★★` 进入本文件；缺失 `常用程度` 按 `0` 处理；`💀`、`changed_in_version`、`removed_or_deprecated` 不进入 common。
> 一级路由见 `routing.index.md`；未命中常用项时，按路由进入分类索引。`Doc` 相对 `references/sources/`。

## ★★★★★

Count: 85

| ID | Summary | Usage | Doc |
|---|---|---|---|
| `AdvancedDisplay` | 把函数的一些参数折叠起来不显示，需要手动点开下拉箭头来展开编辑 | UFUNCTION | `Meta/Blueprint/AdvancedDisplay.md` |
| `AllowPrivateAccess` | 允许一个在C++中private的属性，可以在蓝图中访问 | UPROPERTY | `Meta/Blueprint/AllowPrivateAccess.md` |
| `AutoCreateRefTerm` | 指定函数的多个输入引用参数在没有连接的时候自动为其创建默认值 | UFUNCTION | `Meta/Blueprint/Param/AutoCreateRefTerm.md` |
| `BindWidget` | 指定在C++类中该Widget属性一定要绑定到UMG的某个同名控件 | UPROPERTY | `Meta/Widget/BindWidget.md` |
| `BindWidgetAnim` | 指定在C++类中该UWidgetAnimation属性一定要绑定到UMG下的某个动画 | UPROPERTY | `Meta/Widget/BindWidgetAnim.md` |
| `Bitflags` | 设定一个枚举支持采用位标记赋值，从而在蓝图中可以识别出来是BitMask | UENUM | `Meta/Enum/Bitflags.md` |
| `Bitmask` | 设定一个属性采用Bitmask赋值 | UPROPERTY | `Meta/Enum/Bitmask.md` |
| `BitmaskEnum` | 使用位标记后采用的枚举名字 | UPROPERTY | `Meta/Enum/BitmaskEnum.md` |
| `Blueprint.DisplayName` | 此节点在蓝图中的命名将被此处提供的值所取代，而非代码生成的命名 | UCLASS, UENUM::UMETA, UFUNCTION, UPARAM, UPROPERTY | `Meta/Blueprint/DisplayName.md` |
| `Blueprint.Keywords` | 指定一系列关键字用于在蓝图内右键找到该函数 | UFUNCTION | `Meta/Blueprint/Keywords.md` |
| `BlueprintType` | 表明可以作为一个蓝图变量 | UCLASS, UENUM, UINTERFACE, USTRUCT | `Meta/Blueprint/BlueprintType.md` |
| `CallInEditor` | 可以在Actor的细节面板上作为一个按钮来调用该函数 | UFUNCTION | `Meta/Blueprint/CallInEditor.md` |
| `Category` | 指定属性在细节面板中的分类 | UFUNCTION, UPROPERTY | `Meta/DetailsPanel/Category.md` |
| `ClampMax` | 指定数字输入框实际接受的最大值 | UPROPERTY | `Meta/Numeric/ClampMax.md` |
| `ClampMin` | 指定数字输入框实际接受的最小值 | UPROPERTY | `Meta/Numeric/ClampMin.md` |
| `ConsoleVariable` | 把一个Conifg属性的值同步到一个同名的控制台变量 | UPROPERTY | `Meta/Config/ConsoleVariable.md` |
| `CPP_Default_XXX` | XXX=参数名字 | UPARAM | `Meta/Blueprint/CPP_Default_XXX.md` |
| `CustomStructureParam` | 被CustomStructureParam标记的函数参数会变成Wildcard的通配符参数，其引脚的类型会等于连接的变量类型 | UFUNCTION | `Meta/Blueprint/Param/CustomStructureParam.md` |
| `CustomThunk` | 指定UHT不为该函数生成蓝图调用的辅助函数，而需要用户自定义编写 | UFUNCTION | `Meta/UHT/CustomThunk.md` |
| `DefaultToSelf` | 用在函数上，指定一个参数的默认值为Self值 | UFUNCTION | `Meta/Blueprint/DefaultToSelf.md` |
| `EditCondition` | 给一个属性指定另外一个属性或者表达式来作为是否可编辑的条件 | UPROPERTY | `Meta/DetailsPanel/EditCondition.md` |
| `EditConditionHides` | 在已经有EditCondition的情况下，指定该属性在EditCondition不满足的情况下隐藏起来 | UPROPERTY | `Meta/DetailsPanel/EditConditionHides.md` |
| `Enum.UMETA.DisplayName` | 改变枚举值的显示名称 | UENUM::UMETA | `Meta/Enum/UMETA/DisplayName.md` |
| `Enum.UMETA.Hidden` | 隐藏UENUM的某个值 | UENUM::UMETA | `Meta/Enum/UMETA/Hidden.md` |
| `ExpandBoolAsExecs` | 是ExpandEnumAsExecs的别名，完全等价其功能 | UFUNCTION | `Meta/Blueprint/Exec/ExpandBoolAsExecs.md` |
| `ExpandEnumAsExecs` | 指定多个enum或bool类型的函数参数，自动根据条目生成相应的多个输入或输出执行引脚，并根据实参值不同来相应改变控制流 | UFUNCTION | `Meta/Blueprint/Exec/ExpandEnumAsExecs.md` |
| `ExposeOnSpawn` | 使该属性在ContructObject或SpawnActor等创建对象的时候暴露出来 | UPROPERTY | `Meta/Blueprint/ExposeOnSpawn.md` |
| `GetOptions` | 指定一个外部类的函数提供选项给FName或FString属性在细节面板中下拉选项框提供值列表 | UPARAM, UPROPERTY | `Meta/String/GetOptions.md` |
| `HasNativeBreak` | 为该结构指定一个C++内的UFunction函数作为Break节点的实现 | USTRUCT | `Meta/Struct/HasNativeBreak.md` |
| `HasNativeMake` | 为该结构指定一个C++内的UFunction函数作为Mreak节点的实现 | USTRUCT | `Meta/Struct/HasNativeMake.md` |
| `HideEditConditionToggle` | 用在使用EditCondition的属性上，表示该属性不想要其EditCondition用到的属性被隐藏起来 | UPROPERTY | `Meta/DetailsPanel/HideEditConditionToggle.md` |
| `InlineEditConditionToggle` | 使这个bool属性在被用作EditCondition的时候内联到对方的属性行里成为一个单选框，而不是自己成为一个编辑行 | UPROPERTY | `Meta/DetailsPanel/InlineEditConditionToggle.md` |
| `Input` | 指定FRigUnit下的该属性作为输入引脚 | UPROPERTY | `Meta/RigVM/Input.md` |
| `IsBlueprintBase` | 说明此类是否为创建蓝图的一个可接受基类，与 UCLASS 说明符、Blueprintable 或 'NotBlueprintable` 相似 | UCLASS, UINTERFACE | `Meta/Blueprint/IsBlueprintBase.md` |
| `Latent` | 标明一个函数是一个延迟异步操作 | UFUNCTION | `Meta/Blueprint/Latent/Latent.md` |
| `MaxLength` | 在文本编辑框里限制文本的最大长度 | UPROPERTY | `Meta/String/MaxLength.md` |
| `MultiLine` | 使得文本属性编辑框支持换行 | UPROPERTY | `Meta/String/MultiLine.md` |
| `Output` | 指定FRigUnit下的该属性作为输出引脚 | UPROPERTY | `Meta/RigVM/Output.md` |
| `PasswordField` | 使得文本属性显示为密码框 | UPROPERTY | `Meta/String/PasswordField.md` |
| `ReturnDisplayName` | 改变函数返回值的名字，默认是ReturnValue | UFUNCTION | `Meta/Blueprint/ReturnDisplayName.md` |
| `ShowInnerProperties` | 在属性细节面板中显示对象引用的内部属性 | UPROPERTY | `Meta/Object/ShowInnerProperties.md` |
| `SliderExponent` | 指定数字输入框上滚动条拖动的变化指数分布 | UPROPERTY | `Meta/Numeric/SliderExponent.md` |
| `Spacer` | 隐藏UENUM的某个值 | UENUM::UMETA | `Meta/Enum/UMETA/Spacer.md` |
| `UIMax` | 指定数字输入框上滚动条拖动的最大范围值 | UPROPERTY | `Meta/Numeric/UIMax.md` |
| `UIMin` | 指定数字输入框上滚动条拖动的最小范围值 | UPROPERTY | `Meta/Numeric/UIMin.md` |
| `WorldContext` | 指定函数的一个参数自动接收WorldContext对象，以便确定当前运行所处于的World | UFUNCTION | `Meta/Blueprint/WorldContext.md` |
| `Abstract` | 指定此类为抽象基类。可被继承，但不可生成对象 | UCLASS / Blueprint | `Specifier/UCLASS/Blueprint/Abstract.md` |
| `Blueprintable` | 可以在蓝图里被继承，隐含的作用也可当变量类型 | UCLASS / Blueprint | `Specifier/UCLASS/Blueprint/Blueprintable.md` |
| `BlueprintType` | 可当做变量类型 | UCLASS / Blueprint | `Specifier/UCLASS/Blueprint/BlueprintType.md` |
| `Config` | 指定配置文件的名字，把该对象的值保存到ini配置文件中 | UCLASS / Config | `Specifier/UCLASS/Config/Config.md` |
| `EditInlineNew` | 指定该类的对象可以在属性细节面板里直接内联创建，要和属性的Instanced配合 | UCLASS / Instance | `Specifier/UCLASS/Instance/EditInlineNew.md` |
| `PerObjectConfig` | 在已经有config配置文件名字的情况下，指定应该按每个对象实例来存储值，而不是一个类一个存储值 | UCLASS / Config | `Specifier/UCLASS/Config/PerObjectConfig.md` |
| `UCLASS()` | 留空的默认行为是不能在蓝图中被继承，不能在蓝图中定义变量，但拥有反射的功能 | UCLASS / UHT | `Specifier/UCLASS/UHT/UCLASS_Empty.md` |
| `BlueprintType` | 可以作为蓝图变量 | UENUM / BlueprintType | `Specifier/UENUM/BlueprintType.md` |
| `Flags` | 把该枚举的值作为一个标志来拼接字符串输出 | UENUM / Flags | `Specifier/UENUM/Flags.md` |
| `BlueprintCallable` | 暴露到蓝图中可被调用 | UFUNCTION / Blueprint | `Specifier/UFUNCTION/Blueprint/BlueprintCallable.md` |
| `BlueprintImplementableEvent` | 指定一个函数调用点，可以在蓝图中重载实现 | UFUNCTION / Blueprint | `Specifier/UFUNCTION/Blueprint/BlueprintImplementableEvent.md` |
| `BlueprintNativeEvent` | 可以在蓝图总覆盖实现，但是也在C++中提供一个默认实现 | UFUNCTION / Blueprint | `Specifier/UFUNCTION/Blueprint/BlueprintNativeEvent.md` |
| `BlueprintPure` | 指定作为一个纯函数，一般用于Get函数用来返回值 | UFUNCTION / Blueprint | `Specifier/UFUNCTION/Blueprint/BlueprintPure.md` |
| `CallInEditor` | 可以在属性细节面板上作为一个按钮来调用该函数 | UFUNCTION / Blueprint | `Specifier/UFUNCTION/Blueprint/CallInEditor.md` |
| `Category` | 在蓝图的右键菜单中为该函数指定类别分组，可以嵌套多级 | UFUNCTION / Category | `Specifier/UFUNCTION/Category.md` |
| `Client` | 在Client-owned的Actor上（PlayerController或Pawn）执行一个RPC函数，只运行在客户端上。对应的实现函数会添加_Implementation后缀 | UFUNCTION / Network | `Specifier/UFUNCTION/Network/Client.md` |
| `NetMulticast` | 定义一个多播RPC函数在服务器和客户端上都执行。对应的实现函数会添加_Implementation后缀 | UFUNCTION / Network | `Specifier/UFUNCTION/Network/NetMulticast.md` |
| `Reliable` | 指定一个RPC函数为“可靠的”，当遇见网络错误时会重发以保证到达。一般用在逻辑关键的函数上 | UFUNCTION / Network | `Specifier/UFUNCTION/Network/Reliable.md` |
| `Server` | 在Client-owned的Actor上（PlayerController或Pawn）执行一个RPC函数，只运行在服务器上。对应的实现函数会添加_Implementation后缀 | UFUNCTION / Network | `Specifier/UFUNCTION/Network/Server.md` |
| `Unreliable` | 指定一个RPC函数为“不可靠的”，当遇见网络错误时就会被丢弃。一般用在传播效果表现的函数上，就算漏掉也没有关系 | UFUNCTION / Network | `Specifier/UFUNCTION/Network/Unreliable.md` |
| `WithValidation` | 指定一个RPC函数在执行前需要验证，只有验证通过才可以执行 | UFUNCTION / Network | `Specifier/UFUNCTION/Network/WithValidation.md` |
| `Blueprintable` | 可以在蓝图中实现 | UINTERFACE / Blueprint | `Specifier/UINTERFACE/Blueprint/Blueprintable.md` |
| `DisplayName` | 更改函数参数在蓝图节点上的显示名字 | UPARAM / Blueprint | `Specifier/UPARAM/Blueprint/DisplayName.md` |
| `ref` | 使得函数的参数变成引用类型 | UPARAM / Blueprint | `Specifier/UPARAM/Blueprint/ref.md` |
| `AdvancedDisplay` | 被折叠到高级栏下，要手动打开。一般用在不太常用的属性上面 | UPROPERTY / DetailsPanel | `Specifier/UPROPERTY/DetaisPanel/AdvancedDisplay.md` |
| `BlueprintReadOnly` | 此属性可由蓝图读取，但不能被修改 | UPROPERTY / Blueprint | `Specifier/UPROPERTY/Blueprint/BlueprintReadOnly.md` |
| `BlueprintReadWrite` | 可从蓝图读取或写入此属性 | UPROPERTY / Blueprint | `Specifier/UPROPERTY/Blueprint/BlueprintReadWrite.md` |
| `Category` | 指定属性的类别，使用 | 运算符定义嵌套类目 | UPROPERTY / DetailsPanel | `Specifier/UPROPERTY/DetaisPanel/Category.md` |
| `EditAnywhere` | 在默认值和实例的细节面板上均可编辑 | UPROPERTY / DetailsPanel | `Specifier/UPROPERTY/DetaisPanel/EditAnywhere.md` |
| `EditDefaultsOnly` | 只能在默认值面板里编辑 | UPROPERTY / DetailsPanel | `Specifier/UPROPERTY/DetaisPanel/EditDefaultsOnly.md` |
| `EditInstanceOnly` | 只能在实例的细节面板上编辑该属性 | UPROPERTY / DetailsPanel | `Specifier/UPROPERTY/DetaisPanel/EditInstanceOnly.md` |
| `Replicated` | 指定该属性应随网络进行复制 | UPROPERTY / Network | `Specifier/UPROPERTY/Network/Replicated.md` |
| `ReplicatedUsing` | 指定一个通知回调函数，在属性通过网络更新后执行 | UPROPERTY / Network | `Specifier/UPROPERTY/Network/ReplicatedUsing.md` |
| `SaveGame` | 在SaveGame存档的时候，只序列化有SaveGame标记的属性，而不序列化别的属性 | UPROPERTY / Serialization | `Specifier/UPROPERTY/Serialization/SaveGame.md` |
| `Transient` | 不序列化该属性，该属性初始化时候会被0填充 | UPROPERTY / Serialization | `Specifier/UPROPERTY/Serialization/Transient.md` |
| `VisibleAnywhere` | 在默认值和实例细节面板均可见，但不可编辑 | UPROPERTY / DetailsPanel | `Specifier/UPROPERTY/DetaisPanel/VisibleAnywhere.md` |
| `VisibleDefaultsOnly` | 在默认值细节面板可见，但不可编辑 | UPROPERTY / DetailsPanel | `Specifier/UPROPERTY/DetaisPanel/VisibleDefaultsOnly.md` |
| `VisibleInstanceOnly` | 在实例细节面板可见，但不可编辑 | UPROPERTY / DetailsPanel | `Specifier/UPROPERTY/DetaisPanel/VisibleInstanceOnly.md` |
| `BlueprintType` | 允许这个结构在蓝图中声明变量 | USTRUCT / Blueprint | `Specifier/USTRUCT/Blueprint/BlueprintType.md` |

## ★★★★

Count: 8

| ID | Summary | Usage | Doc |
|---|---|---|---|
| `BlueprintSpawnableComponent` | 允许该组件出现在Actor蓝图里Add组件的面板里 | UCLASS | `Meta/Component/BlueprintSpawnableComponent.md` |
| `CommutativeAssociativeBinaryOperator` | 标记一个二元运算函数的运算支持交换律和结合律，在蓝图节点上增加一个“+”引脚，允许动态的直接添加多个输入值 | UFUNCTION | `Meta/Blueprint/CommutativeAssociativeBinaryOperator.md` |
| `AdvancedClassDisplay` | 把该类下的所有属性都默认显示在高级目录下 | UCLASS / Category | `Specifier/UCLASS/Category/AdvancedClassDisplay.md` |
| `DefaultToInstanced` | 指定该类的所有实例属性都默认是UPROPERTY(instanced)，即都默认创建新的实例，而不是对对象的引用 | UCLASS / Instance | `Specifier/UCLASS/Instance/DefaultToInstanced.md` |
| `HideCategories` | 在类的ClassDefaults属性面板里隐藏某些Category的属性 | UCLASS / Category | `Specifier/UCLASS/Category/HideCategories.md` |
| `NotBlueprintable` | 不可在蓝图里继承，隐含作用也不可当作变量 | UCLASS / Blueprint | `Specifier/UCLASS/Blueprint/NotBlueprintable.md` |
| `NotBlueprintType` | 不可当做变量类型 | UCLASS / Blueprint | `Specifier/UCLASS/Blueprint/NotBlueprintType.md` |
| `FieldNotify` | 在打开MVVM插件后，使得该属性变成支持FieldNotify的属性 | UPROPERTY / UHT | `Specifier/UPROPERTY/UHT/FieldNotify.md` |

## Excluded

- `★★★` and below stay in category indexes only.
- Missing `常用程度` is treated as `0` and stays in category indexes only.
- `💀`, `changed_in_version`, and `removed_or_deprecated` stay in category indexes for diagnosis and migration only.

