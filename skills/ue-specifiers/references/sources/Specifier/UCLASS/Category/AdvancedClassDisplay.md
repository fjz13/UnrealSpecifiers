---
title: "AdvancedClassDisplay"
id: "UCLASS.AdvancedClassDisplay"
kind: "specifier"
symbol: "AdvancedClassDisplay"
scope: "UCLASS"
category: "Category"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "把该类下的所有属性都默认显示在高级目录下"
usage: "UCLASS / Category"
---

# AdvancedClassDisplay

## Decision Summary

- **Use when:** 类的属性在 Details Panel 中默认应偏高级展示。
- **Do not use when:** 类的大多数属性是日常配置入口。
- **Requires:** 类确实有 editor-exposed 属性需要这种展示策略。
- **Conflicts:** 不改变属性的编辑/可见权限。
- **Prefer instead:** 只对个别属性折叠时用属性侧 `AdvancedDisplay`。

- **功能描述：**  把该类下的所有属性都默认显示在高级目录下
- **引擎模块：** Category
- **元数据类型：** bool
- **作用机制：** 在Meta增加[AdvancedClassDisplay](../../../Meta/DetailsPanel/AdvancedClassDisplay.md)
- **常用程度：★★★★**

让这个类的所有属性显示在本身类的Detail面板的“高级”栏目下显示。

但是可以通过在单个属性上使用SimpleDisplay来重载掉。在搜索了一番源码后，发现使用AdvancedClassDisplay的只有3个Actor，且这3个Actor里都没有再定义属性。

## 示例代码：

```cpp
UCLASS(Blueprintable,AdvancedClassDisplay)
class INSIDER_API UMyClass_AdvancedClassDisplay :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyProperty;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,SimpleDisplay)
		int32 MyProperty_Simple;
};

UCLASS(Blueprintable)
class INSIDER_API UMyClass_NoAdvancedClassDisplay :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyProperty;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay)
		int32 MyProperty_Simple;
};
```

## 示例效果：

MyProperty_Simple即使在AdvancedClassDisplay的类中也依然是简单的显示。


## 原理：

```cpp
// Property is advanced if it is marked advanced or the entire class is advanced and the property not marked as simple
static const FName Name_AdvancedClassDisplay("AdvancedClassDisplay");
bool bAdvanced = Property.IsValid() ? ( Property->HasAnyPropertyFlags(CPF_AdvancedDisplay) || ( !Property->HasAnyPropertyFlags( CPF_SimpleDisplay ) && Property->GetOwnerClass() && Property->GetOwnerClass()->GetBoolMetaData(Name_AdvancedClassDisplay) ) ) : false;
```

## 行为

UE5.8 UHT 写入 `AdvancedClassDisplay=true` metadata，默认把类属性显示到 advanced 区域。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `UhtClassSpecifiers.cs` class specifier branch
  - UE5.8 `UhtClass.cs` class flag/metadata resolution and validation

## 常见误用

把 class specifier 的 metadata/flag 结果和 property/function specifier 混淆；或忽略继承/撤销类 specifier 的相互作用。
