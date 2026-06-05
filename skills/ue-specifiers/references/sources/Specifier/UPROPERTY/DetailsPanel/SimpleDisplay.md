---
title: "SimpleDisplay"
id: "UPROPERTY.SimpleDisplay"
kind: "specifier"
symbol: "SimpleDisplay"
scope: "UPROPERTY"
category: "DetailsPanel"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "在细节面板中直接可见，不折叠到高级中"
usage: "UPROPERTY / DetailsPanel"
---

# SimpleDisplay

## Decision Summary

- **Use when:** `SimpleDisplay` specifier 的 `UPROPERTY / DetailsPanel` 场景需要：在细节面板中直接可见，不折叠到高级中。
- **Do not use when:** 声明宏、目标类型或代码契约不属于 `UPROPERTY / DetailsPanel`。
- **Requires:** specifier 必须放在 UE5.8 UHT 支持的宏和声明位置，并满足正文 caveat。
- **Conflicts:** 不要和同类互斥 specifier 或语义相反的暴露/持久化/网络规则混用。
- **Prefer instead:** 能用更窄暴露范围或更明确 metadata 表达时，优先选择更窄方案。

- **功能描述：** 在细节面板中直接可见，不折叠到高级中。
- **元数据类型：** bool
- **引擎模块：** DetailsPanel, Editor
- **作用机制：** 在PropertyFlags中加入CPF_SimpleDisplay
- **常用程度：** ★★★

在细节面板中直接可见，不折叠到高级中。

默认情况下本身就是不折叠，但可以用来覆盖掉类上的AdvancedClassDisplay的设置。具体可参见AdvancedClassDisplay的代码和效果。

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

如果有CPF_SimpleDisplay，则bAdvanced =false

```cpp
void FPropertyNode::InitNode(const FPropertyNodeInitParams& InitParams)
{
	// Property is advanced if it is marked advanced or the entire class is advanced and the property not marked as simple
	static const FName Name_AdvancedClassDisplay("AdvancedClassDisplay");
	bool bAdvanced = Property.IsValid() ? ( Property->HasAnyPropertyFlags(CPF_AdvancedDisplay) || ( !Property->HasAnyPropertyFlags( CPF_SimpleDisplay ) && Property->GetOwnerClass() && Property->GetOwnerClass()->GetBoolMetaData(Name_AdvancedClassDisplay) ) ) : false;

}
```

## 行为

在 UE5.8 UHT 中写入 `CPF_SimpleDisplay`，用于 Details Panel 展示优先级/折叠分组语义。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `UhtPropertyMemberSpecifiers.cs` 对应 specifier 分支

## 常见误用

以为它改变属性可编辑性；或和 `AdvancedDisplay` 同时表达相反意图。
