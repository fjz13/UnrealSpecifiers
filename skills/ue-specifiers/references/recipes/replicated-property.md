# 场景：复制属性

## 适用问题

用户通常会这样问：

- 这个属性要同步到客户端，应该加什么？
- `Replicated` 和 `ReplicatedUsing` 怎么选？
- `OnRep_` 函数什么时候需要？

## 推荐写法

```cpp
UPROPERTY(ReplicatedUsing=OnRep_Health)
float Health = 100.0f;

UFUNCTION()
void OnRep_Health();
```

## 为什么这样写

- `ReplicatedUsing` 表示属性复制后触发通知函数。
- `OnRep_Health` 用于客户端响应复制值变化。
- 仍需在 C++ 中实现复制注册；specifier 本身不是完整复制配置。

## 替代方案

### 只复制不需要通知

```cpp
UPROPERTY(Replicated)
int32 TeamId = 0;
```

适合：客户端只需要读取最终值。

不适合：收到新值后需要刷新 UI、播放表现或重建状态。

### Blueprint 可读复制状态

```cpp
UPROPERTY(ReplicatedUsing=OnRep_Health, BlueprintReadOnly, Category="State")
float Health = 100.0f;
```

适合：Blueprint 需要读取同步状态。

不适合：让客户端 Blueprint 任意写权威状态。

## 常见误用

- 只写 `Replicated`，忘记注册生命周期复制属性。
- `ReplicatedUsing=OnRep_X` 但没有声明对应 `UFUNCTION()`。
- 用 multicast RPC 代替持久状态复制。

## 版本状态

- UE5.8: verified_UE5.8

## 相关知识

- indexes: `references/indexes/specifiers.index.md`
- conflicts: `references/conflicts/replication-conflicts.md`
- original docs: `references/sources/Specifier/UPROPERTY/Network/Replicated.md`, `references/sources/Specifier/UPROPERTY/Network/ReplicatedUsing/ReplicatedUsing.md`
