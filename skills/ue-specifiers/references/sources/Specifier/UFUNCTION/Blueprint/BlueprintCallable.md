---
title: "BlueprintCallable"
id: "UFUNCTION.BlueprintCallable"
kind: "specifier"
symbol: "BlueprintCallable"
scope: "UFUNCTION"
category: "Blueprint"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "暴露到蓝图中可被调用"
usage: "UFUNCTION / Blueprint"
---

# BlueprintCallable

## Decision Summary

- **Use when:** 函数需要作为有执行引脚的 Blueprint 节点被调用。
- **Do not use when:** 函数只是无副作用查询并适合 pure 节点形态。
- **Requires:** 公开给 Blueprint 的函数通常应有清晰 `Category`，并保持参数/返回类型 Blueprint 可反射。
- **Conflicts:** 无直接互斥；与 `BlueprintPure` 组合时节点会变成 pure 形态。
- **Prefer instead:** 查询型 getter 用 `BlueprintPure`；事件覆写入口用 `BlueprintImplementableEvent` 或 `BlueprintNativeEvent`。

- **功能描述：** 暴露到蓝图中可被调用

- **元数据类型：** bool
- **引擎模块：** Blueprint
- **作用机制：** 在FunctionFlags增加FUNC_BlueprintCallable
- **常用程度：** ★★★★★

## 行为

`BlueprintCallable` 把 C++ 函数暴露为 Blueprint 可调用节点。它只表示可调用，不表示函数是 pure、线程安全、只在服务端执行或自动拥有某种权限。

## UE5.8 审计结论

在 UE5.8 UHT 源码 `UhtFunctionSpecifiers.cs` 中，`BlueprintCallableSpecifier` 会设置 `EFunctionFlags.BlueprintCallable`。函数在 Blueprint 菜单中的分类和展示还会受到 `Category`、函数所在类、访问上下文、metadata 以及 Blueprint 类型限制影响。

## 常见误用

- `BlueprintCallable` 不等于 `BlueprintPure`；需要无执行引脚的纯函数时使用 `BlueprintPure`。
- 需要网络权限或表现层限制时另加 `BlueprintAuthorityOnly`、`BlueprintCosmetic` 或运行时校验。
- 建议为常用节点提供清晰 `Category`，否则路由和查找体验会变差。

## 测试代码：

```cpp
UFUNCTION(BlueprintCallable)
void MyFunc_BlueprintCallable() {}
```

## 效果展示：

