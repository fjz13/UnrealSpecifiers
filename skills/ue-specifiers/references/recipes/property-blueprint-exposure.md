# 场景：属性 Blueprint 暴露

## 适用问题

用户通常会这样问：

- 这个属性想在 Blueprint 里读写，应该加什么？
- `EditAnywhere` 是不是等于 `BlueprintReadWrite`？
- 设计师能在面板调参数，蓝图只能读。

## 推荐写法

```cpp
UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Config")
float MoveSpeed = 600.0f;
```

## 为什么这样写

- `EditAnywhere` 控制 Details Panel 编辑。
- `BlueprintReadOnly` 控制 Blueprint 可读但不能直接写。
- `Category` 对 Blueprint 变量和 Details Panel 都有可读性价值。

## 替代方案

### Blueprint 可读写

```cpp
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Config")
float MoveSpeed = 600.0f;
```

适合：蓝图逻辑确实需要修改属性。

不适合：C++ 需要维护不变量或只允许函数修改。

### 只暴露运行时状态

```cpp
UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="State")
float CurrentHealth = 100.0f;
```

适合：蓝图读取状态，面板只展示。

不适合：设计师需要配置默认参数。

## 常见误用

- 只写 `EditAnywhere`，以为 Blueprint 可以访问。
- 只写 `BlueprintReadWrite`，以为 Details Panel 可以编辑。
- 同时写 `BlueprintReadOnly` 和 `BlueprintReadWrite`。

## 版本状态

- UE5.8: verified_UE5.8

## 相关知识

- indexes: `references/indexes/specifiers.index.md`
- conflicts: `references/conflicts/blueprint-readonly-vs-readwrite.md`
- original docs: `references/sources/Specifier/UPROPERTY/Blueprint/BlueprintReadOnly/BlueprintReadOnly.md`, `references/sources/Specifier/UPROPERTY/Blueprint/BlueprintReadWrite/BlueprintReadWrite.md`
