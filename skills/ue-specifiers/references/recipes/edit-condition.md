# 场景：EditCondition

## 适用问题

用户通常会这样问：

- 一个属性只有开关打开时才能编辑，怎么写？
- 不满足条件时想隐藏属性而不是置灰。
- bool 开关能不能显示在同一行？

## 推荐写法

```cpp
UPROPERTY(EditAnywhere, Category="Damage")
bool bOverrideDamage = false;

UPROPERTY(EditAnywhere, Category="Damage", meta=(EditCondition="bOverrideDamage"))
float OverrideDamage = 10.0f;
```

## 为什么这样写

- `EditCondition` 让 Details Panel 根据条件控制属性编辑状态。
- 条件字段和被控制字段应保持命名清晰。
- 这只影响编辑器 UI，不应替代运行时校验。

## 替代方案

### 不满足条件时隐藏

```cpp
UPROPERTY(EditAnywhere, Category="Damage", meta=(EditCondition="bOverrideDamage", EditConditionHides))
float OverrideDamage = 10.0f;
```

适合：条件不满足时字段没有意义。

不适合：用户需要看到当前被禁用的配置值。

### 内联条件开关

```cpp
UPROPERTY(EditAnywhere, Category="Damage", meta=(InlineEditConditionToggle))
bool bOverrideDamage = false;

UPROPERTY(EditAnywhere, Category="Damage", meta=(EditCondition="bOverrideDamage"))
float OverrideDamage = 10.0f;
```

适合：开关只服务于一个配置项。

不适合：开关有独立业务含义，需要单独展示。

## 常见误用

- 把 `EditCondition` 当作运行时合法性校验。
- 条件字段重命名后忘记更新字符串。
- 过度隐藏字段，导致配置状态不可见。

## 版本状态

- UE5.8: verified_UE5.8

## 相关知识

- indexes: `references/indexes/metas.index.md`
- original docs: `references/sources/Meta/DetailsPanel/EditCondition/EditCondition.md`, `references/sources/Meta/DetailsPanel/EditConditionHides/EditConditionHides.md`, `references/sources/Meta/DetailsPanel/InlineEditConditionToggle/InlineEditConditionToggle.md`
