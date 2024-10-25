# Meta = (元数据)

## Actor

| Name                                                                                                                           | 引擎模块                 | 功能描述                                                                                                                                                                                                                                                             | 常用程度  |
|--------------------------------------------------------------------------------------------------------------------------------|----------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|-------|
| [ChildCanTick](Actor/ChildCanTick/ChildCanTick.md)                                                                             | Actor                | 标记允许其蓝图子类可以接受响应Tick事件                                                                                                                                                                                                                                            | ★★★   |
| [ChildCannotTick](Actor/ChildCannotTick.md)                  | Actor | 用于Actor或ActorComponent子类，标记允许其蓝图子类不可以接受响应Tick事件，哪怕父类可以Tick | ★★★      |


## AnimationGraph

| Name                                                         | 引擎模块       | 功能描述                                                     | 常用程度 |
| ------------------------------------------------------------ | -------------- | ------------------------------------------------------------ | -------- |
| [AnimNotifyBoneName](AnimationGraph/AnimNotifyBoneName/AnimNotifyBoneName.md) | AnimationGraph | 使得UAnimNotify或UAnimNotifyState下的FName属性作为BoneName的作用。 | ★★       |
| [AnimBlueprintFunction](AnimationGraph/AnimBlueprintFunction.md) | AnimationGraph | 标明是动画蓝图里的内部纯存根函数，只在动画蓝图编译时设置     | 💀        |
| [CustomizeProperty](AnimationGraph/CustomizeProperty/CustomizeProperty.md) | AnimationGraph | 使用在FAnimNode的成员属性上，告诉编辑器不要为它生成默认Details面板控件，后续会在DetailsCustomization里自定义创建相应的编辑控件。 | ★        |
| [AnimNotifyExpand](AnimationGraph/AnimNotifyExpand.md)       | AnimationGraph | 使得UAnimNotify或UAnimNotifyState下的属性直接展开到细节面板里。 | 💀        |
| [OnEvaluate](AnimationGraph/OnEvaluate.md)                   | AnimationGraph |                                                              | 💀        |
| [FoldProperty](AnimationGraph/FoldProperty/FoldProperty.md)  | AnimationGraph | 在动画蓝图中使得动画节点的某个属性成为FoldProperty。         | ★        |
| [BlueprintCompilerGeneratedDefaults](AnimationGraph/BlueprintCompilerGeneratedDefaults.md) | AnimationGraph | 指定该属性的值是编译器生成的，因此在编译后无需复制，可以加速一些编译性能。 | 💀        |
| [CustomWidget](AnimationGraph/CustomWidget.md)               | AnimationGraph |                                                              | 💀        |
| [AllowedParamType](AnimationGraph/AllowedParamType.md)       | AnimationGraph |                                                              | 💀        |
| [PinShownByDefault](AnimationGraph/PinShownByDefault/PinShownByDefault.md) | AnimationGraph | 在动画蓝图中使得动画节点的某个属性一开始就暴露出来成为引脚，但也可以改变。 | ★★★      |
| [AnimGetter](AnimationGraph/AnimGetter/AnimGetter.md)        | AnimationGraph | 指定UAnimInstance及子类的该函数成为一个AnimGetter函数。      | ★★★      |
| [GetterContext](AnimationGraph/GetterContext/GetterContext.md) | AnimationGraph | 继续限定AnimGetter函数在哪个地方才可以使用，如果不填，则默认都可以用。 | ★★       |


## Asset

| Name                                                         | 引擎模块 | 功能描述                                                     | 常用程度 |
| ------------------------------------------------------------ | -------- | ------------------------------------------------------------ | -------- |
| [RequiredAssetDataTags](Asset/RequiredAssetDataTags/RequiredAssetDataTags.md) | Asset    | 在UObject*属性上指定Tags来进行过滤，必须拥有该Tags才可以被选择。 | ★★       |
| [DisallowedAssetDataTags](Asset/DisallowedAssetDataTags.md)  | Asset    | 在UObject*属性上指定Tags来进行过滤，必须没有拥有该Tags才可以被选择。 | ★★       |
| [ForceShowEngineContent](Asset/ForceShowEngineContent/ForceShowEngineContent.md) | Asset    | 指定UObject*属性的资源可选列表里强制可选引擎的内建资源       | ★★       |
| [ForceShowPluginContent](Asset/ForceShowEngineContent/ForceShowPluginContent.md) | Asset    | 指定UObject*属性的资源可选列表里强制可选其他插件里的内建资源 | 💀        |
| [GetAssetFilter](Asset/GetAssetFilter/GetAssetFilter.md)     | Asset    | 指定一个UFUNCTION来对UObject*属性的可选资源进行排除过滤。    | ★★★      |


## Blueprint

| Name                                                         | 引擎模块  | 功能描述                                                     | 常用程度 |
| ------------------------------------------------------------ | --------- | ------------------------------------------------------------ | -------- |
| [IgnoreTypePromotion](Blueprint/IgnoreTypePromotion/IgnoreTypePromotion.md) | Blueprint | 标记该函数不收录进类型提升函数库                             | ★★       |
| [Variadic](Blueprint/Variadic.md)                            | Blueprint | 指定该函数接受多个参数                                       | ★★★      |
| [ForceAsFunction](Blueprint/ForceAsFunction/ForceAsFunction.md) | Blueprint | 把C++里用BlueprintImplementableEvent或NativeEvent定义的事件强制改为函数在子类中覆写。 | ★★★      |
| [CannotImplementInterfaceInBlueprint](Blueprint/CannotImplementInterfaceInBlueprint.md) | Blueprint | 指定该接口不能在蓝图中实现                                   | ★★★      |
| [CallInEditor](Blueprint/CallInEditor.md)                    | Blueprint | 可以在Actor的细节面板上作为一个按钮来调用该函数。            | ★★★★★    |
| [BlueprintProtected](Blueprint/BlueprintProtected/BlueprintProtected.md) | Blueprint | 指定该函数或属性只能在本类以及子类中被调用或读写，类似C++中的protected作用域限制。不可在别的蓝图类里访问。 | ★★★      |
| [AllowPrivateAccess](Blueprint/AllowPrivateAccess/AllowPrivateAccess.md) | Blueprint | 允许一个在C++中private的属性，可以在蓝图中访问。             | ★★★★★    |
| [BlueprintPrivate](Blueprint/BlueprintPrivate/BlueprintPrivate.md) | Blueprint | 指定该函数或属性只能在本类中被调用或读写，类似C++中的private的作用域限制。不可在别的蓝图类里访问。 | ★★       |
| [CommutativeAssociativeBinaryOperator](Blueprint/CommutativeAssociativeBinaryOperator/CommutativeAssociativeBinaryOperator.md) | Blueprint | 标记一个二元运算函数的运算支持交换律和结合律，在蓝图节点上增加一个“+”引脚，允许动态的直接添加多个输入值。 | ★★★★     |
| [CompactNodeTitle](Blueprint/CompactNodeTitle/CompactNodeTitle.md) | Blueprint | 使得函数的展示形式变成精简压缩模式，同时指定一个新的精简的名字 | ★★★      |
| [CustomStructureParam](Blueprint/Param/CustomStructureParam/CustomStructureParam.md) | Blueprint | 被CustomStructureParam标记的函数参数会变成Wildcard的通配符参数，其引脚的类型会等于连接的变量类型。 | ★★★★★    |
| [DefaultToSelf](Blueprint/DefaultToSelf/DefaultToSelf.md)    | Blueprint | 用在函数上，指定一个参数的默认值为Self值                     | ★★★★★    |
| [ExpandEnumAsExecs](Blueprint/Exec/ExpandEnumAsExecs/ExpandEnumAsExecs.md) | Blueprint | 指定多个enum或bool类型的函数参数，自动根据条目生成相应的多个输入或输出执行引脚，并根据实参值不同来相应改变控制流。 | ★★★★★    |
| [ExpandBoolAsExecs](Blueprint/Exec/ExpandBoolAsExecs.md)     | Blueprint | 是ExpandEnumAsExecs的别名，完全等价其功能。                  | ★★★★★    |
| [ArrayParm](Blueprint/Param/ArrayParm/ArrayParm.md)          | Blueprint | 指定一个函数为使用Array<*>的函数，数组元素类型为通配符的泛型。 | ★★★      |
| [ArrayTypeDependentParams](Blueprint/Param/ArrayTypeDependentParams/ArrayTypeDependentParams.md) | Blueprint | 当ArryParam指定的函数拥有两个或以上Array参数的时候，指定哪些数组参数的类型也应该相应的被更新改变。 | 💀        |
| [AdvancedDisplay](Blueprint/AdvancedDisplay/AdvancedDisplay.md) | Blueprint | 把函数的一些参数折叠起来不显示，需要手动点开下拉箭头来展开编辑。 | ★★★★★    |
| [SetParam](Blueprint/SetParam/SetParam.md)                   | Blueprint | 指定一个函数为使用Set<TItem>的函数，元素类型为通配符的泛型。 | ★★★      |
| [MapParam](Blueprint/Param/MapParam/MapParam.md)             | Blueprint | 指定一个函数为使用TMap<TKey,TValue>的函数，元素类型为通配符的泛型。 | ★★★      |
| [MapKeyParam](Blueprint/Param/MapParam/MapKeyParam.md)       | Blueprint | 指定一个函数参数为Map的Key，其根据MapParam指定的实际Map参数的Key类型而相应改变。 | ★★★      |
| [MapValueParam](Blueprint/Param/MapParam/MapValueParam.md)   | Blueprint | 指定一个函数参数为Map的Value，其根据MapParam指定的实际Map参数的Value类型而相应改变。 | ★★★      |
| [InternalUseParam](Pin/InternalUseParam/InternalUseParam.md) | Blueprint | 用在函数调用上，指定要隐藏的参数名称，也可以隐藏返回值。可以隐藏多个 | ★★★★★    |
| [Keywords](Blueprint/Keywords/Keywords.md)                   | Blueprint | 指定一系列关键字用于在蓝图内右键找到该函数                   | ★★★★★    |
| [Latent](Blueprint/Latent/Latent.md)                         | Blueprint | 标明一个函数是一个延迟异步操作                               | ★★★★★    |
| [NeedsLatentFixup](Blueprint/Latent/NeedsLatentFixup.md)     | Blueprint | 用在FLatentActionInfo::Linkage属性上，告诉蓝图VM生成跳转信息 | ★        |
| [LatentInfo](Blueprint/Latent/LatentInfo.md)                 | Blueprint | 和Latent配合，指明哪个函数参数是LatentInfo参数。             | ★★★      |
| [LatentCallbackTarget](Blueprint/Latent/LatentCallbackTarget.md) | Blueprint | 用在FLatentActionInfo::CallbackTarget属性上，告诉蓝图VM在哪个对象上调用函数。 | ★        |
| [NativeMakeFunc](Blueprint/NativeMakeFunc/NativeMakeFunc.md) | Blueprint | 指定一个函数采用MakeStruct的图标                             | ★        |
| [NativeBreakFunc](Blueprint/NativeBreakFunc.md)              | Blueprint | 指定一个函数采用BreakStruct的图标。                          | ★        |
| [UnsafeDuringActorConstruction](Blueprint/UnsafeDuringActorConstruction/UnsafeDuringActorConstruction.md) | Blueprint | 标明该函数不能在Actor的构造函数里调用                        | ★★       |
| [BlueprintAutocast](Blueprint/BlueprintAutocast/BlueprintAutocast.md) | Blueprint | 告诉蓝图系统这个函数是用来支持从A类型到B类型的自动转换。     | ★        |
| [DeterminesOutputType](Blueprint/Param/DeterminesOutputType/DeterminesOutputType.md) | Blueprint | 指定一个参数的类型作为函数动态调整输出参数类型的参考类型     | ★★★      |
| [DynamicOutputParam](Blueprint/Param/DynamicOutputParam.md)  | Blueprint | 配合DeterminesOutputType，指定多个支持动态类型的输出参数。   | 💀        |
| [ReturnDisplayName](Blueprint/ReturnDisplayName/ReturnDisplayName.md) | Blueprint | 改变函数返回值的名字，默认是ReturnValue                      | ★★★★★    |
| [WorldContext](Blueprint/WorldContext/WorldContext.md)       | Blueprint | 指定函数的一个参数自动接收WorldContext对象，以便确定当前运行所处于的World | ★★★★★    |
| [ShowWorldContextPin](Blueprint/ShowWorldContextPin/ShowWorldContextPin.md) | Blueprint | 放在UCLASS上，指定本类里的函数调用都必须显示WorldContext引脚，无论其本来是否默认隐藏 | 💀        |
| [CallableWithoutWorldContext](Blueprint/CallableWithoutWorldContext/CallableWithoutWorldContext.md) | Blueprint | 让函数也可以脱离WorldContextObject而使用                     | 💀        |
| [AutoCreateRefTerm](Blueprint/Param/AutoCreateRefTerm/AutoCreateRefTerm.md) | Blueprint | 指定函数的多个输入引用参数在没有连接的时候自动为其创建默认值 | ★★★★★    |
| [ProhibitedInterfaces](Blueprint/ProhibitedInterfaces/ProhibitedInterfaces.md) | Blueprint | 列出与蓝图类不兼容的接口，阻止实现                           | ★★       |
| [HiddenNode](Blueprint/HiddenNode/HiddenNode.md)             | Blueprint | 把指定的UBTNode隐藏不在右键菜单中显示。                      | ★        |
| [HideFunctions](Blueprint/HideFunctions.md)                  | Blueprint | 在属性查看器中不显示指定类别中的所有函数。                   | ★★★      |
| [ExposedAsyncProxy](Blueprint/ExposedAsyncProxy/ExposedAsyncProxy.md) | Blueprint | 在 Async Task 节点中公开此类的一个代理对象。                 | ★★★      |
| [HasDedicatedAsyncNode](Blueprint/HasDedicatedAsyncNode/HasDedicatedAsyncNode.md) | Blueprint |                                                              | 💀        |
| [HideThen](Blueprint/HideThen/HideThen.md)                   | Blueprint | 隐藏异步蓝图节点的Then引脚                                   | 💀        |
| [HideSpawnParms](Blueprint/Param/HideSpawnParms/HideSpawnParms.md) | Blueprint | 在UGamelayTask子类生成的蓝图异步节点上隐藏UGamelayTask子类继承链中某些属性。 | 💀        |
| [NotInputConfigurable](Blueprint/NotInputConfigurable/NotInputConfigurable.md) | Blueprint | 让一些UInputModifier和UInputTrigger不能在ProjectSettings里配置。 | ★        |
| [BlueprintThreadSafe](Blueprint/BlueprintThreadSafe/BlueprintThreadSafe.md) | Blueprint | 用在类上或函数上，标记类里的函数都是线程安全的。 这样就可以在动画蓝图等非游戏线程被调用了。 | ★★★      |
| [NotBlueprintThreadSafe](Blueprint/NotBlueprintThreadSafe.md) | Blueprint | 用在函数上，标记这个函数是不线程安全的                       | ★        |
| [RestrictedToClasses](Blueprint/RestrictedToClasses/RestrictedToClasses.md) | Blueprint | 限制蓝图函数库下的函数只能在RestrictedToClasses指定的类蓝图中右键创建出来 | ★★★      |
| [DontUseGenericSpawnObject](Blueprint/DontUseGenericSpawnObject/DontUseGenericSpawnObject.md) | Blueprint | 阻止使用蓝图中的Generic Create Object节点来生成本类的对象。  | ★★       |
| [ObjectSetType](Blueprint/ObjectSetType/ObjectSetType.md)    | Blueprint | 指定统计页面的对象集合类型。                                 | ★        |
| [SparseClassDataTypes](Blueprint/SparseClassDataTypes.md)    | Blueprint |                                                              | ★★★      |
| [KismetHideOverrides](Blueprint/KismetHideOverrides/KismetHideOverrides.md) | Blueprint | 不允许被覆盖的蓝图事件的列表。                               | 💀        |
| [BlueprintType](Blueprint/BlueprintType.md)                  | Blueprint | 表明可以作为一个蓝图变量                                     | ★★★★★    |
| [IsConversionRoot](Blueprint/IsConversionRoot.md)            | Blueprint | 允许Actor在自身以及子类之间做转换                            | ★★★      |
| [BlueprintInternalUseOnlyHierarchical](Blueprint/BlueprintInternalUseOnlyHierarchical.md) | Blueprint | 标明该结构及其子类都不暴露给用户定义和使用，均只能在蓝图系统内部使用 | ★        |
| [BlueprintSetter](Blueprint/BlueprintSetter.md)              | Blueprint | 采用一个自定义的set函数来读取。 会默认设置BlueprintReadWrite. | ★★★      |
| [DisplayName](Blueprint/DisplayName.md)                      | Blueprint | 此节点在蓝图中的命名将被此处提供的值所取代，而非代码生成的命名。 | ★★★★★    |
| [ExposeOnSpawn](Blueprint/ExposeOnSpawn/ExposeOnSpawn.md)    | Blueprint | 使该属性在ContructObject或SpawnActor等创建对象的时候暴露出来。 | ★★★★★    |
| [NativeConst](Blueprint/NativeConst.md)                      | Blueprint | 指定有C++里的const标志                                       | ★        |
| [CPP_Default_XXX](Blueprint/CPP_Default_XXX.md)              | Blueprint | XXX=参数名字                                                 | ★★★★★    |
| [BlueprintGetter](Blueprint/BlueprintGetter.md)              | Blueprint | 采用一个自定义的get函数来读取。 如果没有设置BlueprintSetter或BlueprintReadWrite, 则会默认设置BlueprintReadOnly. | ★★★      |
| [IsBlueprintBase](Blueprint/IsBlueprintBase.md)              | Blueprint | 说明此类是否为创建蓝图的一个可接受基类，与 UCLASS 说明符、Blueprintable 或 'NotBlueprintable` 相似。 | ★★★★★    |
| [BlueprintInternalUseOnly](Blueprint/BlueprintInternalUseOnly.md) | Blueprint | 标明该元素是作为蓝图系统的内部调用或使用，不暴露出来在用户层面直接定义或使用。 | ★★★      |


## Component

| Name                                                         | 引擎模块  | 功能描述                                                     | 常用程度 |
| ------------------------------------------------------------ | --------- | ------------------------------------------------------------ | -------- |
| [UseComponentPicker](Component/UseComponentPicker/UseComponentPicker.md) | Component | 用在ComponentReference属性上，使得选取器的列表里展示出Actor属下的Component以便选择。 | ★★       |
| [AllowAnyActor](Component/AllowAnyActor.md)                  | Component | 用在ComponentReference属性上，在UseComponentPicker的情况下使得组件选取器扩大到场景里其他Actor下的其他组件。 | ★★       |
| [BlueprintSpawnableComponent](Component/BlueprintSpawnableComponent/BlueprintSpawnableComponent.md) | Component | 允许该组件出现在Actor蓝图里Add组件的面板里。                 | ★★★★     |


## Config

| Name                                                                                                                           | 引擎模块                 | 功能描述                                                                                                                                                                                                                                                             | 常用程度  |
|--------------------------------------------------------------------------------------------------------------------------------|----------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|-------|
| [ConsoleVariable](Config/ConsoleVariable/ConsoleVariable.md)                                                                   | Config               | 把一个Conifg属性的值同步到一个同名的控制台变量。                                                                                                                                                                                                                                      | ★★★★★ |
| [EditorConfig](Config/EditorConfig.md)                                                                                         | Config               | 保存编辑器的配置                                                                                                                                                                                                                                                         | ★★★   |
| [ConfigHierarchyEditable](Config/ConfigHierarchyEditable/ConfigHierarchyEditable.md)                                           | Config               | 使得一个属性可以在Config的各个层级配置。                                                                                                                                                                                                                                          | ★★★   |
| [ConfigRestartRequired](Config/ConfigRestartRequired/ConfigRestartRequired.md)                                                 | Config               | 使属性在设置里改变后弹出重启编辑器的对话框。                                                                                                                                                                                                                                           | ★★★   |


## Container

| Name                                                         | 引擎模块  | 功能描述                                                     | 常用程度 |
| ------------------------------------------------------------ | --------- | ------------------------------------------------------------ | -------- |
| [ReadOnlyKeys](Container/ReadOnlyKeys/ReadOnlyKeys.md)       | Container | 使TMap属性的Key不能编辑。                                    | ★★       |
| [ArraySizeEnum](Container/ArraySizeEnum/ArraySizeEnum.md)    | Container | 为固定数组提供一个枚举，使得数组元素按照枚举值来作为索引和显示。 | ★★★      |
| [TitleProperty](Container/TitleProperty/TitleProperty.md)    | Container | 指定结构数组里的结构成员属性内容来作为结构数组元素的显示标题。 | ★★       |
| [EditFixedOrder](Container/EditFixedOrder/EditFixedOrder.md) | Container | 使数组的元素无法通过拖拽来重新排序。                         | ★★       |
| [NoElementDuplicate](Container/NoElementDuplicate/NoElementDuplicate.md) | Container | 去除TArray属性里数据项的Duplicate菜单项按钮。                | ★        |


## Debug

| Name                                                                                                                           | 引擎模块                 | 功能描述                                                                                                                                                                                                                                                             | 常用程度  |
|--------------------------------------------------------------------------------------------------------------------------------|----------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|-------|
| [DebugTreeLeaf](Debug/DebugTreeLeaf/DebugTreeLeaf.md)                                                                          | Debug                | 阻止BlueprintDebugger展开该类的属性以加速编辑器里调试器的性能                                                                                                                                                                                                                          | ★     |


## DetailsPanel

| Name                                                         | 引擎模块     | 功能描述                                                     | 常用程度 |
| ------------------------------------------------------------ | ------------ | ------------------------------------------------------------ | -------- |
| [HideInDetailPanel](DetailsPanel/HideInDetailPanel/HideInDetailPanel.md) | DetailsPanel | 在Actor的事件面板里隐藏该动态多播委托属性。                  | ★★       |
| [DisplayAfter](DetailsPanel/DisplayAfter/DisplayAfter.md)    | DetailsPanel | 使本属性在指定的属性之后显示。                               | ★★★      |
| [EditCondition](DetailsPanel/EditCondition/EditCondition.md) | DetailsPanel | 给一个属性指定另外一个属性或者表达式来作为是否可编辑的条件。 | ★★★★★    |
| [EditConditionHides](DetailsPanel/EditConditionHides/EditConditionHides.md) | DetailsPanel | 在已经有EditCondition的情况下，指定该属性在EditCondition不满足的情况下隐藏起来。 | ★★★★★    |
| [InlineEditConditionToggle](DetailsPanel/InlineEditConditionToggle/InlineEditConditionToggle.md) | DetailsPanel | 使这个bool属性在被用作EditCondition的时候内联到对方的属性行里成为一个单选框，而不是自己成为一个编辑行。 | ★★★★★    |
| [HideEditConditionToggle](DetailsPanel/HideEditConditionToggle/HideEditConditionToggle.md) | DetailsPanel | 用在使用EditCondition的属性上，表示该属性不想要其EditCondition用到的属性被隐藏起来。 | ★★★★★    |
| [DisplayPriority](DetailsPanel/DisplayPriority/DisplayPriority.md) | DetailsPanel | 指定本属性在细节面板的显示顺序优先级，越小的优先级越高。     | ★★★      |
| [AdvancedClassDisplay](DetailsPanel/AdvancedClassDisplay.md) | DetailsPanel | 指定该类型的变量在高级显示里显示                             | ★★★      |
| [bShowOnlyWhenTrue](DetailsPanel/bShowOnlyWhenTrue/bShowOnlyWhenTrue.md) | DetailsPanel | 根据编辑器config配置文件里字段值来决定当前属性是否显示。     | ★        |
| [PrioritizeCategories](DetailsPanel/PrioritizeCategories.md) | DetailsPanel | 把指定的属性目录优先显示在前面                               | ★★★      |
| [AutoExpandCategories](DetailsPanel/AutoExpandCategories.md) | DetailsPanel | 指定类内部的属性目录自动展开起来                             | ★★★      |
| [AutoCollapseCategories](DetailsPanel/AutoCollapseCategories.md) | DetailsPanel | 指定类内部的属性目录自动折叠起来                             | ★★★      |
| [ClassGroupNames](DetailsPanel/ClassGroupNames.md)           | DetailsPanel | 指定ClassGroup的名字                                         | ★★★      |
| [MaxPropertyDepth](DetailsPanel/MaxPropertyDepth/MaxPropertyDepth.md) | DetailsPanel | 指定对象或结构在细节面板里展开的层数。                       | ★        |
| [DeprecatedNode](DetailsPanel/DeprecatedNode/DeprecatedNode.md) | DetailsPanel | 用于BehaviorTreeNode或EnvQueryNode，说明该类已废弃，在编辑器中红色错误展示并有错误ToolTip提示 | ★★       |
| [UsesHierarchy](DetailsPanel/UsesHierarchy.md)               | DetailsPanel | 说明类使用层级数据。用于实例化“细节”面板中的层级编辑功能。   | 💀        |
| [IgnoreCategoryKeywordsInSubclasses](DetailsPanel/IgnoreCategoryKeywordsInSubclasses.md) | DetailsPanel | 用于让一个类的首个子类忽略所有继承的 ShowCategories 和 HideCategories 说明符。 | ★        |
| [NoResetToDefault](DetailsPanel/NoResetToDefault/NoResetToDefault.md) | DetailsPanel | 禁用和隐藏属性在细节面板上的“重置”功能。                     | ★★★      |
| [ReapplyCondition](DetailsPanel/ReapplyCondition.md)         | DetailsPanel | // Properties that have a ReapplyCondition should be disabled behind the specified property when in reapply mode | ★        |
| [HideBehind](DetailsPanel/HideBehind.md)                     | DetailsPanel | 只在指定的属性为true或不为空的时候本属性才显示               | ★        |
| [Category](DetailsPanel/Category.md)                         | DetailsPanel | 指定属性在细节面板中的分类                                   | ★★★★★    |
| [HideCategories](DetailsPanel/HideCategories.md)             | DetailsPanel | 隐藏的类别                                                   | ★★★      |
| [ShowCategories](DetailsPanel/ShowCategories.md)             | DetailsPanel | 显示类别                                                     | 💀        |
| [EditInline](DetailsPanel/EditInline/EditInline.md)          | DetailsPanel | 为对象属性创建一个实例，并作为子对象。                       | ★★★      |
| [NoEditInline](DetailsPanel/NoEditInline.md)                 | DetailsPanel | Object properties pointing to an UObject instance whos class is marked editinline will not show their properties inline in property windows. Useful for getting actor components to appear in the component tree but not inline in the root actor details panel. | 💀        |
| [AllowEditInlineCustomization](DetailsPanel/AllowEditInlineCustomization/AllowEditInlineCustomization.md) | DetailsPanel | 允许EditInline的对象属性可以自定义属性细节面板来编辑该对象内的数据。 | ★        |
| [ForceInlineRow](DetailsPanel/ForceInlineRow/ForceInlineRow.md) | DetailsPanel | 强制TMap属性里的结构key和其他Value合并到同一行来显示         | ★        |


## Development

| Name                                                         | 引擎模块    | 功能描述                                                     | 常用程度 |
| ------------------------------------------------------------ | ----------- | ------------------------------------------------------------ | -------- |
| [DeprecatedProperty](Development/DeprecatedProperty/DeprecatedProperty.md) | Development | 标记弃用，引用到该属性的蓝图会触发一个警告                   | ★        |
| [Deprecated](Development/Deprecated/Deprecated.md)           | Development | 指定该元素要废弃的引擎版本号。                               | ★        |
| [DevelopmentOnly](Development/DevelopmentOnly/DevelopmentOnly.md) | Development | 使得一个函数变为DevelopmentOnly，意味着只会在Development模式中运行。适用于调试输出之类的功能，但在最终发布版中会跳过。 | ★        |
| [DeprecationMessage](Development/DeprecationMessage.md)      | Development | 定义弃用的消息                                               | ★        |
| [DeprecatedFunction](Development/DeprecatedFunction.md)      | Development | 标明一个函数已经被弃用                                       | ★        |
| [Comment](Development/Comment/Comment.md)                    | Development | 用来记录注释的内容                                           | ★★★      |
| [FriendlyName](Development/FriendlyName.md)                  | Development | 和DisplayName一样？                                          | 💀        |
| [DevelopmentStatus](Development/DevelopmentStatus.md)        | Development | 标明开发状态                                                 | ★        |
| [ToolTip](Development/ToolTip/ToolTip.md)                    | Development | 在Meta里提供一个提示文本，覆盖代码注释里的文本               | ★★★      |
| [ShortTooltip](Development/ShortTooltip.md)                  | Development | 提供一个更简洁版本的提示文本，例如在类型选择器的时候显示     | 💀        |


## Enum

| Name                                                         | 引擎模块 | 功能描述                                                     | 常用程度 |
| ------------------------------------------------------------ | -------- | ------------------------------------------------------------ | -------- |
| [EnumDisplayNameFn](Enum/EnumDisplayNameFn/EnumDisplayNameFn.md) | Enum     | 在Runtime下为枚举字段提供自定义名称的函数回调                | ★★       |
| [Bitflags](Enum/Bitflags/Bitflags.md)                        | Enum     | 设定一个枚举支持采用位标记赋值，从而在蓝图中可以识别出来是BitMask | ★★★★★    |
| [UseEnumValuesAsMaskValuesInEditor](Enum/UseEnumValuesAsMaskValuesInEditor/UseEnumValuesAsMaskValuesInEditor.md) | Enum     | 指定枚举值已经是位移后的值，而不是位标记的索引下标。         | ★★       |
| [Spacer](Enum/UMETA/Spacer.md)                               | Enum     | 隐藏UENUM的某个值                                            | ★★★★★    |
| [ValidEnumValues](Enum/ValidEnumValues/ValidEnumValues.md)   | Enum     | 指定枚举属性值上可选的枚举值选项                             | ★★★      |
| [InvalidEnumValues](Enum/InvalidEnumValues.md)               | Enum     | 指定枚举属性值上不可选的枚举值选项，用以排除一些选项         | ★★★      |
| [GetRestrictedEnumValues](Enum/GetRestrictedEnumValues.md)   | Enum     | 指定一个函数来指定枚举属性值的哪些枚举选项是禁用的           | ★★★      |
| [EnumValueDisplayNameOverrides](Enum/EnumValueDisplayNameOverrides/EnumValueDisplayNameOverrides.md) | Enum     | 改变枚举属性值上的显示名字                                   | ★★       |
| [Enum](Enum/Enum.md)                                         | Enum     | 给一个String指定以枚举里值的名称作为选项                     | ★★★      |
| [DisplayName](Enum/UMETA/DisplayName/DisplayName)            | Enum     | 改变枚举值的显示名称                                         | ★★★★★    |
| [Hidden](Enum/UMETA/Hidden/Hidden)                           | Enum     | 隐藏UENUM的某个值                                            | ★★★★★    |
| [DisplayValue](Enum/UMETA/DisplayValue.md)                   | Enum     | Enum /Script/Engine.AnimPhysCollisionType                    | 💀        |
| [Grouping](Enum/UMETA/Grouping.md)                           | Enum     | Enum /Script/Engine.EAlphaBlendOption                        | 💀        |
| [TraceQuery](Enum/UMETA/TraceQuery.md)                       | Enum     | Enum /Script/Engine.ECollisionChannel                        | 💀        |
| [Bitmask](Enum/BitmaskEnum/BitmaskEnum.md)                   | Enum     | 设定一个属性采用Bitmask赋值                                  | ★★★★★    |
| [BitmaskEnum](Enum/BitmaskEnum/BitmaskEnum.md)               | Enum     | 使用位标记后采用的枚举名字                                   | ★★★★★    |


## FieldNotify

| Name                                                                                                                           | 引擎模块                 | 功能描述                                                                                                                                                                                                                                                             | 常用程度  |
|--------------------------------------------------------------------------------------------------------------------------------|----------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|-------|
| [FieldNotifyInterfaceParam](UHT/FieldNotifyInterfaceParam/FieldNotifyInterfaceParam.md)                                        | FieldNotify          | 指定函数的某个参数提供FieldNotify的ViewModel信息。                                                                                                                                                                                                                              | ★★★   |


## GAS

| Name                                                                                                                           | 引擎模块                 | 功能描述                                                                                                                                                                                                                                                             | 常用程度  |
|--------------------------------------------------------------------------------------------------------------------------------|----------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|-------|
| [HideInDetailsView](GAS/HideInDetailsView/HideInDetailsView.md)                                                                | GAS                  | 把该UAttributeSet子类里的属性隐藏在FGameplayAttribute的选项列表里。                                                                                                                                                                                                                | ★★★   |
| [SystemGameplayAttribute](GAS/SystemGameplayAttribute/SystemGameplayAttribute.md)                                              | GAS                  | 把UAbilitySystemComponent子类里面的属性暴露到FGameplayAttribute 选项框里。                                                                                                                                                                                                       | ★★★   |
| [HideFromModifiers](GAS/HideFromModifiers/HideFromModifiers.md)                                                                | GAS                  | 指定AttributeSet下的某属性不出现在GameplayEffect下的Modifiers的Attribute选择里。                                                                                                                                                                                                   | ★★★   |


## Material

| Name                                                         | 引擎模块 | 功能描述                                                     | 常用程度 |
| ------------------------------------------------------------ | -------- | ------------------------------------------------------------ | -------- |
| [MaterialParameterCollectionFunction](Material/MaterialParameterCollectionFunction/MaterialParameterCollectionFunction.md) | Material | 指定该函数是用于操作UMaterialParameterCollection，从而支持ParameterName的提取和验证 | ★★★      |
| [MaterialNewHLSLGenerator](Material/MaterialNewHLSLGenerator/MaterialNewHLSLGenerator.md) | Material | 标识该UMaterialExpression为采用新HLSL生成器的节点，当前在材质蓝图右键菜单中隐藏。 | ★        |
| [ShowAsInputPin](Material/ShowAsInputPin/ShowAsInputPin.md)  | Material | 使得UMaterialExpression里的一些基础类型属性变成材质节点上的引脚。 | ★★★      |
| [MaterialControlFlow](Material/MaterialControlFlow/MaterialControlFlow.md) | Material | 标识该UMaterialExpression为一个控制流节点，当前在材质蓝图右键菜单中隐藏。 | ★        |
| [OverridingInputProperty](Material/OverridingInputProperty/OverridingInputProperty.md) | Material | 在UMaterialExpression中指定本float要覆盖的其他FExpressionInput 属性。 | ★★★      |
| [RequiredInput](Material/RequiredInput.md)                   | Material | 在UMaterialExpression中指定FExpressionInput属性是否要求输入，引脚显示白色或灰色。 | 💀        |
| [Private](Material/Private/Private.md)                       | Material | 标识该UMaterialExpression为私有节点，当前在材质蓝图右键菜单中隐藏。 | ★        |


## Niagara

| Name                                                      | 引擎模块 | 功能描述                                      | 常用程度 |
| --------------------------------------------------------- | -------- | --------------------------------------------- | -------- |
| [NiagaraClearEachFrame](Niagara/NiagaraClearEachFrame.md) | Niagara  | ScriptStruct /Script/Niagara.NiagaraSpawnInfo | 💀        |
| [NiagaraInternalType](Niagara/NiagaraInternalType.md)     | Niagara  | 指定该结构的类型为Niagara的内部类型。         | 💀        |


## Numeric

| Name                                                         | 引擎模块 | 功能描述                                                     | 常用程度 |
| ------------------------------------------------------------ | -------- | ------------------------------------------------------------ | -------- |
| [CtrlMultiplier](Numeric/CtrlMultiplier/CtrlMultiplier.md)   | Numeric  | 指定数字输入框在Ctrl按下时鼠标轮滚动和鼠标拖动改变值的倍率。 | ★★       |
| [ShiftMultiplier](Numeric/ShiftMultiplier.md)                | Numeric  | 指定数字输入框在Shift按下时鼠标轮滚动和鼠标拖动改变值的倍率。 | ★★       |
| [SliderExponent](Numeric/SliderExponent/SliderExponent.md)   | Numeric  | 指定数字输入框上滚动条拖动的变化指数分布                     | ★★★★★    |
| [Multiple](Numeric/Multiple/Multiple.md)                     | Numeric  | 指定数字的值必须是Mutliple提供的值的整数倍。                 | ★★★      |
| [Units](Numeric/Units/Units.md)                              | Numeric  | 设定属性值的单位，支持实时根据数值不同动态改变显示的单位。   | ★★★      |
| [ForceUnits](Numeric/ForceUnits.md)                          | Numeric  | 固定设定属性值的单位保持不变，不根据数值动态调整显示单位。   | ★★★      |
| [Delta](Numeric/Delta/Delta.md)                              | Numeric  | 设定数字输入框值改变的幅度为Delta的倍数                      | ★★★      |
| [LinearDeltaSensitivity](Numeric/LinearDeltaSensitivity.md)  | Numeric  | 在设定Delta后，进一步设定数字输入框变成线性改变以及改变的敏感度（值越大越不敏感） | ★★★      |
| [UIMin](Numeric/UIMin/UIMin.md)                              | Numeric  | 指定数字输入框上滚动条拖动的最小范围值                       | ★★★★★    |
| [UIMax](Numeric/UIMax.md)                                    | Numeric  | 指定数字输入框上滚动条拖动的最大范围值                       | ★★★★★    |
| [ClampMin](Numeric/ClampMin.md)                              | Numeric  | 指定数字输入框实际接受的最小值                               | ★★★★★    |
| [ClampMax](Numeric/ClampMax.md)                              | Numeric  | 指定数字输入框实际接受的最大值                               | ★★★★★    |
| [SupportDynamicSliderMinValue](Numeric/SupportDynamicSliderMinValue/SupportDynamicSliderMinValue.md) | Numeric  | 支持数字输入框上滚动条的最小范围值在Alt按下时被动态改变      | ★        |
| [SupportDynamicSliderMaxValue](Numeric/SupportDynamicSliderMaxValue.md) | Numeric  | 支持数字输入框上滚动条的最大范围值在Alt按下时被动态改变      | ★        |
| [ArrayClamp](Numeric/ArrayClamp/ArrayClamp.md)               | Numeric  | 限定整数属性的值必须在指定数组的合法下标范围内，[0,ArrayClamp.Size()-1] | ★★★      |
| [HideAlphaChannel](Numeric/HideAlphaChannel/HideAlphaChannel.md) | Numeric  | 使FColor或FLinearColor属性在编辑的时候隐藏Alpha通道。        | ★★★      |
| [AllowPreserveRatio](Numeric/AllowPreserveRatio/AllowPreserveRatio.md) | Numeric  | 在细节面板上为FVector属性添加一个比率锁。                    | ★★★      |
| [NoSpinbox](Numeric/NoSpinbox/NoSpinbox.md)                  | Numeric  | 使数值属性禁止默认的拖放和滚轮的UI编辑功能，数值属性包括int系列以及float系列。 | ★★       |
| [sRGB](Numeric/sRGB.md)                                      | Numeric  | 使FColor或FLinearColor属性在编辑的时候采用sRGB方式。         | 💀        |
| [WheelStep](Numeric/WheelStep/WheelStep.md)                  | Numeric  | 指定数字输入框上鼠标轮上下滚动产生的变化值                   | ★★★      |
| [InlineColorPicker](Numeric/InlineColorPicker/InlineColorPicker.md) | Numeric  | 使FColor或FLinearColor属性在编辑的时候直接内联一个颜色选择器。 | ★★       |
| [ShowNormalize](Numeric/ShowNormalize/ShowNormalize.md)      | Numeric  | 使得FVector变量在细节面板出现一个正规化的按钮。              | ★★★      |
| [ColorGradingMode](Numeric/ColorGradingMode/ColorGradingMode.md) | Numeric  | 使得一个FVector4属性成为颜色显示                             | ★★       |


## Object

| Name                                                         | 引擎模块 | 功能描述                                                     | 常用程度 |
| ------------------------------------------------------------ | -------- | ------------------------------------------------------------ | -------- |
| [DisplayThumbnail](Object/DisplayThumbnail/DisplayThumbnail.md) | Object   | 指定是否在该属性左侧显示一个缩略图。                         | ★★★      |
| [ThumbnailSize](Object/ThumbnailSize.md)                     | Object   | 改变缩略图的大小。                                           | 💀        |
| [LoadBehavior](Object/LoadBehavior/LoadBehavior.md)          | Object   | 用在UCLASS上标记这个类的加载行为，使得相应的TObjectPtr属性支持延迟加载。可选的加载行为默认为Eager，可改为LazyOnDemand。 | ★        |
| [ShowInnerProperties](Object/ShowInnerProperties/ShowInnerProperties.md) | Object   | 在属性细节面板中显示对象引用的内部属性                       | ★★★★★    |
| [ShowOnlyInnerProperties](Object/ShowOnlyInnerProperties/ShowOnlyInnerProperties.md) | Object  | 把结构属性的内部属性直接上提一个层级直接展示                 | ★★★      |
| [FullyExpand](Object/FullyExpand.md)                         | Object   |                                                              | 💀        |
| [CollapsableChildProperties](Object/CollapsableChildProperties.md) | Object  | 在TextureGraph模块中新增加的meta。用于折叠一个结构的内部属性。 | 💀        |
| [Untracked](Object/Untracked/Untracked.md)                   | Object   | 使得TSoftObjectPtr和FSoftObjectPath的软对象引用类型的属性，不跟踪记录资产的 。 | ★        |
| [HideAssetPicker](Object/HideAssetPicker/HideAssetPicker.md) | Object   | 隐藏Object类型引脚上的AssetPicker的选择列表                  | ★★       |
| [AssetBundles](Object/AssetBundles/AssetBundles.md)          | Object   | 标明该属性其引用的资产属于哪一些AssetBundles。               | ★★★      |
| [IncludeAssetBundles](Object/IncludeAssetBundles/IncludeAssetBundles.md) | Object   | 用于UPrimaryDataAsset的子对象属性，指定应该继续递归到该子对象里去探测AssetBundle数据。 | ★★       |
| [MustBeLevelActor](Object/MustBeLevelActor.md)               | Object   |                                                              |          |
| [ExposeFunctionCategories](Object/ExposeFunctionCategories/ExposeFunctionCategories.md) | Object   | 指定该Object属性所属于的类里的某些目录下的函数可以直接在本类上暴露出来。 | ★★★      |


## Path

| Name                                                         | 引擎模块 | 功能描述                                                     | 常用程度 |
| ------------------------------------------------------------ | -------- | ------------------------------------------------------------ | -------- |
| [ContentDir](Path/ContentDir/ContentDir.md)                  | Path     | 使用UE的风格来选择Content以及子目录。                        | ★★★      |
| [RelativePath](Path/RelativePath.md)                         | Path     | 使得系统目录选择对话框的结果为当前运行exe的相对路径。        | 💀        |
| [RelativeToGameContentDir](Path/RelativeToGameContentDir.md) | Path     | 使得系统目录选择对话框的结果为相对Content的相对路径。        | 💀        |
| [RelativeToGameDir](Path/RelativeToGameDir/RelativeToGameDir.md) | Path     | 如果系统目录选择框的结果为Project的子目录，则转换为相对路径，否则返回绝对路径。 | ★★★      |
| [LongPackageName](Path/LongPackageName.md)                   | Path     | 使用UE的风格来选择Content以及子目录，或者把文件路径转换为长包名。 | ★★★      |
| [FilePathFilter](Path/FilePathFilter.md)                     | Path     | 设定文件选择器的扩展名，规则符合系统对话框的格式规范，可以填写多个扩展名。 | ★★★      |


## Pin

| Name                                                                                                                           | 引擎模块                 | 功能描述                                                                                                                                                                                                                                                             | 常用程度  |
|--------------------------------------------------------------------------------------------------------------------------------|----------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|-------|
| [HidePin](Pin/HidePin/HidePin.md)                                                                                              | Pin                  | 用在函数调用上，指定要隐藏的参数名称，也可以隐藏返回值。可以隐藏多个参数                                                                                                                                                                                                                             | ★★    |
| [InternalUseParam](Pin/InternalUseParam/InternalUseParam.md)                                                                   | Pin                  | 用在函数调用上，指定要隐藏的参数名称，也可以隐藏返回值。可以隐藏多个参数                                                                                                                                                                                                                             | ★★    |
| [HideSelfPin](Pin/HideSelfPin/HideSelfPin.md)                                                                                  | Pin                  | 用在函数调用上，隐藏默认的SelfPin，也就是Target，导致该函数只能在OwnerClass内调用。                                                                                                                                                                                                            | ★★    |
| [DataTablePin](Pin/DataTablePin/DataTablePin.md)                                                                               | Pin                  | 指定一个函数参数为DataTable或CurveTable类型，以便为FName的其他参数提供RowNameList的选择。                                                                                                                                                                                                   | ★★    |
| [DisableSplitPin](Pin/DisableSplitPin/DisableSplitPin.md)                                                                      | Pin                  | 禁用Struct的split功能                                                                                                                                                                                                                                                 | ★★    |
| [HiddenByDefault](Pin/HiddenByDefault/HiddenByDefault.md)                                                                      | Pin                  | Struct的Make Struct和Break Struct节点中的引脚默认为隐藏状态                                                                                                                                                                                                                     | ★     |
| [AlwaysAsPin](AnimationGraph/AlwaysAsPin/AlwaysAsPin.md)                                                                       | Pin                  | 在动画蓝图中使得动画节点的某个属性总是暴露出来成为引脚                                                                                                                                                                                                                                      | ★★★   |
| [NeverAsPin](AnimationGraph/NeverAsPin/NeverAsPin.md)                                                                          | Pin                  | 在动画蓝图中使得动画节点的某个属性总是不暴露出来成为引脚                                                                                                                                                                                                                                     | ★★★   |
| [PinHiddenByDefault](Pin/PinHiddenByDefault/PinHiddenByDefault.md)                                                             | Pin                  | 使得这个结构里的属性在蓝图里作为引脚时默认是隐藏的。                                                                                                                                                                                                                                       | ★★    |


## RigVMStruct

| Name                                                         | 引擎模块    | 功能描述                                                 | 常用程度 |
| ------------------------------------------------------------ | ----------- | -------------------------------------------------------- | -------- |
| [Input](RigVM/Input/Input.md)                                | RigVMStruct | 指定FRigUnit下的该属性作为输入引脚。                     | ★★★★★    |
| [Constant](RigVM/Constant.md)                                | RigVMStruct | 标识一个属性成为一个常量的引脚。                         | ★★★      |
| [Output](RigVM/Output.md)                                    | RigVMStruct | 指定FRigUnit下的该属性作为输出引脚。                     | ★★★★★    |
| [Visible](RigVM/Visible/Visible.md)                          | RigVMStruct | 指定FRigUnit下的该属性为常量引脚，无法连接变量。         | ★★★      |
| [Hidden](RigVM/Hidden.md)                                    | RigVMStruct | 指定FRigUnit下的该属性隐藏                               | ★★★      |
| [DetailsOnly](RigVM/DetailsOnly/DetailsOnly.md)              | RigVMStruct | 指定FRigUnit下的该属性只在细节面板中显示。               | ★★★      |
| [TemplateName](RigVM/TemplateName/TemplateName.md)           | RigVMStruct | 指定该FRigUnit成为一个泛型模板节点。                     | ★★★      |
| [CustomWidget](RigVM/CustomWidget/CustomWidget.md)           | RigVMStruct | 指定该FRigUnit里的属性要用自定义的控件来编辑。           | ★★       |
| [ExpandByDefault](RigVM/ExpandByDefault/ExpandByDefault.md)  | RigVMStruct | 把FRigUnit里的属性引脚默认展开。                         | ★★★      |
| [Aggregate](RigVM/Aggregate/Aggregate.md)                    | RigVMStruct | 指定FRigUnit里的属性引脚为可扩展连续二元运算符的运算数。 | ★★★      |
| [Varying](RigVM/Varying.md)                                  | RigVMStruct | ScriptStruct /Script/RigVM.RigVMFunction_GetDeltaTime    | 💀        |
| [MenuDescSuffix](RigVM/MenuDescSuffix/MenuDescSuffix.md)     | RigVMStruct | 标识FRigUnit在蓝图右键菜单项的名字后缀。                 | ★★★      |
| [NodeColor](RigVM/NodeColor/NodeColor.md)                    | RigVMStruct | 指定FRigUnit蓝图节点的RGB颜色值。                        | ★★       |
| [Icon](RigVM/Icon/Icon.md)                                   | RigVMStruct | 设定FRigUnit蓝图节点的图标。                             | ★★       |
| [Deprecated](RigVM/Deprecated)                               | RigVMStruct | 标识该FRigUnit为弃用状态，不在蓝图右键菜单中显示。       | ★★       |
| [Abstract](RigVM/Abstract/Abstract.md)                       | RigVMStruct | 标识该FRigUnit为抽象类，不用实现Execute。                | ★★       |
| [RigVMTypeAllowed](RigVM/RigVMTypeAllowed/RigVMTypeAllowed.md) | RigVMStruct | 指定一个UENUM可以在FRigUnit的UEnum*属性中被选择。        | ★★       |
| [Keywords](RigVM/Keywords/Keywords.md)                       | RigVMStruct | 设定FRigUnit蓝图节点在右键菜单中的关键字，方便输入查找。 | ★★★      |


## Scene

| Name                                                                                                                           | 引擎模块                 | 功能描述                                                                                                                                                                                                                                                             | 常用程度  |
|--------------------------------------------------------------------------------------------------------------------------------|----------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|-------|
| [MakeEditWidget](Scene/MakeEditWidget/MakeEditWidget.md)                                                                       | Scene                | 使FVector和FTranform在场景编辑器里出现一个可移动的控件。                                                                                                                                                                                                                             | ★★★   |
| [ValidateWidgetUsing](Scene/ValidateWidgetUsing/ValidateWidgetUsing.md)                                                        | Scene                | 提供一个函数来验证当前属性值是否合法。                                                                                                                                                                                                                                              | ★★★   |
| [AllowedLocators](Scene/AllowedLocators.md)                                                                                    | Scene                | 用来给Sequencer定位可绑定的对象                                                                                                                                                                                                                                             | ★     |


## Script

| Name                                                       | 引擎模块 | 功能描述                                                     | 常用程度 |
| ---------------------------------------------------------- | -------- | ------------------------------------------------------------ | -------- |
| [ScriptName](Script/ScriptName.md)                         | Script   | 在导出到脚本里时使用的名字                                   | ★★★      |
| [ScriptNoExport](Script/ScriptNoExport.md)                 | Script   | 不导出该函数或属性到脚本。                                   | ★★★      |
| [ScriptConstant](Script/ScriptConstant.md)                 | Script   | 把一个静态函数的返回值包装成为一个常量值。                   | ★★★      |
| [ScriptConstantHost](Script/ScriptConstantHost.md)         | Script   | 在ScriptConstant的基础上，指定常量生成的所在类型。           | ★        |
| [ScriptMethod](Script/ScriptMethod.md)                     | Script   | 把静态函数导出变成第一个参数的成员函数。                     | ★★★      |
| [ScriptMethodMutable](Script/ScriptMethodMutable.md)       | Script   | 把ScriptMethod的第一个const结构参数在调用上改成引用参数，函数内修改的值会保存下来。 | ★★       |
| [ScriptMethodSelfReturn](Script/ScriptMethodSelfReturn.md) | Script   | 在ScriptMethod的情况下，指定把这个函数的返回值要去覆盖该函数的第一个参数。 | ★★       |
| [ScriptOperator](Script/ScriptOperator.md)                 | Script   | 把第一个参数为结构的静态函数包装成结构的运算符。             | ★★★      |
| [ScriptDefaultMake](Script/ScriptDefaultMake.md)           | Script   | 禁用结构上的HasNativeMake，在脚本里构造的时候不调用C++里的NativeMake函数，而采用脚本内建的默认初始化方式。 | ★        |
| [ScriptDefaultBreak](Script/ScriptDefaultBreak.md)         | Script   |                                                              | ★        |


## Sequencer

| Name                                                                                                                           | 引擎模块                 | 功能描述                                                                                                                                                                                                                                                             | 常用程度  |
|--------------------------------------------------------------------------------------------------------------------------------|----------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|-------|
| [TakeRecorderDisplayName](Sequencer/TakeRecorderDisplayName/TakeRecorderDisplayName.md)                                        | Sequencer            | 指定UTakeRecorderSource的显示名字。                                                                                                                                                                                                                                      | ★★    |
| [SequencerBindingResolverLibrary](Sequencer/SequencerBindingResolverLibrary/SequencerBindingResolverLibrary.md)                | Sequencer            | 把具有SequencerBindingResolverLibrary标记的UBlueprintFunctionLibrary作为动态绑定的类。                                                                                                                                                                                          | ★★    |
| [CommandLineID](Sequencer/CommandLineID/CommandLineID.md)                                                                      | Sequencer            | 标记UMovieSceneCaptureProtocolBase的子类的协议类型。                                                                                                                                                                                                                        | ★★    |


## Serialization

| Name                                                         | 引擎模块      | 功能描述                                                     | 常用程度 |
| ------------------------------------------------------------ | ------------- | ------------------------------------------------------------ | -------- |
| [SkipUCSModifiedProperties](Serialization/SkipUCSModifiedProperties.md) | Serialization | 允许ActorComponent里的属性在Actor构造函数里被修改后依然保存下来 | ★        |
| [MatchedSerializers](Serialization/MatchedSerializers.md)    | Serialization | 只在NoExportTypes.h中使用，标明采用结构序列化器。是否支持文本导入导出 | 💀        |


## SparseDataType

| Name                                                                                                                           | 引擎模块                 | 功能描述                                                                                                                                                                                                                                                             | 常用程度  |
|--------------------------------------------------------------------------------------------------------------------------------|----------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|-------|
| [NoGetter](SparseDataType/NoGetter/NoGetter.md)                                                                                | SparseDataType       | 阻止UHT为该属性生成一个C++的get函数，只对稀疏类的结构数据里的属性生效。                                                                                                                                                                                                                         | ★     |


## String/Text

| Name                                                         | 引擎模块    | 功能描述                                                     | 常用程度 |
| ------------------------------------------------------------ | ----------- | ------------------------------------------------------------ | -------- |
| [PasswordField](String/PasswordField/PasswordField.md)       | String/Text | 使得文本属性显示为密码框                                     | ★★★★★    |
| [PropertyValidator](String/PropertyValidator/PropertyValidator.md) | String/Text | 用名字指定一个UFUNCTION函数来进行文本的验证                  | ★★★      |
| [MultiLine](String/MultiLine/MultiLine.md)                   | String/Text | 使得文本属性编辑框支持换行。                                 | ★★★★★    |
| [AllowedCharacters](String/AllowedCharacters/AllowedCharacters.md) | String/Text | 只允许文本框里可以输入这些字符。                             | ★★★      |
| [GetOptions](String/GetOptions/GetOptions.md)                | String/Text | 指定一个外部类的函数提供选项给FName或FString属性在细节面板中下拉选项框提供值列表。 | ★★★★★    |
| [GetKeyOptions](String/GetKeyOptions.md)                     | String/Text | 为TMap里的FName/FString作为Key提供细节面板里选项框的选项值   | 💀        |
| [GetValueOptions](String/GetValueOptions.md)                 | String/Text | 为TMap里的FName/FString作Value提供细节面板里选项框的选项值   | 💀        |
| [MaxLength](String/MaxLength/MaxLength.md)                   | String/Text | 在文本编辑框里限制文本的最大长度                             | ★★★★★    |


## Struct

| Name                                                         | 引擎模块 | 功能描述                                                     | 常用程度 |
| ------------------------------------------------------------ | -------- | ------------------------------------------------------------ | -------- |
| [MakeStructureDefaultValue](Struct/MakeStructureDefaultValue/MakeStructureDefaultValue.md) | Struct   | 存储BP中自定义结构里的属性的默认值。                         | ★        |
| [IgnoreForMemberInitializationTest](Struct/IgnoreForMemberInitializationTest.md) | Struct   | 使得该属性忽略结构的未初始验证。                             | ★★       |
| [HasNativeBreak](Struct/HasNativeBreak/HasNativeBreak.md)    | Struct   | 为该结构指定一个C++内的UFunction函数作为Break节点的实现      | ★★★★★    |
| [HasNativeMake](Struct/HasNativeMake.md)                     | Struct   | 为该结构指定一个C++内的UFunction函数作为Mreak节点的实现      | ★★★★★    |
| [DataflowFlesh](Struct/DataflowFlesh.md)                     | Struct   | ScriptStruct /Script/DataflowNodes.FloatOverrideDataflowNode | 💀        |


## TypePicker

| Name                                                         | 引擎模块   | 功能描述                                                     | 常用程度 |
| ------------------------------------------------------------ | ---------- | ------------------------------------------------------------ | -------- |
| [AllowedTypes](TypePicker/AllowedTypes/AllowedTypes.md)      | TypePicker | 为FPrimaryAssetId可以指定允许的资产类型。                    | ★★★      |
| [BaseClass](TypePicker/BaseClass/BaseClass.md)               | TypePicker | 只在StateTree模块中使用，限制FStateTreeEditorNode选择的基类类型。 | ★        |
| [AllowedClasses](TypePicker/AllowedClasses/AllowedClasses.md) | TypePicker | 用在类或对象选择器上，指定选择的对象必须属于某一些类型基类。 | ★★★      |
| [ExactClass](TypePicker/ExactClass/ExactClass.md)            | TypePicker | 在同时设置AllowedClasses和GetAllowedClasses的时候，ExactClass指定只取这两个集合中类型完全一致的类型交集，否则取一致的交集再加上其子类。 | ★        |
| [DisallowedClasses](TypePicker/DisallowedClasses/DisallowedClasses.md) | TypePicker | 用在类或对象选择器上，指定选择的对象排除掉某一些类型基类。   | ★★★      |
| [GetAllowedClasses](TypePicker/GetAllowedClasses/GetAllowedClasses.md) | TypePicker | 用在类或对象选择器上，通过一个函数来指定选择的对象必须属于某一些类型基类。 | ★★       |
| [GetDisallowedClasses](TypePicker/GetDisallowedClasses/GetDisallowedClasses.md) | TypePicker | 用在类选择器上，通过一个函数来指定选择的类型列表中排除掉某一些类型基类。 | ★★       |
| [BaseStruct](TypePicker/BaseStruct/BaseStruct.md)            | TypePicker | 指定FInstancedStruct属性选项列表选择的结构都必须继承于BaseStruct指向的结构。 | ★★★      |
| [ExcludeBaseStruct](TypePicker/ExcludeBaseStruct.md)         | TypePicker | 在使用BaseStruct的FInstancedStruct属性上忽略BaseStruct指向的结构基类。 | ★★★      |
| [StructTypeConst](TypePicker/StructTypeConst.md)             | TypePicker | 指定FInstancedStruct属性的类型不能在编辑器被选择。           | ★        |
| [MetaStruct](TypePicker/MetaStruct/MetaStruct.md)            | TypePicker | 设定到UScriptStruct*属性上，指定选择的类型的父结构。         | ★★★      |
| [ShowDisplayNames](TypePicker/ShowDisplayNames/ShowDisplayNames.md) | TypePicker | 在Class和Struct属性上，指定类选择器显示另外的显示名称而不是类原始的名字。 | ★        |
| [DisallowedStructs](TypePicker/DisallowedStructs.md)         | TypePicker | 只在SmartObject模块中应用，用以在类选择器中排除掉某个类以及子类。 | ★        |
| [RowType](TypePicker/RowType/RowType.md)                     | TypePicker | 指定FDataTableRowHandle 属性的可选行类型的基类。             | ★★★      |
| [MustImplement](TypePicker/MustImplement/MustImplement.md)   | TypePicker | 指定TSubClassOf或FSoftClassPath属性选择的类必须实现该接口    | ★★★      |
| [ShowTreeView](TypePicker/ShowTreeView/ShowTreeView.md)      | TypePicker | 用于选择Class或Struct的属性上，使得在类选取器中显示为树形而不是列表。 | ★★       |
| [BlueprintBaseOnly](TypePicker/BlueprintBaseOnly/BlueprintBaseOnly.md) | TypePicker | 用于类属性，指定是否只接受可创建蓝图子类的基类               | ★★       |
| [MetaClass](TypePicker/MetaClass/MetaClass.md)               | TypePicker | 用在软引用属性上，限定要选择的对象的基类                     | ★★       |
| [AllowAbstract](TypePicker/AllowAbstract/AllowAbstract.md)   | TypePicker | 用于类属性，指定是否接受抽象类。                             | ★★       |
| [HideViewOptions](TypePicker/HideViewOptions/HideViewOptions.md) | TypePicker | 用于选择Class或Struct的属性上，隐藏在类选取器中修改显示选项的功能。 | ★        |
| [OnlyPlaceable](TypePicker/OnlyPlaceable/OnlyPlaceable.md)   | TypePicker | 用在类属性上，指定是否只接受可被放置到场景里的Actor          | ★★       |


## UHT

| Name                                                    | 引擎模块 | 功能描述                                                     | 常用程度 |
| ------------------------------------------------------- | -------- | ------------------------------------------------------------ | -------- |
| [DocumentationPolicy](UHT/DocumentationPolicy.md)       | UHT      | 指定文档验证的规则，当前只能设为Strict                       | ★        |
| [GetByRef](Blueprint/GetByRef.md)                       | UHT      | 指定UHT为该属性生成返回引用的C++代码                         | 💀        |
| [CustomThunk](UHT/CustomThunk.md)                       | UHT      | 指定UHT不为该函数生成蓝图调用的辅助函数，而需要用户自定义编写。 | ★★★★★    |
| [NativeConstTemplateArg](UHT/NativeConstTemplateArg.md) | UHT      | 指定该属性是一个const的模板参数。                            | 💀        |
| [CppFromBpEvent](UHT/CppFromBpEvent.md)                 | UHT      |                                                              | 💀        |
| [IncludePath](UHT/IncludePath.md)                       | UHT      | 记录UClass的引用路径                                         | 💀        |
| [ModuleRelativePath](UHT/ModuleRelativePath.md)         | UHT      | 记录类型定义的的头文件路径，为其处于模块的内部相对路径。     | 💀        |


## Widget

| Name                                                         | 引擎模块 | 功能描述                                                     | 常用程度 |
| ------------------------------------------------------------ | -------- | ------------------------------------------------------------ | -------- |
| [DisableNativeTick](Widget/DisableNativeTick/DisableNativeTick.md) | Widget   | 禁用该UserWidget的NativeTick。                               | ★★★      |
| [ViewmodelBlueprintWidgetExtension](Widget/ViewmodelBlueprintWidgetExtension.md) | Widget   | 用来验证InListItems的Object类型是否符合EntryWidgetClass的MVVM绑定的ViewModelProperty。 | 💀        |
| [DesignerRebuild](Widget/DesignerRebuild/DesignerRebuild.md) | Widget   | 指定Widget里的某个属性值改变后应该重新刷新UMG的预览界面。    | ★        |
| [DefaultGraphNode](Widget/DefaultGraphNode.md)               | Widget   | 标记引擎默认创建的蓝图节点。                                 | 💀        |
| [BindWidget](Widget/BindWidget/BindWidget.md)                | Widget   | 指定在C++类中该Widget属性一定要绑定到UMG的某个同名控件。     | ★★★★★    |
| [BindWidgetOptional](Widget/BindWidgetOptional/BindWidgetOptional.md) | Widget   | 指定在C++类中该Widget属性可以绑定到UMG的某个同名控件，也可以不绑定。 | ★★★      |
| [OptionalWidget](Widget/OptionalWidget.md)                   | Widget   | 指定在C++类中该Widget属性可以绑定到UMG的某个同名控件，也可以不绑定。 | ★★★      |
| [IsBindableEvent](Widget/IsBindableEvent/IsBindableEvent.md) | Widget   | 把一个动态单播委托暴露到UMG蓝图里以绑定相应事件。            | ★★★      |
| [EntryInterface](Widget/EntryInterface/EntryInterface.md)    | Widget   | 限定EntryWidgetClass属性上可选类必须实现的接口，用在DynamicEntryBox和ListView这两个Widget上。 | ★★★      |
| [EntryClass](Widget/EntryClass.md)                           | Widget | 限定EntryWidgetClass属性上可选类必须继承自的基类，用在DynamicEntryBox和ListView这两个Widget上。 | ★★★      |
| [BindWidgetAnim](Widget/BindWidgetAnim/BindWidgetAnim.md)    | Widget   | 指定在C++类中该UWidgetAnimation属性一定要绑定到UMG下的某个动画 | ★★★★★    |
| [BindWidgetAnimOptional](Widget/BindWidgetAnimOptional/BindWidgetAnimOptional.md) | Widget   | 指定在C++类中该UWidgetAnimation属性可以要绑定到UMG下的某个动画，也可以不绑定。 | ★★★      |