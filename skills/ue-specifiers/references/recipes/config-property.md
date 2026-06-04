# 场景：Config 属性

## 适用问题

用户通常会这样问：

- 属性想从 ini 配置读取，应该怎么写？
- `Config` 和 `GlobalConfig` 有什么区别？
- 为什么 `UPROPERTY(Config)` 没生效？

## 推荐写法

```cpp
UCLASS(Config=Game)
class UMySettingsObject : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(Config, EditDefaultsOnly, Category="Config")
    float SpawnRate = 1.0f;
};
```

## 为什么这样写

- 类上需要有 config 上下文，属性上的 `Config` 才有明确配置来源。
- `EditDefaultsOnly` 常用于默认配置对象，不鼓励每个实例随意改配置。
- `Category` 让配置字段在编辑器中可读。

## 替代方案

### 派生类共享全局配置

```cpp
UPROPERTY(GlobalConfig, EditDefaultsOnly, Category="Config")
float SpawnRate = 1.0f;
```

适合：不希望派生类覆盖的共享配置。

不适合：每个派生类需要不同默认值。

### 非配置运行时参数

```cpp
UPROPERTY(EditAnywhere, Category="Config")
float SpawnRate = 1.0f;
```

适合：普通设计参数，不走 ini。

不适合：需要配置文件持久化或部署覆盖。

## 常见误用

- 只给属性加 `Config`，类没有配置上下文。
- 用 `Config` 存运行时频繁变化状态。
- 把 `Config` 当作 SaveGame 使用。

## 版本状态

- UE5.8: pending_UE5.8_validation

## 相关知识

- indexes: `references/indexes/specifiers.index.md`
- original docs: `references/sources/Specifier/UPROPERTY/Config/Config.md`, `references/sources/Specifier/UPROPERTY/Config/GlobalConfig/GlobalConfig.md`
