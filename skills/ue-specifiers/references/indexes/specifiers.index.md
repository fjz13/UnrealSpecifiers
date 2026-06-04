# Specifiers Index

> 该文件是给 AI 快速检索用的摘要索引，不替代原始 `references/sources` 文档。推荐前必须按状态门禁处理；`changed_in_version` 和 `removed_or_deprecated` 不能作为 UE5.8 常规方案推荐。
> 完整 source 路由索引见 `references/indexes/sources.index.md`。

## UPROPERTY - Details Panel

| ID | 摘要 | 使用场景 | 相关项 | 冲突项 | 状态 | source_doc |
|---|---|---|---|---|---|---|
| `UPROPERTY.EditAnywhere` | 默认值和实例 Details Panel 均可编辑 | 设计师和关卡实例都需要编辑 | `EditDefaultsOnly`, `EditInstanceOnly`, `BlueprintReadOnly`, `BlueprintReadWrite` | `VisibleAnywhere`, `VisibleDefaultsOnly`, `VisibleInstanceOnly` | `verified_UE5.8` | `references/sources/Specifier/UPROPERTY/DetaisPanel/EditAnywhere/EditAnywhere.md` |
| `UPROPERTY.EditDefaultsOnly` | 只允许默认值编辑 | 只希望在 CDO 或蓝图默认值中配置 | `EditAnywhere`, `VisibleDefaultsOnly` | `VisibleAnywhere`, `VisibleDefaultsOnly`, `VisibleInstanceOnly` | `verified_UE5.8` | `references/sources/Specifier/UPROPERTY/DetaisPanel/EditDefaultsOnly.md` |
| `UPROPERTY.EditInstanceOnly` | 只允许实例编辑 | 每个关卡实例可单独配置 | `EditAnywhere`, `VisibleInstanceOnly` | `VisibleAnywhere`, `VisibleDefaultsOnly`, `VisibleInstanceOnly` | `verified_UE5.8` | `references/sources/Specifier/UPROPERTY/DetaisPanel/EditInstanceOnly.md` |
| `UPROPERTY.VisibleAnywhere` | 默认值和实例 Details Panel 均可见但不可编辑 | 运行时或组件状态需要展示 | `VisibleDefaultsOnly`, `VisibleInstanceOnly`, `BlueprintReadOnly` | `EditAnywhere`, `EditDefaultsOnly`, `EditInstanceOnly` | `verified_UE5.8` | `references/sources/Specifier/UPROPERTY/DetaisPanel/VisibleAnywhere.md` |
| `UPROPERTY.VisibleDefaultsOnly` | 默认值 Details Panel 可见但不可编辑 | 默认对象或蓝图默认值只展示 | `VisibleAnywhere`, `VisibleInstanceOnly` | `EditAnywhere`, `EditDefaultsOnly`, `EditInstanceOnly` | `verified_UE5.8` | `references/sources/Specifier/UPROPERTY/DetaisPanel/VisibleDefaultsOnly.md` |
| `UPROPERTY.VisibleInstanceOnly` | 实例 Details Panel 可见但不可编辑 | 关卡实例只展示状态 | `VisibleAnywhere`, `VisibleDefaultsOnly` | `EditAnywhere`, `EditDefaultsOnly`, `EditInstanceOnly` | `verified_UE5.8` | `references/sources/Specifier/UPROPERTY/DetaisPanel/VisibleInstanceOnly.md` |
| `UPROPERTY.Category` | 设置 Details Panel 或 Blueprint 分类 | 属性需要清晰分组 | `BlueprintReadOnly`, `BlueprintReadWrite`, `BlueprintCallable` | 无明确冲突 | `verified_UE5.8` | `references/sources/Specifier/UPROPERTY/DetaisPanel/Category/Category.md` |

## UPROPERTY - Blueprint

| ID | 摘要 | 使用场景 | 相关项 | 冲突项 | 状态 | source_doc |
|---|---|---|---|---|---|---|
| `UPROPERTY.BlueprintReadOnly` | Blueprint 可读，不允许 Blueprint 直接写 | 蓝图需要访问状态但不应修改 | `EditAnywhere`, `VisibleAnywhere`, `Category` | `BlueprintReadWrite` | `verified_UE5.8` | `references/sources/Specifier/UPROPERTY/Blueprint/BlueprintReadOnly/BlueprintReadOnly.md` |
| `UPROPERTY.BlueprintReadWrite` | Blueprint 可读写 | 蓝图逻辑需要修改属性 | `EditAnywhere`, `Category` | `BlueprintReadOnly` | `verified_UE5.8` | `references/sources/Specifier/UPROPERTY/Blueprint/BlueprintReadWrite/BlueprintReadWrite.md` |

## UPROPERTY - Serialization And Config

| ID | 摘要 | 使用场景 | 相关项 | 冲突项 | 状态 | source_doc |
|---|---|---|---|---|---|---|
| `UPROPERTY.SaveGame` | 标记属性参与 SaveGame 序列化 | `USaveGame` 或存档系统持久化字段 | `BlueprintReadWrite`, `Category` | `Transient` 通常语义相反 | `verified_UE5.8` | `references/sources/Specifier/UPROPERTY/Serialization/SaveGame/SaveGame.md` |
| `UPROPERTY.Transient` | 标记属性不应被常规序列化持久保存 | 缓存、运行时临时状态 | `DuplicateTransient` | `SaveGame`, `Config` 语义需谨慎组合 | `verified_UE5.8` | `references/sources/Specifier/UPROPERTY/Serialization/Transient/Transient.md` |
| `UPROPERTY.DuplicateTransient` | 复制对象时重置或不保留该属性值 | 复制实例不应继承的运行时状态 | `Transient`, `NonPIEDuplicateTransient` | 无明确冲突 | `verified_UE5.8` | `references/sources/Specifier/UPROPERTY/Serialization/DuplicateTransient/DuplicateTransient.md` |
| `UPROPERTY.Config` | 属性从 config 文件读写 | 项目、类或对象配置项 | `UCLASS(Config=...)`, `GlobalConfig` | `Transient` 语义需谨慎组合 | `verified_UE5.8` | `references/sources/Specifier/UPROPERTY/Config/Config.md` |
| `UPROPERTY.GlobalConfig` | 类层级共享的 config 属性 | 派生类不希望覆盖的全局配置 | `Config`, `UCLASS(Config=...)` | 无明确冲突 | `verified_UE5.8` | `references/sources/Specifier/UPROPERTY/Config/GlobalConfig/GlobalConfig.md` |

## UPROPERTY - Replication And Instancing

| ID | 摘要 | 使用场景 | 相关项 | 冲突项 | 状态 | source_doc |
|---|---|---|---|---|---|---|
| `UPROPERTY.Replicated` | 属性参与网络复制 | 服务端状态同步到客户端 | `GetLifetimeReplicatedProps`, `ReplicatedUsing` | `NotReplicated` | `verified_UE5.8` | `references/sources/Specifier/UPROPERTY/Network/Replicated.md` |
| `UPROPERTY.ReplicatedUsing` | 属性复制后调用通知函数 | 客户端收到复制值后需要响应 | `Replicated`, `OnRep_` 函数 | `NotReplicated` | `verified_UE5.8` | `references/sources/Specifier/UPROPERTY/Network/ReplicatedUsing/ReplicatedUsing.md` |
| `UPROPERTY.Instanced` | 对象属性使用实例化子对象语义 | UObject 子对象需要内联实例和持久引用 | `EditInlineNew`, `DefaultToInstanced` | 普通资产引用场景不适合 | `verified_UE5.8` | `references/sources/Specifier/UPROPERTY/Instance/Instanced/Instanced.md` |

## UFUNCTION - Blueprint

| ID | 摘要 | 使用场景 | 相关项 | 冲突项 | 状态 | source_doc |
|---|---|---|---|---|---|---|
| `UFUNCTION.BlueprintCallable` | 生成可由 Blueprint 调用的函数节点 | 蓝图需要执行 C++ 函数 | `Category`, `BlueprintPure` | 无明确冲突，但语义需区分 Pure | `verified_UE5.8` | `references/sources/Specifier/UFUNCTION/Blueprint/BlueprintCallable/BlueprintCallable.md` |
| `UFUNCTION.BlueprintPure` | 生成无执行引脚的纯函数节点 | 查询值且不应产生副作用 | `BlueprintCallable`, `Category` | 有副作用函数不适合 | `verified_UE5.8` | `references/sources/Specifier/UFUNCTION/Blueprint/BlueprintPure/BlueprintPure.md` |
| `UFUNCTION.BlueprintImplementableEvent` | C++ 声明事件，Blueprint 实现 | C++ 调用 Blueprint 扩展点 | `BlueprintNativeEvent` | 不提供 C++ 默认实现 | `verified_UE5.8` | `references/sources/Specifier/UFUNCTION/Blueprint/BlueprintImplementableEvent/BlueprintImplementableEvent.md` |
| `UFUNCTION.BlueprintNativeEvent` | C++ 声明事件，可由 C++ 默认实现并被 Blueprint 覆盖 | 需要 C++ fallback 的蓝图事件 | `BlueprintImplementableEvent` | 忘记 `_Implementation` | `verified_UE5.8` | `references/sources/Specifier/UFUNCTION/Blueprint/BlueprintNativeEvent/BlueprintNativeEvent.md` |
| `UFUNCTION.CallInEditor` | 函数可在编辑器 Details Panel 中点击调用 | 编辑器内工具按钮或调试操作 | `BlueprintCallable`, `Category` | 运行时-only 操作需谨慎 | `verified_UE5.8` | `references/sources/Specifier/UFUNCTION/Blueprint/CallInEditor/CallInEditor.md` |

## UFUNCTION - Network

| ID | 摘要 | 使用场景 | 相关项 | 冲突项 | 状态 | source_doc |
|---|---|---|---|---|---|---|
| `UFUNCTION.Server` | RPC 在服务端执行 | 客户端请求服务端执行权威逻辑 | `Reliable`, `Unreliable`, `_Implementation` | 非网络对象或无所有权调用需谨慎 | `verified_UE5.8` | `references/sources/Specifier/UFUNCTION/Network/Server/Server.md` |
| `UFUNCTION.Client` | RPC 在 owning client 执行 | 服务端通知特定客户端 | `Reliable`, `Unreliable`, `_Implementation` | 非 owning client 语义需谨慎 | `verified_UE5.8` | `references/sources/Specifier/UFUNCTION/Network/Client/Client.md` |
| `UFUNCTION.NetMulticast` | RPC 在服务端和相关客户端执行 | 广播临时事件或表现 | `Reliable`, `Unreliable`, `_Implementation` | 持久状态不应只靠 multicast | `verified_UE5.8` | `references/sources/Specifier/UFUNCTION/Network/NetMulticast/NetMulticast.md` |

## Missing Or Deferred P0 Items

- `ShortToolTip` source appears as `references/sources/Meta/Development/ShortTooltip.md`; spelling differs from the P0 request and is tracked in `metas.index.md`.
- `ToolTip` source appears as `references/sources/Meta/Development/ToolTip/ToolTip.md`.
