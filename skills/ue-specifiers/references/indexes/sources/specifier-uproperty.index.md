# Specifier UPROPERTY

> Category source index. Use targeted search in this file, then open only the listed `Doc`.
> Resolve `Doc` relative to the nearest preceding `Doc root`; each `Doc root` is relative to `references/sources/`.

## Specifier - UPROPERTY

> Doc root: `Specifier/UPROPERTY/`

| ID | Summary | Usage | Doc |
|---|---|---|---|
| `AdvancedDisplay` | 被折叠到高级栏下，要手动打开。一般用在不太常用的属性上面 | UPROPERTY / DetailsPanel | `DetaisPanel/AdvancedDisplay.md` |
| `AssetRegistrySearchable` | 标记该属性可以作为AssetRegistry的Tag和Value值来进行资产的过滤搜索 | UPROPERTY / Asset | `Asset/AssetRegistrySearchable.md` |
| `BlueprintAssignable` | 在蓝图中可以为这个多播委托绑定事件 | UPROPERTY / Blueprint | `Blueprint/BlueprintAssignable.md` |
| `BlueprintAuthorityOnly` | 只能绑定为BlueprintAuthorityOnly的事件，让该多播委托只接受在服务端运行的事件 | UPROPERTY / Blueprint | `Blueprint/BlueprintAuthorityOnly.md` |
| `BlueprintCallable` | 在蓝图中可以调用这个多播委托 | UPROPERTY / Blueprint | `Blueprint/BlueprintCallable.md` |
| `BlueprintGetter` | 为属性定义一个自定义的Get函数来读取 | UPROPERTY / Blueprint | `Blueprint/BlueprintGetter.md` |
| `BlueprintReadOnly` | 此属性可由蓝图读取，但不能被修改 | UPROPERTY / Blueprint | `Blueprint/BlueprintReadOnly.md` |
| `BlueprintReadWrite` | 可从蓝图读取或写入此属性 | UPROPERTY / Blueprint | `Blueprint/BlueprintReadWrite.md` |
| `BlueprintSetter` | 采用一个自定义的set函数来读取 | UPROPERTY / Blueprint | `Blueprint/BlueprintSetter.md` |
| `Category` | 指定属性的类别，使用 \| 运算符定义嵌套类目 | UPROPERTY / DetailsPanel | `DetaisPanel/Category.md` |
| `Config` | 指定该属性是一个配置属性，该属性可以被序列化读写到ini文件（路径由uclass的config标签指定）中 | UPROPERTY / Config | `Config/Config.md` |
| `DuplicateTransient` | 在对象复制或COPY格式导出的时候，忽略该属性 | UPROPERTY / Serialization | `Serialization/DuplicateTransient.md` |
| `EditAnywhere` | 在默认值和实例的细节面板上均可编辑 | UPROPERTY / DetailsPanel | `DetaisPanel/EditAnywhere.md` |
| `EditDefaultsOnly` | 只能在默认值面板里编辑 | UPROPERTY / DetailsPanel | `DetaisPanel/EditDefaultsOnly.md` |
| `EditFixedSize` | 在细节面板上不允许改变该容器的元素个数 | UPROPERTY / DetailsPanel | `DetaisPanel/EditFixedSize.md` |
| `EditInstanceOnly` | 只能在实例的细节面板上编辑该属性 | UPROPERTY / DetailsPanel | `DetaisPanel/EditInstanceOnly.md` |
| `Export` | 在对Asset导出的时候，决定该类的对象应该导出内部的属性值，而是对象的路径 | UPROPERTY / Serialization | `Serialization/Export.md` |
| `FieldNotify` | 在打开MVVM插件后，使得该属性变成支持FieldNotify的属性 | UPROPERTY / UHT | `UHT/FieldNotify.md` |
| `Getter` | 为属性增加一个C++的Get函数，只在C++层面应用 | UPROPERTY / Blueprint | `Blueprint/Getter.md` |
| `GlobalConfig` | 和Config一样指定该属性可作为配置读取和写入ini中，但只会读取写入到配置文件里基类的值，而不会使用配置文件里子类里的值 | UPROPERTY / Config | `Config/GlobalConfig.md` |
| `Instanced` | 指定对该对象属性的编辑赋值应该新创建一个实例并作为子对象，而不是寻找一个对象引用 | UPROPERTY / Instance | `Instanced.md` |
| `Interp` | 指定该属性值可暴露到时间轴里编辑，在平常的Timeline或UMG的动画里使用 | UPROPERTY / DetailsPanel | `DetaisPanel/Interp.md` |
| `Localized` | UE5.8 中已废弃。UHT 遇到 Localized 会记录 deprecated 错误，不应再作为可推荐的 UPROPERTY specifier 使用 | UPROPERTY / Asset | `Asset/Localized.md` |
| `Native` | 属性为本地：C++代码负责对其进行序列化并公开到垃圾回收 | UPROPERTY / UHT | `UHT/Native.md` |
| `NoClear` | 指定该属性的编辑选项中不出现Clear按钮，不允许置null | UPROPERTY / DetailsPanel | `DetaisPanel/NoClear.md` |
| `NonPIEDuplicateTransient` | 在对象复制的时候，且在不是PIE的场合，忽略该属性 | UPROPERTY / Serialization | `Serialization/NonPIEDuplicateTransient.md` |
| `NonTransactional` | 对该属性的改变操作，不会被包含进编辑器的Undo/Redo命令中 | UPROPERTY / DetailsPanel | `DetaisPanel/NonTransactional.md` |
| `NotReplicated` | 跳过复制。这只会应用到服务请求函数中的结构体成员和参数 | UPROPERTY / Network | `Network/NotReplicated.md` |
| `RepRetry` | UE5.8 中已废弃。UHT 遇到 RepRetry 会记录 deprecated 错误，不应再作为可推荐的 UPROPERTY specifier 使用 | UPROPERTY / Network | `Network/RepRetry.md` |
| `Replicated` | 指定该属性应随网络进行复制 | UPROPERTY / Network | `Network/Replicated.md` |
| `ReplicatedUsing` | 指定一个通知回调函数，在属性通过网络更新后执行 | UPROPERTY / Network | `Network/ReplicatedUsing.md` |
| `SaveGame` | 在SaveGame存档的时候，只序列化有SaveGame标记的属性，而不序列化别的属性 | UPROPERTY / Serialization | `Serialization/SaveGame.md` |
| `Setter` | 为属性增加一个C++的Set函数，只在C++层面应用 | UPROPERTY / Blueprint | `Blueprint/Setter.md` |
| `SimpleDisplay` | 在细节面板中直接可见，不折叠到高级中 | UPROPERTY / DetailsPanel | `DetaisPanel/SimpleDisplay.md` |
| `SkipSerialization` | 二进制序列化时跳过该属性，但在ExportText的时候依然可以导出 | UPROPERTY / Serialization | `Serialization/SkipSerialization.md` |
| `TextExportTransient` | 在ExportText导出为.COPY格式的时候，忽略该属性 | UPROPERTY / Serialization | `Serialization/TextExportTransient.md` |
| `Transient` | 不序列化该属性，该属性初始化时候会被0填充 | UPROPERTY / Serialization | `Serialization/Transient.md` |
| `UPROPERTY(标识符)` | UE5.8 UHT 在 property parser 中解析 UPROPERTY，成员属性使用 UhtTableNames.PropertyMember 的 specifier table。该页是 UPROPERTY 条目索引，不是单个 | UPROPERTY | `../UPROPERTY.md` |
| `VisibleAnywhere` | 在默认值和实例细节面板均可见，但不可编辑 | UPROPERTY / DetailsPanel | `DetaisPanel/VisibleAnywhere.md` |
| `VisibleDefaultsOnly` | 在默认值细节面板可见，但不可编辑 | UPROPERTY / DetailsPanel | `DetaisPanel/VisibleDefaultsOnly.md` |
| `VisibleInstanceOnly` | 在实例细节面板可见，但不可编辑 | UPROPERTY / DetailsPanel | `DetaisPanel/VisibleInstanceOnly.md` |



