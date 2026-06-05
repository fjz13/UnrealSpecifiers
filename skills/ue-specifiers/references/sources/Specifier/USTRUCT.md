---
title: "USTRUCT(标识符)"
id: "USTRUCT.USTRUCT(标识符)"
kind: "specifier"
symbol: "USTRUCT(标识符)"
scope: "USTRUCT"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "UE5.8 UHT 通过 UhtScriptStructParser 识别 USTRUCT，创建 script struct 并使用 UhtTableNames.ScriptStruct 的 keyword/specifier table "
usage: "USTRUCT"
---

# USTRUCT(标识符)

## Decision Summary

- **Use when:** `USTRUCT(标识符)` specifier 的 `USTRUCT` 场景需要：UE5.8 UHT 通过 UhtScriptStructParser 识别 USTRUCT，创建 script struct 并使用 UhtTableNames.ScriptStruct 的 keyword/specifier table。
- **Do not use when:** 声明宏、目标类型或代码契约不属于 `USTRUCT`。
- **Requires:** specifier 必须放在 UE5.8 UHT 支持的宏和声明位置，并满足正文 caveat。
- **Conflicts:** 不要和同类互斥 specifier 或语义相反的暴露/持久化/网络规则混用。
- **Prefer instead:** 能用更窄暴露范围或更明确 metadata 表达时，优先选择更窄方案。

 ## UHT

| Name                                                         | 引擎模块      | 功能描述                                                     | 常用程度 |
| ------------------------------------------------------------ | ------------- | ------------------------------------------------------------ | -------- |
| [NoExport](USTRUCT/UHT/NoExport.md)                 | UHT           | 指定UHT不要用来自动生成注册的代码，而只是进行词法分析提取元数据。 | ★        |
| [Atomic](USTRUCT/UHT/Atomic.md)                       | UHT           | 指定该结构在序列化的时候总是一整个输出全部属性，而不是只输出改变的属性。 | ★        |
| [IsAlwaysAccessible](USTRUCT/UHT/IsAlwaysAccessible.md)      | UHT           | 指定UHT在生成文件的时候总是可以访问到改结构的声明，否则要在gen.cpp里生成镜像结构定义 | 💀        |
| [HasDefaults](USTRUCT/UHT/HasDefaults.md)                    | UHT           | 指定该结构的字段拥有默认值。这样如果本结构作为函数参数或返回值时候，函数则可以为其提供默认值。 | 💀        |
| [HasNoOpConstructor](USTRUCT/UHT/HasNoOpConstructor.md)      | UHT           | 指定该结构拥有ForceInit的构造函数，这样在作为BP function返回值的时候，可以调用来初始化 | 💀        |
| [IsCoreType](USTRUCT/UHT/IsCoreType.md)                      | UHT           | 指定该结构是核心类，UHT在用它的时候不需要前向声明。          | 💀        |


 ## Blueprint

| Name                                                         | 引擎模块      | 功能描述                                                     | 常用程度 |
| ------------------------------------------------------------ | ------------- | ------------------------------------------------------------ | -------- |
| [BlueprintType](USTRUCT/Blueprint/BlueprintType.md) | Blueprint     | 允许这个结构在蓝图中声明变量                                 | ★★★★★    |
| [BlueprintInternalUseOnly](USTRUCT/Blueprint/BlueprintInternalUseOnly.md) | Blueprint     | 不可定义新BP变量，但可作为别的类的成员变量暴露和变量传递     | ★★       |
| [BlueprintInternalUseOnlyHierarchical](USTRUCT/Blueprint/BlueprintInternalUseOnlyHierarchical.md) | Blueprint     | 在BlueprintInternalUseOnly的基础上，增加了子类也不能定义新BP变量的限制。 | ★        |


 ## Serialization

| Name                                                         | 引擎模块      | 功能描述                                                     | 常用程度 |
| ------------------------------------------------------------ | ------------- | ------------------------------------------------------------ | -------- |
| [immutable](USTRUCT/immutable.md)              | Serialization | Immutable is only legal in Object.h and is being phased out, do not use on new structs! | 💀        |

## 行为

UE5.8 UHT 通过 `UhtScriptStructParser` 识别 `USTRUCT`，创建 script struct 并使用 `UhtTableNames.ScriptStruct` 的 keyword/specifier table 解析 specifier。该页是 USTRUCT 条目索引，不是单个 specifier。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `UhtScriptStructParser.cs` routes `USTRUCT` to script-struct specifier table
  - UE5.8 `UhtTables.cs` creates the `ScriptStruct` keyword/specifier table

## 常见误用

把总览页当成 specifier；具体行为应跳转到 `BlueprintType`、serialization specifier 或 struct metadata。
