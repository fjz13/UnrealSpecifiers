# 场景：Instanced 子对象

## 适用问题

用户通常会这样问：

- UObject 子对象想在 Details Panel 里内联编辑，应该加什么？
- `Instanced` 是不是用来引用资产？
- 为什么子对象编辑后所有实例像共享了同一个对象？

## 推荐写法

```cpp
UCLASS(EditInlineNew, DefaultToInstanced)
class UMyRule : public UObject
{
    GENERATED_BODY()
};

UPROPERTY(EditAnywhere, Instanced, Category="Rules")
TObjectPtr<UMyRule> Rule;
```

## 为什么这样写

- `Instanced` 表达属性持有实例化子对象，而不是普通共享资产引用。
- 子对象类通常需要支持内联新建或默认实例化语义。
- 适合组合式配置对象和 per-owner 子对象数据。

## 替代方案

### 引用共享资产

```cpp
UPROPERTY(EditAnywhere, Category="Rules")
TObjectPtr<UMyRuleAsset> RuleAsset;
```

适合：多个对象共享同一份资产数据。

不适合：每个 owner 需要独立可编辑子对象实例。

### 数组内联子对象

```cpp
UPROPERTY(EditAnywhere, Instanced, Category="Rules")
TArray<TObjectPtr<UMyRule>> Rules;
```

适合：一组 owner 专属策略对象。

不适合：大量运行时对象频繁创建且性能敏感的场景。

## 常见误用

- 用 `Instanced` 引用应该共享的资产。
- 只给属性加 `Instanced`，但子对象类不支持编辑器内联创建。
- 没有考虑 UObject outer、GC 和序列化生命周期。

## 版本状态

- UE5.8: verified_UE5.8

## 相关知识

- indexes: `references/indexes/specifiers.index.md`
- original docs: `references/sources/Specifier/UPROPERTY/Instance/Instanced/Instanced.md`, `references/sources/Specifier/UCLASS/Instance/EditInlineNew/EditInlineNew.md`, `references/sources/Specifier/UCLASS/Instance/DefaultToInstanced/DefaultToInstanced.md`
