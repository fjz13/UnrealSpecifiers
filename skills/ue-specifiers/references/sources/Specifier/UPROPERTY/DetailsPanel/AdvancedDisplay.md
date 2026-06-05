---
title: "AdvancedDisplay"
id: "UPROPERTY.AdvancedDisplay"
kind: "specifier"
symbol: "AdvancedDisplay"
scope: "UPROPERTY"
category: "DetailsPanel"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "被折叠到高级栏下，要手动打开。一般用在不太常用的属性上面"
usage: "UPROPERTY / DetailsPanel"
---

# AdvancedDisplay

## Decision Summary

- **Use when:** Details Panel 属性是低频高级设置，应默认折叠。
- **Do not use when:** 属性是配置该对象的核心字段。
- **Requires:** 属性已经暴露到 Details Panel。
- **Conflicts:** 不改变属性可见性、可编辑性或 Blueprint 访问。
- **Prefer instead:** 必填或高频属性保持普通显示；真正不该显示用更窄暴露策略。

- **功能描述：** 被折叠到高级栏下，要手动打开。一般用在不太常用的属性上面。
- **元数据类型：** bool
- **引擎模块：** DetailsPanel, Editor
- **作用机制：** 在PropertyFlags中加入CPF_AdvancedDisplay
- **常用程度：★★★★★**

被折叠到高级栏下，要手动打开。一般用在不太常用的属性上面。

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
}
```

## 示例效果：


## 原理：

如果CPF_AdvancedDisplay，bAdvanced =true

```cpp
void FPropertyNode::InitNode(const FPropertyNodeInitParams& InitParams)
{
	// Property is advanced if it is marked advanced or the entire class is advanced and the property not marked as simple
	static const FName Name_AdvancedClassDisplay("AdvancedClassDisplay");
	bool bAdvanced = Property.IsValid() ? ( Property->HasAnyPropertyFlags(CPF_AdvancedDisplay) || ( !Property->HasAnyPropertyFlags( CPF_SimpleDisplay ) && Property->GetOwnerClass() && Property->GetOwnerClass()->GetBoolMetaData(Name_AdvancedClassDisplay) ) ) : false;

}
```

## 行为

在 UE5.8 UHT 中写入 `CPF_AdvancedDisplay`。属性侧 specifier 是 Details/Blueprint 展示折叠标志，不同于 UFUNCTION 的 `meta=(AdvancedDisplay=...)` 参数规则。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `UhtPropertyMemberSpecifiers.cs` 对应 specifier 分支

## 常见误用

把 UPROPERTY `AdvancedDisplay` 写成函数参数列表；或以为它改变序列化/访问权限。
