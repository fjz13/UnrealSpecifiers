| Name                                                         | 引擎模块       | 功能描述                                                     | 常用程度 |
| ------------------------------------------------------------ | -------------- | ------------------------------------------------------------ | -------- |
| [Category](UFUNCTION/Category/Category.md)                   | Editor         | 在蓝图的右键菜单中为该函数指定类别分组，可以嵌套多级         | 5        |
| [CallInEditor](UFUNCTION/Blueprint/CallInEditor/CallInEditor.md) | Editor         | 可以在属性细节面板上作为一个按钮来调用该函数。               | 5        |
| [BlueprintCallable](UFUNCTION/Blueprint/BlueprintCallable/BlueprintCallable.md) | Blueprint      | 暴露到蓝图中可被调用                                         | 5        |
| [BlueprintPure](UFUNCTION/Blueprint/BlueprintPure/BlueprintPure.md) | Blueprint      | 指定作为一个纯函数，一般用于Get函数用来返回值。              | 5        |
| [BlueprintImplementableEvent](UFUNCTION/Blueprint/BlueprintImplementableEvent/BlueprintImplementableEvent.md) | Blueprint      | 指定一个函数调用点，可以在蓝图中重载实现。                   | 5        |
| [BlueprintNativeEvent](UFUNCTION/Blueprint/BlueprintNativeEvent/BlueprintNativeEvent.md) | Blueprint      | 可以在蓝图总覆盖实现，但是也在C++中提供一个默认实现。        | 5        |
| [BlueprintGetter](UFUNCTION/Blueprint/BlueprintGetter.md)    | Blueprint      | 指定该函数作为属性的自定义Get函数。                          | 2        |
| [BlueprintSetter](UFUNCTION/Blueprint/BlueprintSetter.md)    | Blueprint      | 指定该函数作为属性的自定义Set函数。                          | 2        |
| [Exec](UFUNCTION/Exec/Exec.md)                               | Behavior       | 在特定类里注册一个函数为作为控制台命令，允许接受参数。       | 3        |
| [BlueprintAuthorityOnly](UFUNCTION/Network/BlueprintAuthorityOnly/BlueprintAuthorityOnly.md) | Network        | 这个函数只能在拥有网络权限的端上运行。                       | 3        |
| [BlueprintCosmetic](UFUNCTION/Network/BlueprintCosmetic/BlueprintCosmetic.md) | Network        | 此函数为修饰性的，无法在DS上运行。                           | 3        |
| [Client](UFUNCTION/Network/Client/Client.md)                 | Network        | 在Client-owned的Actor上（PlayerController或Pawn）执行一个RPC函数，只运行在客户端上。对应的实现函数会添加_Implementation后缀。 | 5        |
| [Server](UFUNCTION/Network/Server/Server.md)                 | Network        | 在Client-owned的Actor上（PlayerController或Pawn）执行一个RPC函数，只运行在服务器上。对应的实现函数会添加_Implementation后缀 | 5        |
| [NetMulticast](UFUNCTION/Network/NetMulticast/NetMulticast.md) | Network        | 定义一个多播RPC函数在服务器和客户端上都执行。对应的实现函数会添加_Implementation后缀。 | 5        |
| [Reliable](UFUNCTION/Network/Reliable.md)                    | Network        | 指定一个RPC函数为“可靠的”，当遇见网络错误时会重发以保证到达。一般用在逻辑关键的函数上。 | 5        |
| [Unreliable](UFUNCTION/Network/Unreliable.md)                | Network        | 指定一个RPC函数为“不可靠的”，当遇见网络错误时就会被丢弃。一般用在传播效果表现的函数上，就算漏掉也没有关系。 | 5        |
| [WithValidation](UFUNCTION/Network/WithValidation.md)        | Network        | 指定一个RPC函数在执行前需要验证，只有验证通过才可以执行。    | 5        |
| [ServiceRequest](UFUNCTION/Network/ServiceRequest.md)        | Network        | 此函数为RPC（远程过程调用）服务请求。rpc服务请求             |          |
| [ServiceResponse](UFUNCTION/Network/ServiceResponse.md)      | Network        | 此函数为RPC服务响应。rpc服务回复                             |          |
| [BlueprintInternalUseOnly](UFUNCTION/UHT/BlueprintInternalUseOnly/BlueprintInternalUseOnly.md) | Blueprint, UHT | 指示不应向最终用户公开此函数。蓝图内部调用，不暴露给用户。   | 3        |
| [CustomThunk](UFUNCTION/UHT/CustomThunk/CustomThunk.md)      | UHT            | 指定UHT不为该函数生成蓝图调用的辅助函数，而需要用户自定义编写。 | 3        |
| [SealedEvent](UFUNCTION/Blueprint/SealedEvent/SealedEvent.md) | Behavior       | 无法在子类中覆盖此函数。SealedEvent关键词只能用于事件。对于非事件函数，请将它们声明为static或final，以密封它们。 |          |
| [Variadic](UFUNCTION/UHT/Variadic/Variadic.md)               | Blueprint, UHT | 标识一个函数可以接受任意类型的多个参数（包括input/output)．  | 3        |
| [FieldNotify](UFUNCTION/UHT/FieldNotify/FieldNotify.md)      | UHT            | 为该函数创建一个FieldNotify的绑定点。                        | 3        |
