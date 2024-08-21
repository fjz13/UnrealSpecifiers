| Name                                                         | 引擎模块             | 功能描述                                                     | 常用程度 |
| ------------------------------------------------------------ | -------------------- | ------------------------------------------------------------ | -------- |
| [Category](UPROPERTY\DetaisPanel\Category\Category.md)       | DetailsPanel, Editor | 指定属性的类别，使用 &#124; 运算符定义嵌套类目。             | 5        |
| [SimpleDisplay](UPROPERTY\DetaisPanel\SimpleDisplay\SimpleDisplay.md) | DetailsPanel, Editor | 在细节面板中直接可见，不折叠到高级中。                       | 3        |
| [AdvancedDisplay](UPROPERTY\DetaisPanel\AdvancedDisplay\AdvancedDisplay.md) | DetailsPanel, Editor | 被折叠到高级栏下，要手动打开。一般用在不太常用的属性上面。   | 5        |
| [EditAnywhere](UPROPERTY\DetaisPanel\EditAnywhere\EditAnywhere.md) | DetailsPanel, Editor | 在默认值和实例的细节面板上均可编辑                           | 5        |
| [EditDefaultsOnly](UPROPERTY\DetaisPanel\EditDefaultsOnly.md) | DetailsPanel, Editor | 只能在默认值面板里编辑                                       | 5        |
| [EditInstanceOnly](UPROPERTY\DetaisPanel\EditInstanceOnly.md) | DetailsPanel, Editor | 只能在实例的细节面板上编辑该属性                             | 5        |
| [VisibleAnywhere](UPROPERTY\DetaisPanel\VisibleAnywhere.md)  | DetailsPanel, Editor | 在默认值和实例细节面板均可见，但不可编辑                     | 5        |
| [VisibleDefaultsOnly](UPROPERTY\DetaisPanel\VisibleDefaultsOnly.md) | DetailsPanel, Editor | 在默认值细节面板可见，但不可编辑                             | 5        |
| [VisibleInstanceOnly](UPROPERTY\DetaisPanel\VisibleInstanceOnly.md) | DetailsPanel, Editor | 在实例细节面板可见，但不可编辑                               | 5        |
| [EditFixedSize](UPROPERTY\DetaisPanel\EditFixedSize\EditFixedSize.md) | DetailsPanel, Editor | 在细节面板上不允许改变该容器的元素个数。                     | 3        |
| [NoClear](UPROPERTY\DetaisPanel\NoClear\NoClear.md)          | DetailsPanel, Editor | 指定该属性的编辑选项中不出现Clear按钮，不允许置null。        | 3        |
| [BlueprintReadWrite](UPROPERTY\Blueprint\BlueprintReadWrite\BlueprintReadWrite.md) | Blueprint            | 可从蓝图读取或写入此属性。                                   | 5        |
| [BlueprintReadOnly](UPROPERTY\Blueprint\BlueprintReadOnly\BlueprintReadOnly.md) | Blueprint            | 此属性可由蓝图读取，但不能被修改。                           | 5        |
| [BlueprintGetter](UPROPERTY\Blueprint\BlueprintGetter\BlueprintGetter.md) | Blueprint            | 为属性定义一个自定义的Get函数来读取。                        | 3        |
| [Getter](UPROPERTY\Blueprint\Getter.md)                      | Blueprint            | 为属性增加一个C++的Get函数，只在C++层面应用。                | 3        |
| [Setter](UPROPERTY\Blueprint\Setter\Setter.md)               | Blueprint            | 为属性增加一个C++的Set函数，只在C++层面应用。                | 3        |
| [BlueprintSetter](UPROPERTY\Blueprint\BlueprintSetter.md)    | Blueprint            | 采用一个自定义的set函数来读取。                              | 3        |
| [BlueprintCallable](UPROPERTY\Blueprint\BlueprintCallable\BlueprintCallable.md) | Blueprint            | 在蓝图中可以调用这个多播委托                                 | 3        |
| [BlueprintAssignable](UPROPERTY\Blueprint\BlueprintAssignable\BlueprintAssignable.md) | Blueprint            | 在蓝图中可以为这个多播委托绑定事件                           | 3        |
| [BlueprintAuthorityOnly](UPROPERTY\Blueprint\BlueprintAuthorityOnly\BlueprintAuthorityOnly.md) | Blueprint, Network   | 只能绑定为BlueprintAuthorityOnly的事件，让该多播委托只接受在服务端运行的事件 | 3        |
| [Config](UPROPERTY\Config\Config.md)                         | Config               | 指定该属性是一个配置属性，该属性可以被序列化读写到ini文件（路径由uclass的config标签指定）中。 | 3        |
| [GlobalConfig](UPROPERTY\Config\GlobalConfig\GlobalConfig.md) | Config               | 和Config一样指定该属性可作为配置读取和写入ini中，但只会读取写入到配置文件里基类的值，而不会使用配置文件里子类里的值。 | 3        |
| [Export](UPROPERTY\Serialization\Export\Export.md)           | Serialization        | 在对Asset导出的时候，决定该类的对象应该导出内部的属性值，而是对象的路径。 | 1        |
| [Instanced](UPROPERTY\Instance\Instanced\Instanced.md)       | Instance             | 指定对该对象属性的编辑赋值应该新创建一个实例并作为子对象，而不是寻找一个对象引用。 | 3        |
| [AssetRegistrySearchable](UPROPERTY\Asset\AssetRegistrySearchable\AssetRegistrySearchable.md) | Asset                | 标记该属性可以作为AssetRegistry的Tag和Value值来进行资产的过滤搜索 | 3        |
| [Interp](UPROPERTY\DetaisPanel\Interp\Interp.md)             | Sequencer            | 指定该属性值可暴露到时间轴里编辑，在平常的Timeline或UMG的动画里使用。 | 3        |
| [Localized](UPROPERTY\Asset\Localized.md)                    | Behavior             | 此属性的值将拥有一个定义的本地化值。多用于字符串。暗示为 ReadOnly。该值有一个本地化值。最常标记在string上 |          |
| [Native](UPROPERTY\UHT\Native.md)                            | Behavior             | 属性为本地：C++代码负责对其进行序列化并公开到垃圾回收 。     |          |
| [NonTransactional](UPROPERTY\DetaisPanel\NonTransactional\NonTransactional.md) | Editor               | 对该属性的改变操作，不会被包含进编辑器的Undo/Redo命令中。    | 2        |
| [Replicated](UPROPERTY\Network\Replicated.md)                | Network              | 指定该属性应随网络进行复制。                                 | 5        |
| [ReplicatedUsing](UPROPERTY\Network\ReplicatedUsing\ReplicatedUsing.md) | Network              | 指定一个通知回调函数，在属性通过网络更新后执行。             | 5        |
| [NotReplicated](UPROPERTY\Network\NotReplicated.md)          | Network              | 跳过复制。这只会应用到服务请求函数中的结构体成员和参数。     | 3        |
| [RepRetry](UPROPERTY\Network\RepRetry.md)                    | Network              | 只适用于结构体属性。如果此属性未能完全发送（举例而言：Object引用尚无法通过网络进行序列化），则重新尝试对其的复制。对简单引用而言，这是默认选择；但对结构体而言，这会产生带宽开销，并非优选项。因此在指定此标签之前其均为禁用状态。 |          |
| [SaveGame](UPROPERTY\Serialization\SaveGame\SaveGame.md)     | Serialization        | 在SaveGame存档的时候，只序列化有SaveGame标记的属性，而不序列化别的属性。 | 5        |
| [SkipSerialization](UPROPERTY\Serialization\SkipSerialization\SkipSerialization.md) | Serialization        | 二进制序列化时跳过该属性，但在ExportText的时候依然可以导出。 | 3        |
| [TextExportTransient](UPROPERTY\Serialization\TextExportTransient.md) | Serialization        | 在ExportText导出为.COPY格式的时候，忽略该属性。              | 1        |
| [Transient](UPROPERTY\Serialization\Transient\Transient.md)  | Serialization        | 不序列化该属性，该属性初始化时候会被0填充。                  | 5        |
| [DuplicateTransient](UPROPERTY\Serialization\DuplicateTransient\DuplicateTransient.md) | Serialization        | 在对象复制或COPY格式导出的时候，忽略该属性。                 | 2        |
| [NonPIEDuplicateTransient](UPROPERTY\Serialization\NonPIEDuplicateTransient\NonPIEDuplicateTransient.md) | Serialization        | 在对象复制的时候，且在不是PIE的场合，忽略该属性。            | 1        |
| [FieldNotify](UPROPERTY\UHT\FieldNotify\FieldNotify.md)      | MVVM, UHT            | 在打开MVVM插件后，使得该属性变成支持FieldNotify的属性。      | 4        |
