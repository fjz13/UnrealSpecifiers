---
title: "ShowCategories"
id: "meta.ShowCategories"
kind: "meta"
symbol: "ShowCategories"
category: "DetailsPanel"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "显示类别"
usage: "UCLASS"
---

# ShowCategories

## Decision Summary

- **Use when:** `ShowCategories` metadata 的 `UCLASS` 场景需要：显示类别。
- **Do not use when:** 目标声明不属于 `UCLASS`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 显示类别
- **使用位置：** UCLASS
- **元数据类型：** strings="a，b，c"
- **关联项：** [HideCategories](HideCategories.md)

在类上面标记的ShowCategories，并不会保存到meta中去，只是用来抹除基类HideCategories的设置。因此meta里的ShowCategories是没有用到的。

```cpp
//(BlueprintType = true, IncludePath = Class/Display/MyClass_HideCategories.h, IsBlueprintBase = true, ModuleRelativePath = Class/Display/MyClass_HideCategories.h)
UCLASS(Blueprintable, ShowCategories = MyGroup1)
class INSIDER_API UMyClass_ShowCategories :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Property_NotInGroup;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyGroup1)
		int Property_Group1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyGroup2 | MyGroup22")
		int Property_Group222;
};
```

## 行为

UE5.8 class metadata/list；由 UCLASS `ShowCategories` 写入，用于恢复/显示分类。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `ObjectMacros.h` property/class metadata declaration/comment
  - UE5.8 `PropertyEditor` Details metadata usage

## 常见误用

参数名、属性名或目标宏写错导致 metadata 被保留但没有对应编辑器/Blueprint 行为。
