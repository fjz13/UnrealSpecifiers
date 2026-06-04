# Meta Blueprint And Pins

> Category source index. Use targeted search in this file, then open only the listed `Doc`.
> Resolve `Doc` relative to the nearest preceding `Doc root`; each `Doc root` is relative to `references/sources/`.

## Meta - Blueprint

> Doc root: `Meta/Blueprint/`

| ID | Summary | Usage | Doc |
|---|---|---|---|
| `AdvancedDisplay` | 把函数的一些参数折叠起来不显示，需要手动点开下拉箭头来展开编辑 | UFUNCTION | `AdvancedDisplay.md` |
| `AllowPrivateAccess` | 允许一个在C++中private的属性，可以在蓝图中访问 | UPROPERTY | `AllowPrivateAccess.md` |
| `ArrayParm` | 指定一个函数为使用Array<*>的函数，数组元素类型为通配符的泛型 | UFUNCTION | `Param/ArrayParm.md` |
| `ArrayTypeDependentParams` | 当ArryParam指定的函数拥有两个或以上Array参数的时候，指定哪些数组参数的类型也应该相应的被更新改变 | UFUNCTION | `Param/ArrayTypeDependentParams.md` |
| `AutoCreateRefTerm` | 指定函数的多个输入引用参数在没有连接的时候自动为其创建默认值 | UFUNCTION | `Param/AutoCreateRefTerm.md` |
| `Blueprint.DisplayName` | 此节点在蓝图中的命名将被此处提供的值所取代，而非代码生成的命名 | UCLASS, UENUM::UMETA, UFUNCTION, UPARAM, UPROPERTY | `DisplayName.md` |
| `Blueprint.Keywords` | 指定一系列关键字用于在蓝图内右键找到该函数 | UFUNCTION | `Keywords.md` |
| `BlueprintAutocast` | 告诉蓝图系统这个函数是用来支持从A类型到B类型的自动转换 | UFUNCTION | `BlueprintAutocast.md` |
| `BlueprintGetter` | 采用一个自定义的get函数来读取 | UFUNCTION, UPROPERTY | `BlueprintGetter.md` |
| `BlueprintInternalUseOnly` | 标明该元素是作为蓝图系统的内部调用或使用，不暴露出来在用户层面直接定义或使用 | UFUNCTION, USTRUCT | `BlueprintInternalUseOnly.md` |
| `BlueprintInternalUseOnlyHierarchical` | 标明该结构及其子类都不暴露给用户定义和使用，均只能在蓝图系统内部使用 | USTRUCT | `BlueprintInternalUseOnlyHierarchical.md` |
| `BlueprintPrivate` | 指定该函数或属性只能在本类中被调用或读写，类似C++中的private的作用域限制。不可在别的蓝图类里访问 | UFUNCTION, UPROPERTY | `BlueprintPrivate.md` |
| `BlueprintProtected` | 指定该函数或属性只能在本类以及子类中被调用或读写，类似C++中的protected作用域限制。不可在别的蓝图类里访问 | UFUNCTION, UPROPERTY | `BlueprintProtected.md` |
| `BlueprintSetter` | 采用一个自定义的set函数来读取 | UFUNCTION, UPROPERTY | `BlueprintSetter.md` |
| `BlueprintThreadSafe` | 用在类上或函数上，标记类里的函数都是线程安全的 | UCLASS, UFUNCTION | `BlueprintThreadSafe.md` |
| `BlueprintType` | 表明可以作为一个蓝图变量 | UCLASS, UENUM, UINTERFACE, USTRUCT | `BlueprintType.md` |
| `CPP_Default_XXX` | XXX=参数名字 | UPARAM | `CPP_Default_XXX.md` |
| `CallInEditor` | 可以在Actor的细节面板上作为一个按钮来调用该函数 | UFUNCTION | `CallInEditor.md` |
| `CallableWithoutWorldContext` | 让函数也可以脱离WorldContextObject而使用 | UFUNCTION | `CallableWithoutWorldContext.md` |
| `CannotImplementInterfaceInBlueprint` | 指定该接口不能在蓝图中实现 | Blueprint | `CannotImplementInterfaceInBlueprint.md` |
| `CommutativeAssociativeBinaryOperator` | 标记一个二元运算函数的运算支持交换律和结合律，在蓝图节点上增加一个“+”引脚，允许动态的直接添加多个输入值 | UFUNCTION | `CommutativeAssociativeBinaryOperator.md` |
| `CompactNodeTitle` | 使得函数的展示形式变成精简压缩模式，同时指定一个新的精简的名字 | UFUNCTION | `CompactNodeTitle.md` |
| `CustomStructureParam` | 被CustomStructureParam标记的函数参数会变成Wildcard的通配符参数，其引脚的类型会等于连接的变量类型 | UFUNCTION | `Param/CustomStructureParam.md` |
| `DefaultToSelf` | 用在函数上，指定一个参数的默认值为Self值 | UFUNCTION | `DefaultToSelf.md` |
| `DeterminesOutputType` | 指定一个参数的类型作为函数动态调整输出参数类型的参考类型 | UFUNCTION | `Param/DeterminesOutputType.md` |
| `DontUseGenericSpawnObject` | 阻止使用蓝图中的Generic Create Object节点来生成本类的对象 | UCLASS | `DontUseGenericSpawnObject.md` |
| `DynamicOutputParam` | 配合DeterminesOutputType，指定多个支持动态类型的输出参数 | UFUNCTION | `Param/DynamicOutputParam.md` |
| `ExpandBoolAsExecs` | 是ExpandEnumAsExecs的别名，完全等价其功能 | UFUNCTION | `Exec/ExpandBoolAsExecs.md` |
| `ExpandEnumAsExecs` | 指定多个enum或bool类型的函数参数，自动根据条目生成相应的多个输入或输出执行引脚，并根据实参值不同来相应改变控制流 | UFUNCTION | `Exec/ExpandEnumAsExecs.md` |
| `ExposeOnSpawn` | 使该属性在ContructObject或SpawnActor等创建对象的时候暴露出来 | UPROPERTY | `ExposeOnSpawn.md` |
| `ExposedAsyncProxy` | 在 Async Task 节点中公开此类的一个代理对象 | UCLASS | `ExposedAsyncProxy.md` |
| `ForceAsFunction` | 把C++里用BlueprintImplementableEvent或NativeEvent定义的事件强制改为函数在子类中覆写 | UFUNCTION | `ForceAsFunction.md` |
| `GetByRef` | 指定UHT为该属性生成返回引用的C++代码 | UPROPERTY | `GetByRef.md` |
| `HasDedicatedAsyncNode` | 隐藏UBlueprintAsyncActionBase子类里工厂方法自动生成的蓝图异步节点，以便自己可以手动自定义创建一个相应的UK2Node_XXX | UCLASS | `HasDedicatedAsyncNode.md` |
| `HiddenNode` | 把指定的UBTNode隐藏不在右键菜单中显示 | UCLASS | `HiddenNode.md` |
| `HideFunctions` | 在属性查看器中不显示指定类别中的所有函数 | UCLASS | `HideFunctions.md` |
| `HideSpawnParms` | 在UGamelayTask子类生成的蓝图异步节点上隐藏UGamelayTask子类继承链中某些属性 | UFUNCTION | `Param/HideSpawnParms.md` |
| `HideThen` | 隐藏异步蓝图节点的Then引脚 | UCLASS | `HideThen.md` |
| `IgnoreTypePromotion` | 标记该函数不收录进类型提升函数库 | UFUNCTION | `IgnoreTypePromotion.md` |
| `IsBlueprintBase` | 说明此类是否为创建蓝图的一个可接受基类，与 UCLASS 说明符、Blueprintable 或 'NotBlueprintable` 相似 | UCLASS, UINTERFACE | `IsBlueprintBase.md` |
| `IsConversionRoot` | 允许Actor在自身以及子类之间做转换 | UCLASS, UINTERFACE | `IsConversionRoot.md` |
| `KismetHideOverrides` | 不允许被覆盖的蓝图事件的列表 | UCLASS | `KismetHideOverrides.md` |
| `Latent` | 标明一个函数是一个延迟异步操作 | UFUNCTION | `Latent/Latent.md` |
| `LatentCallbackTarget` | 用在FLatentActionInfo::CallbackTarget属性上，告诉蓝图VM在哪个对象上调用函数 | UPROPERTY | `Latent/LatentCallbackTarget.md` |
| `LatentInfo` | 和Latent配合，指明哪个函数参数是LatentInfo参数 | UFUNCTION | `Latent/LatentInfo.md` |
| `MapKeyParam` | 指定一个函数参数为Map的Key，其根据MapParam指定的实际Map参数的Key类型而相应改变 | UFUNCTION | `Param/MapParam/MapKeyParam.md` |
| `MapParam` | 指定一个函数为使用TMap<TKey,TValue>的函数，元素类型为通配符的泛型 | UFUNCTION | `Param/MapParam/MapParam.md` |
| `MapValueParam` | 指定一个函数参数为Map的Value，其根据MapParam指定的实际Map参数的Value类型而相应改变 | UFUNCTION | `Param/MapParam/MapValueParam.md` |
| `NativeBreakFunc` | 指定一个函数采用BreakStruct的图标 | UFUNCTION | `NativeBreakFunc.md` |
| `NativeConst` | 指定有C++里的const标志 | UPARAM | `NativeConst.md` |
| `NativeMakeFunc` | 指定一个函数采用MakeStruct的图标 | UFUNCTION | `NativeMakeFunc.md` |
| `NeedsLatentFixup` | 用在FLatentActionInfo::Linkage属性上，告诉蓝图VM生成跳转信息 | UPROPERTY | `Latent/NeedsLatentFixup.md` |
| `NotBlueprintThreadSafe` | 用在函数上，标记这个函数是不线程安全的 | UFUNCTION | `NotBlueprintThreadSafe.md` |
| `NotInputConfigurable` | 让一些UInputModifier和UInputTrigger不能在ProjectSettings里配置 | UCLASS | `NotInputConfigurable.md` |
| `ObjectSetType` | 指定统计页面的对象集合类型 | UCLASS | `ObjectSetType.md` |
| `ProhibitedInterfaces` | 列出与蓝图类不兼容的接口，阻止实现 | UCLASS | `ProhibitedInterfaces.md` |
| `RestrictedToClasses` | 限制蓝图函数库下的函数只能在RestrictedToClasses指定的类蓝图中右键创建出来 | UCLASS | `RestrictedToClasses.md` |
| `ReturnDisplayName` | 改变函数返回值的名字，默认是ReturnValue | UFUNCTION | `ReturnDisplayName.md` |
| `SetParam` | 指定一个函数为使用Set<TItem>的函数，元素类型为通配符的泛型 | UFUNCTION | `SetParam.md` |
| `ShowWorldContextPin` | 放在UCLASS上，指定本类里的函数调用都必须显示WorldContext引脚，无论其本来是否默认隐藏 | UCLASS | `ShowWorldContextPin.md` |
| `SparseClassDataTypes` | UCLASS：SparseClassDataType | UCLASS | `SparseClassDataTypes.md` |
| `UnsafeDuringActorConstruction` | 标明该函数不能在Actor的构造函数里调用 | UFUNCTION | `UnsafeDuringActorConstruction.md` |
| `Variadic` | 指定该函数接受多个参数 | UFUNCTION | `Variadic.md` |
| `WorldContext` | 指定函数的一个参数自动接收WorldContext对象，以便确定当前运行所处于的World | UFUNCTION | `WorldContext.md` |


## Meta - Pin

> Doc root: `Meta/Pin/`

| ID | Summary | Usage | Doc |
|---|---|---|---|
| `DataTablePin` | 指定一个函数参数为DataTable或CurveTable类型，以便为FName的其他参数提供RowNameList的选择 | UFUNCTION | `DataTablePin.md` |
| `DisableSplitPin` | 禁用Struct的split功能 | USTRUCT | `DisableSplitPin.md` |
| `HiddenByDefault` | Struct的Make Struct和Break Struct节点中的引脚默认为隐藏状态 | USTRUCT | `HiddenByDefault.md` |
| `HidePin` | 用在函数调用上，指定要隐藏的参数名称，也可以隐藏返回值。可以隐藏多个参数 | UFUNCTION | `HidePin.md` |
| `HideSelfPin` | 用在函数调用上，隐藏默认的SelfPin，也就是Target，导致该函数只能在OwnerClass内调用 | UFUNCTION | `HideSelfPin.md` |
| `InternalUseParam` | 用在函数调用上，指定要隐藏的参数名称，也可以隐藏返回值。可以隐藏多个参数 | UFUNCTION | `InternalUseParam.md` |
| `PinHiddenByDefault` | 使得这个结构里的属性在蓝图里作为引脚时默认是隐藏的 | UPROPERTY | `PinHiddenByDefault.md` |



