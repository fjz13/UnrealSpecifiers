---
title: "UFUNCTION(标识符)"
id: "UFUNCTION.UFUNCTION(标识符)"
kind: "specifier"
symbol: "UFUNCTION(标识符)"
scope: "UFUNCTION"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "UE5.8 UHT 源码仍注册并处理该 UFUNCTION 条目；本轮按 UE5.8 标记为已验证"
usage: "UFUNCTION"
---

# UFUNCTION(标识符)

## Editor

| Name                                                         | 引擎模块 | 功能描述                                             | 常用程度 |
| ------------------------------------------------------------ | -------- | ---------------------------------------------------- | -------- |
| [Category](UFUNCTION/Category.md)                   | Editor   | 在蓝图的右键菜单中为该函数指定类别分组，可以嵌套多级 | ★★★★★    |
| [CallInEditor](UFUNCTION/Blueprint/CallInEditor.md) | Editor   | 可以在属性细节面板上作为一个按钮来调用该函数。       | ★★★★★    |


## Blueprint

| Name                                                         | 引擎模块  | 功能描述                                              | 常用程度 |
| ------------------------------------------------------------ | --------- | ----------------------------------------------------- | -------- |
| [BlueprintCallable](UFUNCTION/Blueprint/BlueprintCallable.md) | Blueprint | 暴露到蓝图中可被调用                                  | ★★★★★    |
| [BlueprintPure](UFUNCTION/Blueprint/BlueprintPure.md) | Blueprint | 指定作为一个纯函数，一般用于Get函数用来返回值。       | ★★★★★    |
| [BlueprintImplementableEvent](UFUNCTION/Blueprint/BlueprintImplementableEvent.md) | Blueprint | 指定一个函数调用点，可以在蓝图中重载实现。            | ★★★★★    |
| [BlueprintNativeEvent](UFUNCTION/Blueprint/BlueprintNativeEvent.md) | Blueprint | 可以在蓝图总覆盖实现，但是也在C++中提供一个默认实现。 | ★★★★★    |
| [BlueprintGetter](UFUNCTION/Blueprint/BlueprintGetter.md)    | Blueprint | 指定该函数作为属性的自定义Get函数。                   | ★★       |
| [BlueprintSetter](UFUNCTION/Blueprint/BlueprintSetter.md)    | Blueprint | 指定该函数作为属性的自定义Set函数。                   | ★★       |


## Behavior

| Name                                                         | 引擎模块 | 功能描述                                                     | 常用程度 |
| ------------------------------------------------------------ | -------- | ------------------------------------------------------------ | -------- |
| [Exec](UFUNCTION/Exec.md)                               | Behavior | 在特定类里注册一个函数为作为控制台命令，允许接受参数。       | ★★★      |
| [SealedEvent](UFUNCTION/Blueprint/SealedEvent.md) | Behavior | 无法在子类中覆盖此函数。SealedEvent关键词只能用于事件。对于非事件函数，请将它们声明为static或final，以密封它们。 | 💀        |


## Network

| Name                                                         | 引擎模块 | 功能描述                                                     | 常用程度 |
| ------------------------------------------------------------ | -------- | ------------------------------------------------------------ | -------- |
| [BlueprintAuthorityOnly](UFUNCTION/Network/BlueprintAuthorityOnly.md) | Network  | 这个函数只能在拥有网络权限的端上运行。                       | ★★★      |
| [BlueprintCosmetic](UFUNCTION/Network/BlueprintCosmetic.md) | Network  | 此函数为修饰性的，无法在DS上运行。                           | ★★★      |
| [Client](UFUNCTION/Network/Client.md)                 | Network  | 在Client-owned的Actor上（PlayerController或Pawn）执行一个RPC函数，只运行在客户端上。对应的实现函数会添加_Implementation后缀。 | ★★★★★    |
| [Server](UFUNCTION/Network/Server.md)                 | Network  | 在Client-owned的Actor上（PlayerController或Pawn）执行一个RPC函数，只运行在服务器上。对应的实现函数会添加_Implementation后缀 | ★★★★★    |
| [NetMulticast](UFUNCTION/Network/NetMulticast.md) | Network  | 定义一个多播RPC函数在服务器和客户端上都执行。对应的实现函数会添加_Implementation后缀。 | ★★★★★    |
| [Reliable](UFUNCTION/Network/Reliable.md)                    | Network  | 指定一个RPC函数为“可靠的”，当遇见网络错误时会重发以保证到达。一般用在逻辑关键的函数上。 | ★★★★★    |
| [Unreliable](UFUNCTION/Network/Unreliable.md)                | Network  | 指定一个RPC函数为“不可靠的”，当遇见网络错误时就会被丢弃。一般用在传播效果表现的函数上，就算漏掉也没有关系。 | ★★★★★    |
| [WithValidation](UFUNCTION/Network/WithValidation.md)        | Network  | 指定一个RPC函数在执行前需要验证，只有验证通过才可以执行。    | ★★★★★    |
| [ServiceRequest](UFUNCTION/Network/ServiceRequest.md)        | Network  | 此函数为RPC（远程过程调用）服务请求。rpc服务请求             | 💀        |
| [ServiceResponse](UFUNCTION/Network/ServiceResponse.md)      | Network  | 此函数为RPC服务响应。rpc服务回复                             | 💀        |


## UHT

| Name                                                         | 引擎模块       | 功能描述                                                     | 常用程度 |
| ------------------------------------------------------------ | -------------- | ------------------------------------------------------------ | -------- |
| [BlueprintInternalUseOnly](UFUNCTION/UHT/BlueprintInternalUseOnly.md) | Blueprint, UHT | 指示不应向最终用户公开此函数。蓝图内部调用，不暴露给用户。   | ★★★      |
| [CustomThunk](UFUNCTION/UHT/CustomThunk.md)      | UHT            | 指定UHT不为该函数生成蓝图调用的辅助函数，而需要用户自定义编写。 | ★★★      |
| [Variadic](UFUNCTION/UHT/Variadic.md)               | Blueprint, UHT | 标识一个函数可以接受任意类型的多个参数（包括input/output)．  | ★★★      |
| [FieldNotify](UFUNCTION/UHT/FieldNotify.md)      | UHT            | 为该函数创建一个FieldNotify的绑定点。                        | ★★★      |
## UE5.8 审计结论

UE5.8 UHT 源码仍注册并处理该 UFUNCTION 条目；本轮按 UE5.8 标记为已验证。
