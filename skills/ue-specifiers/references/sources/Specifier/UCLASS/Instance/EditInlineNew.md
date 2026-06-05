---
title: "EditInlineNew"
id: "UCLASS.EditInlineNew"
kind: "specifier"
symbol: "EditInlineNew"
scope: "UCLASS"
category: "Instance"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定该类的对象可以在属性细节面板里直接内联创建，要和属性的Instanced配合"
usage: "UCLASS / Instance"
---

# EditInlineNew

## Decision Summary

- **Use when:** UObject 类需要能在拥有者 Details Panel 中以内联方式创建实例。
- **Do not use when:** 类应该作为独立资产、Actor、组件模板或外部引用被选择。
- **Requires:** 持有方属性通常需要 `Instanced`，否则内联创建缺少正确所有权语义。
- **Conflicts:** 不适合 Actor 类；Actor 实例应通过关卡放置或生成流程管理。
- **Prefer instead:** 资产型配置用 DataAsset/Blueprint 资产引用；组件用组件创建流程。

- **功能描述：**  指定该类的对象可以在属性细节面板里直接内联创建，要和属性的Instanced配合。
- **引擎模块：** Instance
- **元数据类型：** bool
- **作用机制：** 在ClassFlags中添加CLASS_EditInlineNew
- **关联项：** NotEditInlineNew (NotEditInlineNew.md)
- **常用程度：★★★★★**

指定该类的对象可以在属性细节面板里直接内联创建。

如果想在细节面板里直接创建对象，属性上也必须先标记Instanced或ShowInnerProperties。

EditInlineNew主要是用在UObject的子类上，一般不标EditInlineNew的是用在Actor或资产的引用上。注意EditInlineNew是表明增加从属性细节面板里直接创建对象实例的能力，而非限制只能在属性细节面板里创建，当然也可以自己手动NewObject再赋值给对象引用属性。

这个跟UPROPERTY上的Instanced能力是独立的。如果UCLASS上不加EditInlineNew，但是属性上加上Instanced，则在手动NewObject赋值该属性后，该属性也会展开内部属性来提供编辑功能。因为Instanced的属性会自动的在property上加上EditInline的meta。

此说明符会传播到所有子类；子类可通过 NotEditInlineNew 说明符覆盖它。

## 行为

`EditInlineNew` 让该 `UClass` 的实例可以作为 Details Panel 中的 inline object 候选类型被创建。它是类能力声明；属性侧仍需要 `Instanced`、`EditInline` metadata 或相关 inline 展示路径，编辑器才会提供内联对象编辑/创建入口。

## UE5.8 审计结论

在 UE5.8 UHT 源码 `UhtClassSpecifiers.cs` 中，`EditInlineNewSpecifier` 会添加 `EClassFlags.EditInlineNew`，`NotEditInlineNewSpecifier` 会移除该 flag。UE5.8 PropertyEditor 中 `PropertyNode.cpp` 根据属性 `EditInline` metadata 设置 `EditInlineNew` 节点标记；`SPropertyEditorEditInline.cpp` 的 inline class filter 要求候选类带 `CLASS_EditInlineNew`，并排除 hidden、hide dropdown、deprecated 以及未允许的 abstract 类。Hello 样例 `Class/Instance/MyClass_Edit.h` 覆盖 `EditInlineNew`、`NotEditInlineNew` 和 `Instanced` 组合。

## 常见误用

- `EditInlineNew` 不会让所有该类指针属性自动 inline 创建；属性通常还需要 `Instanced`。
- 它不是运行时创建对象的机制；C++ 中仍应使用 `NewObject`、默认子对象或合适的工厂逻辑。
- 普通资产引用和 Actor 引用通常不应该用 `EditInlineNew` 表达。

## 示例代码：

```cpp
UCLASS(Blueprintable, EditInlineNew)
class INSIDER_API UMyClass_EditInlineNew :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyProperty;
};

UCLASS(Blueprintable, NotEditInlineNew)
class INSIDER_API UMyClass_NotEditInlineNew :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyProperty;
};

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyClass_Edit_Test :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = InstancedProperty)
		UMyClass_EditInlineNew* MyEditInlineNew;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = InstancedProperty)
		UMyClass_NotEditInlineNew* MyNotEditInlineNew;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NormalProperty)
		UMyClass_EditInlineNew* MyEditInlineNew_NotInstanced;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NormalProperty)
		UMyClass_NotEditInlineNew* MyNotEditInlineNew_NotInstanced;
};
```

## 示例效果：

EditInlineNew支持直接C++或BP子类创建对象实例，然后在上面编辑实例。

而NotEditInlineNew的属性则无法找到支持的类来创建对象。

如果属性上没有Instanced则只能尝试去引用（找不到对象）。


## 原理：

判断该类是否有CLASS_EditInlineNew来决定是否可内联创建编辑。

```cpp
template <typename TClass, typename TIsChildOfFunction>
bool FPropertyEditorInlineClassFilter::IsClassAllowedHelper(TClass InClass, TIsChildOfFunction IsClassChildOf, TSharedRef< FClassViewerFilterFuncs > InFilterFuncs)
{
	const bool bMatchesFlags = InClass->HasAnyClassFlags(CLASS_EditInlineNew) &&
		!InClass->HasAnyClassFlags(CLASS_Hidden | CLASS_HideDropDown | CLASS_Deprecated) &&
		(bAllowAbstract || !InClass->HasAnyClassFlags(CLASS_Abstract));
}
```
