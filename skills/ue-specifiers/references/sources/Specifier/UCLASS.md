---
title: "UCLASS(标识符)"
id: "UCLASS.UCLASS(标识符)"
kind: "specifier"
symbol: "UCLASS(标识符)"
scope: "UCLASS"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "UE5.8 UHT 通过 UhtClassParser 识别 UCLASS，创建 class 类型并使用 UhtTableNames.Class 的 keyword/specifier table 解析 specifier。该页是 UCLA"
usage: "UCLASS"
---

# UCLASS(标识符)

## Decision Summary

- **Use when:** `UCLASS(标识符)` specifier 的 `UCLASS` 场景需要：UE5.8 UHT 通过 UhtClassParser 识别 UCLASS，创建 class 类型并使用 UhtTableNames.Class 的 keyword/specifier table 解析 specifier。该页是 UCLA。
- **Do not use when:** 声明宏、目标类型或代码契约不属于 `UCLASS`。
- **Requires:** specifier 必须放在 UE5.8 UHT 支持的宏和声明位置，并满足正文 caveat。
- **Conflicts:** 不要和同类互斥 specifier 或语义相反的暴露/持久化/网络规则混用。
- **Prefer instead:** 能用更窄暴露范围或更明确 metadata 表达时，优先选择更窄方案。

## UHT

| Name                                                       | 引擎模块 | 功能描述                                                     | 常用程度 |
| ---------------------------------------------------------- | -------- | ------------------------------------------------------------ | -------- |
| [NoExport](UCLASS/UHT/NoExport.md)                         | UHT      | 指定UHT不要用来自动生成注册的代码，而只是进行词法分析提取元数据。 | 💀        |
| [Intrinsic](UCLASS/UHT/Intrinsic.md)                       | UHT      | 指定UHT完全不为此类生成代码，需要自己手写。                  | 💀        |
| [Interface](UCLASS/UHT/Interface.md)                       | UHT      | 标识这个Class是个Interface。                                 | 💀        |
| [UCLASS_Empty](UCLASS/UHT/UCLASS_Empty.md)                         | UHT      | 留空的默认行为是不能在蓝图中被继承，不能在蓝图中定义变量，但拥有反射的功能。 | ★★★★★    |
| [Without_UCLASS](UCLASS/UHT/Without_UCLASS.md)                 | UHT      | 只是作为一个普通的C++对象，没有反射功能。                    | ★        |
| [CustomThunkTemplates](UCLASS/UHT/CustomThunkTemplates.md) | UHT      | Specifies the struct that contains the CustomThunk implementations | 💀        |
| [CustomConstructor](UCLASS/UHT/CustomConstructor.md)       | UHT      | 阻止构造函数声明自动生成。                                   | 💀        |
| [CustomFieldNotify](UCLASS/UHT/CustomFieldNotify.md)       | UHT      | 阻止UHT为该类生成FieldNotify的相关代码。                     | 💀        |


## Blueprint

| Name                                                         | 引擎模块  | 功能描述                                                     | 常用程度 |
| ------------------------------------------------------------ | --------- | ------------------------------------------------------------ | -------- |
| [Blueprintable](UCLASS/Blueprint/Blueprintable.md) | Blueprint | 可以在蓝图里被继承，隐含的作用也可当变量类型                 | ★★★★★    |
| [NotBlueprintable](UCLASS/Blueprint/NotBlueprintable.md)     | Blueprint | 不可在蓝图里继承，隐含作用也不可当作变量                     | ★★★★     |
| [BlueprintType](UCLASS/Blueprint/BlueprintType.md) | Blueprint | 可当做变量类型                                               | ★★★★★    |
| [NotBlueprintType](UCLASS/Blueprint/NotBlueprintType.md)     | Blueprint | 不可当做变量类型                                             | ★★★★     |
| [Abstract](UCLASS/Blueprint/Abstract.md)            | Blueprint | 指定此类为抽象基类。可被继承，但不可生成对象。               | ★★★★★    |
| [Const](UPARAM/Blueprint/Const.md)                     | Blueprint | 表示本类的内部属性不可在蓝图中被修改，只读不可写。           | ★★★      |
| [ShowFunctions](UCLASS/Blueprint/ShowFunctions.md)           | Blueprint | 在子类的函数覆盖列表里重新打开某些函数。                     | ★★       |
| [HideFunctions](UCLASS/Blueprint/HideFunctions.md) | Blueprint | 在子类的函数覆盖列表里隐藏掉某些函数。                       | ★★       |
| [SparseClassDataType](UCLASS/Blueprint/SparseClassDataType.md) | Blueprint | 让Actor的一些重复不变的数据存放在一个共同的结构里，以达到减少内容使用量的目的 | ★★★      |
| [NeedsDeferredDependencyLoading](UCLASS/Blueprint/NeedsDeferredDependencyLoading.md) | Blueprint |                                                              | 💀        |


## DllExport

| Name                                       | 引擎模块  | 功能描述                                      | 常用程度 |
| ------------------------------------------ | --------- | --------------------------------------------- | -------- |
| [MinimalAPI](UINTERFACE/UHT/MinimalAPI.md) | DllExport | 不dll导出该类的函数，只导出类型信息当作变量。 | ★★★      |


## Category

| Name                                                         | 引擎模块         | 功能描述                                                     | 常用程度 |
| ------------------------------------------------------------ | ---------------- | ------------------------------------------------------------ | -------- |
| [ClassGroup](UCLASS/Category/ClassGroup.md)       | Category | 指定组件在Actor的AddComponent面板里的分组，以及在蓝图右键菜单中的分组。 | ★★★     |
| [ShowCategories](UCLASS/Category/ShowCategories.md) | Category         | 在类的ClassDefaults属性面板里显示某些Category的属性。        | ★★★     |
| [HideCategories](UCLASS/Category/HideCategories.md) | Category         | 在类的ClassDefaults属性面板里隐藏某些Category的属性。        | ★★★★    |
| [CollapseCategories](UCLASS/Category/CollapseCategories.md) | Category         | 在类的属性面板里隐藏所有带Category的属性，但是只对带有多个嵌套Category的属性才起作用。 | ★★      |
| [DontCollapseCategories](UCLASS/Category/DontCollapseCategories.md) | Category         | 使继承自基类的CollapseCatogories说明符无效。                 | ★★      |
| [AutoExpandCategories](UCLASS/Category/AutoExpandCategories.md) | Category         | 指定此类的对象在细节面板中应该自动展开的Category。           | ★       |
| [AutoCollapseCategories](UCLASS/Category/AutoCollapseCategories.md) | Category         | AutoCollapseCategories说明符使父类上的 AutoExpandCategories 说明符的列出类别的效果无效。 | ★       |
| [DontAutoCollapseCategories](UCLASS/Category/DontAutoCollapseCategories.md) | Category         | 使列出的类别的继承自父类的AutoCollapseCategories说明符无效。 | ★       |
| [PrioritizeCategories](UCLASS/Category/PrioritizeCategories.md) | Category         | 把指定的属性目录优先显示在细节面板的前面。                   | ★★★     |
| [ComponentWrapperClass](UCLASS/Category/ComponentWrapperClass.md) | Category         | 指定该类为一个简单的封装类，忽略掉子类的Category相关设置。   | ★★      |
| [AdvancedClassDisplay](UCLASS/Category/AdvancedClassDisplay.md) | Category         | 把该类下的所有属性都默认显示在高级目录下                     | ★★★★    |


## TypePicker

| Name                                                         | 引擎模块   | 功能描述             | 常用程度 |
| ------------------------------------------------------------ | ---------- | -------------------- | -------- |
| [HideDropDown](UCLASS/HideDropDown.md) | TypePicker | 在类选择器中隐藏此类 | ★★       |

## Development

| Name                                                         | 引擎模块    | 功能描述                                                     | 常用程度 |
| ------------------------------------------------------------ | ----------- | ------------------------------------------------------------ | -------- |
| [Deprecated](UCLASS/Development/Deprecated.md)    | Development | 标明该类已经弃用。                                           | ★★★      |
| [Experimental](UCLASS/Development/Experimental.md) | Development | 标明该类是试验性版本，当前没有文档描述，之后有可能废弃掉。   | ★★★      |
| [EarlyAccessPreview](UCLASS/Development/EarlyAccessPreview.md) | Development | 标明该类是早期预览版，比试验版要更完善一些，但还是没到产品级。 | ★★★      |

## Instance

| Name                                                         | 引擎模块 | 功能描述                                                     | 常用程度 |
| ------------------------------------------------------------ | -------- | ------------------------------------------------------------ | -------- |
| [Within](UCLASS/Instance/Within.md)                          | Instance | 指定对象创建的时候必须依赖于OuterClassName的对象作为Outer。  | ★★★      |
| [DefaultToInstanced](UCLASS/Instance/DefaultToInstanced.md) | Instance | 指定该类的所有实例属性都默认是UPROPERTY(instanced)，即都默认创建新的实例，而不是对对象的引用。 | ★★★★     |
| [EditInlineNew](UCLASS/Instance/EditInlineNew.md) | Instance | 指定该类的对象可以在属性细节面板里直接内联创建，要和属性的Instanced配合。 | ★★★★★    |
| [NotEditInlineNew](UCLASS/Instance/NotEditInlineNew.md)      | Instance | 不能通过EditInline按钮创建                                   | ★        |


## Scene

| Name                                                         | 引擎模块         | 功能描述                                                     | 常用程度 |
| ------------------------------------------------------------ | ---------------- | ------------------------------------------------------------ | -------- |
| [NotPlaceable](UCLASS/Scene/NotPlaceable.md)    | Scene         | 标明该Actor不可被放置在关卡里                                | ★★★     |
| [Placeable](UCLASS/Scene/Placeable.md)             | Scene            | 标明该Actor可以放置在关卡里。                                | ★★★     |
| [ConversionRoot](UCLASS/Scene/ConversionRoot.md) | Scene            | 在场景编辑器里允许Actor在自身以及子类之间做转换              | ★       |

## Config

| Name                                                         | 引擎模块         | 功能描述                                                     | 常用程度 |
| ------------------------------------------------------------ | ---------------- | ------------------------------------------------------------ | -------- |
| [Config](UCLASS/Config/Config.md)                            | Config           | 指定配置文件的名字，把该对象的值保存到ini配置文件中。        | ★★★★★   |
| [PerObjectConfig](UCLASS/Config/PerObjectConfig.md)          | Config           | 在已经有config配置文件名字的情况下，指定应该按每个对象实例来存储值，而不是一个类一个存储值。 | ★★★★★   |
| [ConfigDoNotCheckDefaults](UCLASS/Config/ConfigDoNotCheckDefaults.md) | Config           | 指定在保存配置值的时候忽略上一级的配置值的一致性检查。       | ★       |
| [DefaultConfig](UCLASS/Config/DefaultConfig.md) | Config           | 指定保存到的配置文件层级是Project/Config/DefaultXXX.ini。    | ★★★     |
| [GlobalUserConfig](UCLASS/Config/GlobalUserConfig.md) | Config           | 指定保存到的配置文件层级是全局用户设置 Engine/Config/UserXXX.ini。 | ★★★     |
| [ProjectUserConfig](UCLASS/Config/ProjectUserConfig.md) | Config           | 指定保存到的配置文件层级是项目用户设置 Project/Config/UserXXX.ini。 | ★★★     |
| [EditorConfig](UCLASS/Config/EditorConfig.md)   | Config   | 用来在编辑器状态下保存信息。                                 | ★       |


## Serialization

| Name                                                         | 引擎模块      | 功能描述                                                     | 常用程度 |
| ------------------------------------------------------------ | ------------- | ------------------------------------------------------------ | -------- |
| [Transient](UCLASS/Serialization/Transient.md)     | Serialization | 指定该类的所有对象都略过序列化。                             | ★★★      |
| [NonTransient](UCLASS/Serialization/NonTransient.md)         | Serialization | 使继承自基类的Transient说明符无效。                          | ★★★      |
| [Optional](UCLASS/Serialization/Optional.md)        | Serialization | 标记该类的对象是可选的，在Cooking的时候可以选择是否要忽略保存它们。 | ★        |
| [MatchedSerializers](UCLASS/Serialization/MatchedSerializers.md) | Serialization | 指定类支持文本结构序列化                                     | 💀        |

## 行为

UE5.8 UHT 通过 `UhtClassParser` 识别 `UCLASS`，创建 class 类型并使用 `UhtTableNames.Class` 的 keyword/specifier table 解析 specifier。该页是 UCLASS 条目索引，不是单个 specifier。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 UHT parser keyword table for the macro
  - UE5.8 `UhtTables.cs` specifier table registration

## 常见误用

把总览页当成可填写 specifier；具体行为应跳到 class specifier 或 metadata 条目。
