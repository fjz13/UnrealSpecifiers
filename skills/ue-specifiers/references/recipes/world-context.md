# 场景：WorldContext

## 适用问题

用户通常会这样问：

- Blueprint Function Library 里静态函数怎么拿 World？
- `WorldContext`、`DefaultToSelf`、`HidePin` 怎么配？
- 为什么函数库节点需要手动接 WorldContext？

## 推荐写法

```cpp
UFUNCTION(BlueprintCallable, Category="World", meta=(WorldContext="WorldContextObject"))
static void DoWorldAction(const UObject* WorldContextObject);
```

## 为什么这样写

- `WorldContext` 告诉 Blueprint 节点哪个参数提供世界上下文。
- 静态函数库通常没有自然的 `this` world，需要显式上下文对象。
- 是否隐藏该 pin 取决于节点能否从调用上下文安全推断。

## 替代方案

### 默认使用 self 并隐藏上下文 pin

```cpp
UFUNCTION(BlueprintCallable, Category="World", meta=(WorldContext="WorldContextObject", DefaultToSelf="WorldContextObject", HidePin="WorldContextObject"))
static void DoWorldAction(const UObject* WorldContextObject);
```

适合：Blueprint 调用上下文能可靠提供对象。

不适合：函数可在无 world 或多 world 上下文中调用。

### 显式传入上下文

```cpp
UFUNCTION(BlueprintCallable, Category="World")
static void DoWorldActionExplicit(const UObject* WorldContextObject);
```

适合：调用者必须明确选择 world。

不适合：希望节点像 Kismet 常用函数一样自动适配上下文。

## 常见误用

- 在静态 Blueprint 函数中直接假设有有效 world。
- 隐藏 WorldContext pin 但节点可能在不合适上下文中调用。
- 参数名和 `WorldContext="..."` 字符串不一致。

## 版本状态

- UE5.8: verified_UE5.8

## 相关知识

- indexes: `references/indexes/metas.index.md`
- original docs: `references/sources/Meta/Blueprint/WorldContext/WorldContext.md`, `references/sources/Meta/Blueprint/DefaultToSelf/DefaultToSelf.md`, `references/sources/Meta/Pin/HidePin/HidePin.md`
