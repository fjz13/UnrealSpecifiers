# 场景：Details Panel 属性编辑

## 适用问题

用户通常会这样问：

- 这个属性想在 Details Panel 里编辑，应该用什么？
- `EditAnywhere` 和 `VisibleAnywhere` 有什么区别？
- 只想让蓝图默认值能改，不想让关卡实例改。

## 推荐写法

```cpp
UPROPERTY(EditAnywhere, Category="Config")
float MoveSpeed = 600.0f;
```

## 为什么这样写

- `EditAnywhere` 控制默认值和实例 Details Panel 都可编辑。
- `Category` 让属性在 Details Panel 中分组，避免落入默认分类。
- Details Panel 可编辑性和 Blueprint 可访问性是两件事；需要 Blueprint 访问时另加 `BlueprintReadOnly` 或 `BlueprintReadWrite`。

## 替代方案

### 只允许默认值编辑

```cpp
UPROPERTY(EditDefaultsOnly, Category="Config")
float MoveSpeed = 600.0f;
```

适合：类默认值、蓝图默认值配置。

不适合：关卡中每个实例要单独改值。

### 只展示运行时状态

```cpp
UPROPERTY(VisibleAnywhere, Category="State")
float CurrentHealth = 100.0f;
```

适合：只读展示组件、状态、缓存结果。

不适合：设计师需要在面板中调参。

## 常见误用

- 同时写 `EditAnywhere` 和 `VisibleAnywhere`。
- 以为 `EditAnywhere` 会自动让 Blueprint 读写。
- 忘记 `Category`，导致属性分类混乱。

## 版本状态

- UE5.8: verified_UE5.8

## 相关知识

- indexes: `references/indexes/specifiers.index.md`
- conflicts: `references/conflicts/property-edit-vs-visible.md`
- original docs: `references/sources/Specifier/UPROPERTY/DetaisPanel/EditAnywhere/EditAnywhere.md`
