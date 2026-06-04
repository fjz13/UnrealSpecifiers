# Meta Development Config And Serialization

> Category source index. Use targeted search in this file, then open only the listed `Doc`.
> Resolve `Doc` relative to the nearest preceding `Doc root`; each `Doc root` is relative to `references/sources/`.

## Meta - Config

> Doc root: `Meta/Config/`

| ID | Summary | Usage | Doc |
|---|---|---|---|
| `ConfigHierarchyEditable` | 使得一个属性可以在Config的各个层级配置 | UPROPERTY | `ConfigHierarchyEditable.md` |
| `ConfigRestartRequired` | 使属性在设置里改变后弹出重启编辑器的对话框 | UPROPERTY | `ConfigRestartRequired.md` |
| `ConsoleVariable` | 把一个Conifg属性的值同步到一个同名的控制台变量 | UPROPERTY | `ConsoleVariable.md` |
| `EditorConfig` | 保存编辑器的配置 | UCLASS | `EditorConfig.md` |


## Meta - Development

> Doc root: `Meta/Development/`

| ID | Summary | Usage | Doc |
|---|---|---|---|
| `Comment` | 用来记录注释的内容 | Any | `Comment.md` |
| `DeprecatedFunction` | 标明一个函数已经被弃用 | UFUNCTION | `DeprecatedFunction.md` |
| `DeprecatedProperty` | 标记弃用，引用到该属性的蓝图会触发一个警告 | UPROPERTY | `DeprecatedProperty.md` |
| `DeprecationMessage` | 定义弃用的消息 | UCLASS, UFUNCTION, UPROPERTY | `DeprecationMessage.md` |
| `Development.Deprecated` | 指定该元素要废弃的引擎版本号 | Any | `Deprecated.md` |
| `DevelopmentOnly` | 使得一个函数变为DevelopmentOnly，意味着只会在Development模式中运行。适用于调试输出之类的功能，但在最终发布版中会跳过 | UFUNCTION | `DevelopmentOnly.md` |
| `DevelopmentStatus` | 标明开发状态 | UCLASS | `DevelopmentStatus.md` |
| `FriendlyName` | 和DisplayName一样？ | Any | `FriendlyName.md` |
| `ShortTooltip` | 提供一个更简洁版本的提示文本，例如在类型选择器的时候显示 | Any | `ShortTooltip.md` |
| `ToolTip` | 在Meta里提供一个提示文本，覆盖代码注释里的文本 | Any | `ToolTip.md` |


## Meta - General

> Doc root: `Meta/`

| ID | Summary | Usage | Doc |
|---|---|---|---|
| `Meta = (元数据)` | UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用 | meta=(...) | `Meta.md` |


## Meta - IgnoreForMemberInitializationTest

> Doc root: `Meta/Struct/`

| ID | Summary | Usage | Doc |
|---|---|---|---|
| `IgnoreForMemberInitializationTest` | 使得该属性忽略结构的未初始验证 | UPROPERTY | `IgnoreForMemberInitializationTest.md` |


## Meta - Serialization

> Doc root: `Meta/Serialization/`

| ID | Summary | Usage | Doc |
|---|---|---|---|
| `MatchedSerializers` | 只在NoExportTypes.h中使用，标明采用结构序列化器。是否支持文本导入导出 | UCLASS | `MatchedSerializers.md` |
| `SkipUCSModifiedProperties` | 允许ActorComponent里的属性在Actor构造函数里被修改后依然保存下来 | UPROPERTY | `SkipUCSModifiedProperties.md` |



