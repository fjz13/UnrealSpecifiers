---
title: "Category"
id: "UPROPERTY.Category"
kind: "specifier"
symbol: "Category"
scope: "UPROPERTY"
category: "DetailsPanel"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定属性的类别，使用 | 运算符定义嵌套类目"
usage: "UPROPERTY / DetailsPanel"
---

# Category

## Decision Summary

- **Use when:** Details Panel 或 Blueprint 中的属性需要清晰分类。
- **Do not use when:** 属性未暴露给 editor/Blueprint，或分类只服务 C++ 阅读。
- **Requires:** 分类名应短、稳定，并符合项目约定；嵌套分类可用 `|`。
- **Conflicts:** 不提供编辑、可见、保存、复制或 Blueprint 访问语义。
- **Prefer instead:** C++-only 成员用代码结构表达分组。

- **功能描述：** 指定属性的类别，使用 | 运算符定义嵌套类目。
- **元数据类型：** strings=“a|b|c”
- **引擎模块：** DetailsPanel, Editor
- **作用机制：** 在Meta中加入[Category](../../../Meta/DetailsPanel/Category.md)
- **常用程度：★★★★★**

指定属性的类别，使用 | 运算符定义嵌套类目。

## 行为

`Category` 会写入属性 metadata，用于 Details Panel、Blueprint 节点面板或相关编辑器 UI 的分类显示。`Category = "A|B|C"` 表示嵌套分类路径。

对暴露到编辑器或 Blueprint 的属性，显式 `Category` 通常是推荐写法；对于 Engine 模块里的编辑器/Blueprint 暴露属性，UHT 会要求更严格的显式分类。

## UE5.8 审计结论

状态：`verified_UE5.8`

在 `D:/github/GitWorkspace/Hello/Source/Insider/Property/MyProperty_Test.h` 中，Details Panel 与 Blueprint 相关样例均使用了 `Category`，包括简单分类如 `Category = Edit`、`Category = Blueprint`，以及其他 Insider 样例中的嵌套分类。

`bat/build-hello.bat` 已在 UE5.8 下成功编译 `HelloEditor Win64 Development`，说明这些样例可通过 UE5.8 UHT/编译流程。

UE5.8 源码 `C:/Program Files/Epic Games/UE_5.8/Engine/Source/Programs/Shared/EpicGames.UHT/Specifiers/UhtDefaultSpecifiers.cs` 中，UHT 解析逻辑把 `Category` 写入 metadata。`Types/UhtProperty.cs` 会对暴露到编辑器或 Blueprint 但缺少 Category 的 Engine 模块属性进行诊断；如果设置了 Category 但属性没有通过 `EditAnywhere`、`BlueprintReadWrite`、`VisibleAnywhere`、`BlueprintReadOnly`、`BlueprintAssignable` 或 `BlueprintCallable` 等暴露，UHT 会发出警告。

## 示例代码：

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyProperty_Test :public UObject
{
	//PropertyFlags:	CPF_Edit | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_SimpleDisplay | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
	UPROPERTY(EditAnywhere, SimpleDisplay, Category = Display)
		int32 MyInt_SimpleDisplay = 123;

	//PropertyFlags:	CPF_Edit | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_AdvancedDisplay | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = Display)
		int32 MyInt_AdvancedDisplay = 123;
public:
	//PropertyFlags:	CPF_Edit | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
	UPROPERTY(EditAnywhere, Category = Edit)
		int32 MyInt_EditAnywhere = 123;

	//PropertyFlags:	CPF_Edit | CPF_ZeroConstructor | CPF_DisableEditOnInstance | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
	UPROPERTY(EditDefaultsOnly, Category = Edit)
		int32 MyInt_EditDefaultsOnly = 123;

	//PropertyFlags:	CPF_Edit | CPF_ZeroConstructor | CPF_DisableEditOnTemplate | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
	UPROPERTY(EditInstanceOnly, Category = Edit)
		int32 MyInt_EditInstanceOnly = 123;

	//PropertyFlags:	CPF_Edit | CPF_ZeroConstructor | CPF_EditConst | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
	UPROPERTY(VisibleAnywhere, Category = Edit)
		int32 MyInt_VisibleAnywhere = 123;

	//PropertyFlags:	CPF_Edit | CPF_ZeroConstructor | CPF_DisableEditOnInstance | CPF_EditConst | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
	UPROPERTY(VisibleDefaultsOnly, Category = Edit)
		int32 MyInt_VisibleDefaultsOnly = 123;
}
```

## 示例效果：


## 原理：

比较简单，把值设置到meta里的Category，之后读取出来使用。

## 常见误用

- 不要把 `Category` 当作权限控制；它只影响分类显示。
- 对 Blueprint 或 Details Panel 暴露的属性，建议显式写 `Category`，避免默认分类不稳定或 UHT 诊断。
- 嵌套分类使用 `|`，例如 `Category = "Inventory|Weapon"`。
- 如果属性没有暴露到编辑器或 Blueprint，单独设置 `Category` 通常没有意义，还可能触发警告。
