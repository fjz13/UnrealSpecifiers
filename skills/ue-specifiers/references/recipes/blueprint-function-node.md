# 场景：Blueprint 函数节点

## 适用问题

用户通常会这样问：

- C++ 函数想在 Blueprint 里调用，应该写什么？
- 查询函数应该用 `BlueprintCallable` 还是 `BlueprintPure`？
- Blueprint 节点名称和分类怎么设置？

## 推荐写法

```cpp
UFUNCTION(BlueprintCallable, Category="Inventory")
void AddItem(FName ItemId, int32 Count);
```

## 为什么这样写

- `BlueprintCallable` 让函数生成带执行引脚的 Blueprint 节点。
- `Category` 给节点分组，方便 Blueprint 菜单搜索和组织。
- 有副作用的函数不要做成 `BlueprintPure`。

## 替代方案

### 无副作用查询

```cpp
UFUNCTION(BlueprintPure, Category="Inventory")
int32 GetItemCount(FName ItemId) const;
```

适合：只读查询、计算结果、无状态修改。

不适合：修改对象、触发事件、执行异步或网络逻辑。

### 自定义显示名

```cpp
UFUNCTION(BlueprintCallable, Category="Inventory", meta=(DisplayName="Add Inventory Item"))
void AddItem(FName ItemId, int32 Count);
```

适合：C++ 命名和 Blueprint 展示命名需要不同。

不适合：为了美化而隐藏语义不清的 API。

## 常见误用

- 把有副作用的函数标为 `BlueprintPure`。
- 忘记 `Category`。
- 只用 `DisplayName` 解决命名问题，却不改善 C++ API 本身。

## 版本状态

- UE5.8: verified_UE5.8

## 相关知识

- indexes: `references/indexes/specifiers.index.md`, `references/indexes/metas.index.md`
- original docs: `references/sources/Specifier/UFUNCTION/Blueprint/BlueprintCallable/BlueprintCallable.md`, `references/sources/Specifier/UFUNCTION/Blueprint/BlueprintPure/BlueprintPure.md`
