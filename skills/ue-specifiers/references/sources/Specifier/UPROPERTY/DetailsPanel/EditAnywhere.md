---
title: "EditAnywhere"
id: "UPROPERTY.EditAnywhere"
kind: "specifier"
symbol: "EditAnywhere"
scope: "UPROPERTY"
category: "DetailsPanel"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "在默认值和实例的细节面板上均可编辑"
usage: "UPROPERTY / DetailsPanel"
---

# EditAnywhere

## Decision Summary

- **Use when:** 属性需要在类默认值和关卡/蓝图实例上都能被编辑。
- **Do not use when:** 属性只应展示不可编辑，或只允许默认值/实例其中一侧编辑。
- **Requires:** 需要 Blueprint 访问时另加 `BlueprintReadOnly` 或 `BlueprintReadWrite`。
- **Conflicts:** `EditDefaultsOnly`、`EditInstanceOnly`、`VisibleAnywhere`、`VisibleDefaultsOnly`、`VisibleInstanceOnly`。
- **Prefer instead:** 只读展示用 `VisibleAnywhere`；只改默认值用 `EditDefaultsOnly`；只改实例用 `EditInstanceOnly`。

- **功能描述：** 在默认值和实例的细节面板上均可编辑
- **元数据类型：** bool
- **引擎模块：** DetailsPanel, Editor
- **作用机制：** 在PropertyFlags中加入CPF_Edit
- **常用程度：★★★★★**

在默认值和实例的细节面板上均可编辑。

## 行为

`EditAnywhere` 让属性在类默认值和实例的 Details Panel 中都可编辑。它只控制编辑器属性面板的编辑权限，不等价于 Blueprint 可读写，也不自动参与存档、复制或配置系统。

## UE5.8 审计结论

在 UE5.8 UHT 源码 `UhtPropertyMemberSpecifiers.cs` 中，`EditAnywhereSpecifier` 会设置 `EPropertyFlags.Edit`，并通过 `SeenEditSpecifier` 阻止同一属性同时声明多个 edit/visibility specifier。Hello 样例 `Property/MyProperty_Test.h` 中的属性 flags 也对应 `CPF_Edit`。

## 常见误用

- 不要和 `EditDefaultsOnly`、`EditInstanceOnly`、`VisibleAnywhere`、`VisibleDefaultsOnly`、`VisibleInstanceOnly` 同时使用；UE5.8 UHT 会报重复 edit/visibility specifier。
- 需要 Blueprint 访问时另加 `BlueprintReadOnly` 或 `BlueprintReadWrite`。
- 需要只展示不可编辑时用 `VisibleAnywhere`，不是 `EditAnywhere`。

## 示例代码：

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyProperty_Test :public UObject
{
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

	//PropertyFlags:	CPF_Edit | CPF_ZeroConstructor | CPF_DisableEditOnTemplate | CPF_EditConst | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
	UPROPERTY(VisibleInstanceOnly, Category = Edit)
		int32 MyInt_VisibleInstanceOnly = 123;
}
```

## 示例效果：


## 原理：

CPF_Edit在源码里有非常多的使用，决定了很多地方属性是否可以显示和编辑。有兴趣可以自己去搜搜CPF_Edit的使用。
