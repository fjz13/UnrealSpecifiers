---
title: "UPROPERTY(标识符)"
id: "UPROPERTY.UPROPERTY(标识符)"
kind: "specifier"
symbol: "UPROPERTY(标识符)"
scope: "UPROPERTY"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "UE5.8 UHT 在 property parser 中解析 UPROPERTY，成员属性使用 UhtTableNames.PropertyMember 的 specifier table。该页是 UPROPERTY 条目索引，不是单个 "
usage: "UPROPERTY"
---

# UPROPERTY(标识符)

 ## Serialization

| Name                                                                                                     | 引擎模块                 | 功能描述                                                                                                                 | 常用程度  |
|----------------------------------------------------------------------------------------------------------|----------------------|----------------------------------------------------------------------------------------------------------------------|-------|
| [Export](UPROPERTY/Serialization/Export.md)                                                       | Serialization        | 在对Asset导出的时候，决定该类的对象应该导出内部的属性值，而是对象的路径。                                                                              | ★     |
| [SaveGame](UPROPERTY/Serialization/SaveGame.md)                                                 | Serialization        | 在SaveGame存档的时候，只序列化有SaveGame标记的属性，而不序列化别的属性。                                                                         | ★★★★★ |
| [SkipSerialization](UPROPERTY/Serialization/SkipSerialization.md)                      | Serialization        | 二进制序列化时跳过该属性，但在ExportText的时候依然可以导出。                                                                                  | ★★★   |
| [TextExportTransient](UPROPERTY/Serialization/TextExportTransient.md)                                    | Serialization        | 在ExportText导出为.COPY格式的时候，忽略该属性。                                                                                      | ★     |
| [Transient](UPROPERTY/Serialization/Transient.md)                                              | Serialization        | 不序列化该属性，该属性初始化时候会被0填充。                                                                                               | ★★★★★ |
| [DuplicateTransient](UPROPERTY/Serialization/DuplicateTransient.md)                   | Serialization        | 在对象复制或COPY格式导出的时候，忽略该属性。                                                                                             | ★★    |
| [NonPIEDuplicateTransient](UPROPERTY/Serialization/NonPIEDuplicateTransient.md) | Serialization        | 在对象复制的时候，且在不是PIE的场合，忽略该属性。                                                                                           | ★     |


 ## Sequencer

| Name                                                                                                     | 引擎模块                 | 功能描述                                                                                                                 | 常用程度  |
|----------------------------------------------------------------------------------------------------------|----------------------|----------------------------------------------------------------------------------------------------------------------|-------|
| [Interp](UPROPERTY/DetaisPanel/Interp.md)                                                         | Sequencer            | 指定该属性值可暴露到时间轴里编辑，在平常的Timeline或UMG的动画里使用。                                                                             | ★★★   |


 ## Network

| Name                                                                                                     | 引擎模块                 | 功能描述                                                                                                                 | 常用程度  |
|----------------------------------------------------------------------------------------------------------|----------------------|----------------------------------------------------------------------------------------------------------------------|-------|
| [Replicated](UPROPERTY/Network/Replicated.md)                                                            | Network              | 指定该属性应随网络进行复制。                                                                                                       | ★★★★★ |
| [ReplicatedUsing](UPROPERTY/Network/ReplicatedUsing.md)                                  | Network              | 指定一个通知回调函数，在属性通过网络更新后执行。                                                                                             | ★★★★★ |
| [NotReplicated](UPROPERTY/Network/NotReplicated.md)                                                      | Network              | 跳过复制。这只会应用到服务请求函数中的结构体成员和参数。                                                                                         | ★★★   |
| [RepRetry](UPROPERTY/Network/RepRetry.md)                                                                | Network              | 只适用于结构体属性。如果此属性未能完全发送（举例而言：Object引用尚无法通过网络进行序列化），则重新尝试对其的复制。对简单引用而言，这是默认选择；但对结构体而言，这会产生带宽开销，并非优选项。因此在指定此标签之前其均为禁用状态。 | 💀    |


 ## UHT

| Name                                                                                                     | 引擎模块                 | 功能描述                                                                                                                 | 常用程度  |
|----------------------------------------------------------------------------------------------------------|----------------------|----------------------------------------------------------------------------------------------------------------------|-------|
| [FieldNotify](UPROPERTY/UHT/FieldNotify.md)                                                  | MVVM, UHT            | 在打开MVVM插件后，使得该属性变成支持FieldNotify的属性。                                                                                  | ★★★★  |


 ## Instance

| Name                                                                                                     | 引擎模块                 | 功能描述                                                                                                                 | 常用程度  |
|----------------------------------------------------------------------------------------------------------|----------------------|----------------------------------------------------------------------------------------------------------------------|-------|
| [Instanced](UPROPERTY/Instanced.md)                                                   | Instance             | 指定对该对象属性的编辑赋值应该新创建一个实例并作为子对象，而不是寻找一个对象引用。                                                                            | ★★★   |


 ## Editor

| Name                                                                                                     | 引擎模块                 | 功能描述                                                                                                                 | 常用程度  |
|----------------------------------------------------------------------------------------------------------|----------------------|----------------------------------------------------------------------------------------------------------------------|-------|
| [NonTransactional](UPROPERTY/DetaisPanel/NonTransactional.md)                           | Editor               | 对该属性的改变操作，不会被包含进编辑器的Undo/Redo命令中。                                                                                    | ★★    |


 ## DetailsPanel

| Name                                                                                                     | 引擎模块                 | 功能描述                                                                                                                 | 常用程度  |
|----------------------------------------------------------------------------------------------------------|----------------------|----------------------------------------------------------------------------------------------------------------------|-------|
| [Category](UPROPERTY/DetaisPanel/Category.md)                                                   | DetailsPanel, Editor | 指定属性的类别，使用 &#124; 运算符定义嵌套类目。                                                                                         | ★★★★★ |
| [SimpleDisplay](UPROPERTY/DetaisPanel/SimpleDisplay.md)                                    | DetailsPanel, Editor | 在细节面板中直接可见，不折叠到高级中。                                                                                                  | ★★★   |
| [AdvancedDisplay](UPROPERTY/DetaisPanel/AdvancedDisplay.md)                              | DetailsPanel, Editor | 被折叠到高级栏下，要手动打开。一般用在不太常用的属性上面。                                                                                        | ★★★★★ |
| [EditAnywhere](UPROPERTY/DetaisPanel/EditAnywhere.md)                                       | DetailsPanel, Editor | 在默认值和实例的细节面板上均可编辑                                                                                                    | ★★★★★ |
| [EditDefaultsOnly](UPROPERTY/DetaisPanel/EditDefaultsOnly.md)                                            | DetailsPanel, Editor | 只能在默认值面板里编辑                                                                                                          | ★★★★★ |
| [EditInstanceOnly](UPROPERTY/DetaisPanel/EditInstanceOnly.md)                                            | DetailsPanel, Editor | 只能在实例的细节面板上编辑该属性                                                                                                     | ★★★★★ |
| [VisibleAnywhere](UPROPERTY/DetaisPanel/VisibleAnywhere.md)                                              | DetailsPanel, Editor | 在默认值和实例细节面板均可见，但不可编辑                                                                                                 | ★★★★★ |
| [VisibleDefaultsOnly](UPROPERTY/DetaisPanel/VisibleDefaultsOnly.md)                                      | DetailsPanel, Editor | 在默认值细节面板可见，但不可编辑                                                                                                     | ★★★★★ |
| [VisibleInstanceOnly](UPROPERTY/DetaisPanel/VisibleInstanceOnly.md)                                      | DetailsPanel, Editor | 在实例细节面板可见，但不可编辑                                                                                                      | ★★★★★ |
| [EditFixedSize](UPROPERTY/DetaisPanel/EditFixedSize.md)                                    | DetailsPanel, Editor | 在细节面板上不允许改变该容器的元素个数。                                                                                                 | ★★★   |
| [NoClear](UPROPERTY/DetaisPanel/NoClear.md)                                                      | DetailsPanel, Editor | 指定该属性的编辑选项中不出现Clear按钮，不允许置null。                                                                                      | ★★★   |


 ## Config

| Name                                                                                                     | 引擎模块                 | 功能描述                                                                                                                 | 常用程度  |
|----------------------------------------------------------------------------------------------------------|----------------------|----------------------------------------------------------------------------------------------------------------------|-------|
| [Config](UPROPERTY/Config/Config.md)                                                                     | Config               | 指定该属性是一个配置属性，该属性可以被序列化读写到ini文件（路径由uclass的config标签指定）中。                                                               | ★★★   |
| [GlobalConfig](UPROPERTY/Config/GlobalConfig.md)                                            | Config               | 和Config一样指定该属性可作为配置读取和写入ini中，但只会读取写入到配置文件里基类的值，而不会使用配置文件里子类里的值。                                                      | ★★★   |


 ## Blueprint

| Name                                                                                                     | 引擎模块                 | 功能描述                                                                                                                 | 常用程度  |
|----------------------------------------------------------------------------------------------------------|----------------------|----------------------------------------------------------------------------------------------------------------------|-------|
| [BlueprintAuthorityOnly](UPROPERTY/Blueprint/BlueprintAuthorityOnly.md)           | Blueprint, Network   | 只能绑定为BlueprintAuthorityOnly的事件，让该多播委托只接受在服务端运行的事件                                                                    | ★★★   |
| [BlueprintReadWrite](UPROPERTY/Blueprint/BlueprintReadWrite.md)                       | Blueprint            | 可从蓝图读取或写入此属性。                                                                                                        | ★★★★★ |
| [BlueprintReadOnly](UPROPERTY/Blueprint/BlueprintReadOnly.md)                          | Blueprint            | 此属性可由蓝图读取，但不能被修改。                                                                                                    | ★★★★★ |
| [BlueprintGetter](UPROPERTY/Blueprint/BlueprintGetter.md)                                | Blueprint            | 为属性定义一个自定义的Get函数来读取。                                                                                                 | ★★★   |
| [Getter](UPROPERTY/Blueprint/Getter.md)                                                                  | Blueprint            | 为属性增加一个C++的Get函数，只在C++层面应用。                                                                                          | ★★★   |
| [Setter](UPROPERTY/Blueprint/Setter.md)                                                           | Blueprint            | 为属性增加一个C++的Set函数，只在C++层面应用。                                                                                          | ★★★   |
| [BlueprintSetter](UPROPERTY/Blueprint/BlueprintSetter.md)                                                | Blueprint            | 采用一个自定义的set函数来读取。                                                                                                    | ★★★   |
| [BlueprintCallable](UPROPERTY/Blueprint/BlueprintCallable.md)                          | Blueprint            | 在蓝图中可以调用这个多播委托                                                                                                       | ★★★   |
| [BlueprintAssignable](UPROPERTY/Blueprint/BlueprintAssignable.md)                    | Blueprint            | 在蓝图中可以为这个多播委托绑定事件                                                                                                    | ★★★   |


 ## Behavior

| Name                                                                                                     | 引擎模块                 | 功能描述                                                                                                                 | 常用程度  |
|----------------------------------------------------------------------------------------------------------|----------------------|----------------------------------------------------------------------------------------------------------------------|-------|
| [Localized](UPROPERTY/Asset/Localized.md)                                                                | Behavior             | 此属性的值将拥有一个定义的本地化值。多用于字符串。暗示为 ReadOnly。该值有一个本地化值。最常标记在string上                                                         | 💀    |
| [Native](UPROPERTY/UHT/Native.md)                                                                        | Behavior             | 属性为本地：C++代码负责对其进行序列化并公开到垃圾回收 。                                                                                       | 💀    |


 ## Asset

| Name                                                                                                     | 引擎模块                 | 功能描述                                                                                                                 | 常用程度  |
|----------------------------------------------------------------------------------------------------------|----------------------|----------------------------------------------------------------------------------------------------------------------|-------|
| [AssetRegistrySearchable](UPROPERTY/Asset/AssetRegistrySearchable.md)            | Asset                | 标记该属性可以作为AssetRegistry的Tag和Value值来进行资产的过滤搜索                                                                          | ★★★   |

## 行为

UE5.8 UHT 在 property parser 中解析 `UPROPERTY`，成员属性使用 `UhtTableNames.PropertyMember` 的 specifier table。该页是 UPROPERTY 条目索引，不是单个 specifier。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 UHT parser keyword table for the macro
  - UE5.8 `UhtTables.cs` specifier table registration

## 常见误用

把总览页当成可填写 specifier；具体行为应跳到 property specifier 或 metadata 条目。
