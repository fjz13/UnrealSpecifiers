---
title: "BlueprintReadOnly"
id: "UPROPERTY.BlueprintReadOnly"
kind: "specifier"
symbol: "BlueprintReadOnly"
scope: "UPROPERTY"
category: "Blueprint"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "此属性可由蓝图读取，但不能被修改"
usage: "UPROPERTY / Blueprint"
---

# BlueprintReadOnly

- **功能描述：** 此属性可由蓝图读取，但不能被修改。
- **元数据类型：** bool
- **引擎模块：** Blueprint
- **作用机制：** 在PropertyFlags中加入CPF_BlueprintVisible, CPF_BlueprintReadOnly
- **常用程度：** ★★★★★

此属性可由蓝图读取，但不能被修改。此说明符与 BlueprintReadWrite 说明符不兼容。

## 行为

`BlueprintReadOnly` 让属性在 Blueprint 中可读取但不可写入。它控制 Blueprint 访问权限，不控制 Details Panel 是否可编辑；编辑器面板仍需要 `EditAnywhere`、`VisibleAnywhere` 等 specifier 单独决定。

## UE5.8 审计结论

在 UE5.8 UHT 源码 `UhtPropertyMemberSpecifiers.cs` 中，`BlueprintReadOnlySpecifier` 会设置 `EPropertyFlags.BlueprintVisible | EPropertyFlags.BlueprintReadOnly`。同一实现会拒绝与 `BlueprintReadWrite` 或 `BlueprintSetter` 冲突，并且 private 成员除非显式 `meta=(AllowPrivateAccess=true)`，否则会报错。

## 常见误用

- 不要把 `BlueprintReadOnly` 当作 Details Panel 只读；面板可见性和编辑权限由 edit/visibility specifier 控制。
- 需要 Blueprint 写入时使用 `BlueprintReadWrite`，不要同时写两者。
- private 属性暴露给 Blueprint 时要确认是否真的需要 `AllowPrivateAccess`，不要把它当成默认写法。

## 示例代码：

```cpp
public:
	//PropertyFlags:	CPF_BlueprintVisible | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
	UPROPERTY(BlueprintReadWrite, Category = Blueprint)
		int32 MyInt_ReadWrite = 123;
	//PropertyFlags:	CPF_BlueprintVisible | CPF_BlueprintReadOnly | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
	UPROPERTY(BlueprintReadOnly, Category = Blueprint)
		int32 MyInt_ReadOnly = 123;
```

## 示例效果：

指定蓝图中只读：

![Untitled](Untitled.png)

## 原理：

有CPF_BlueprintVisible 就可以Get

加上CPF_BlueprintReadOnly 后就不能修改。

```cpp
EPropertyAccessResultFlags PropertyAccessUtil::CanGetPropertyValue(const FProperty* InProp)
{
	if (!InProp->HasAnyPropertyFlags(CPF_Edit | CPF_BlueprintVisible | CPF_BlueprintAssignable))
	{
		return EPropertyAccessResultFlags::PermissionDenied | EPropertyAccessResultFlags::AccessProtected;
	}

	return EPropertyAccessResultFlags::Success;
}

FBlueprintEditorUtils::EPropertyWritableState FBlueprintEditorUtils::IsPropertyWritableInBlueprint(const UBlueprint* Blueprint, const FProperty* Property)
{
	if (Property)
	{
		if (!Property->HasAnyPropertyFlags(CPF_BlueprintVisible))
		{
			return EPropertyWritableState::NotBlueprintVisible;
		}
		if (Property->HasAnyPropertyFlags(CPF_BlueprintReadOnly))
		{
			return EPropertyWritableState::BlueprintReadOnly;
		}
		if (Property->GetBoolMetaData(FBlueprintMetadata::MD_Private))
		{
			const UClass* OwningClass = Property->GetOwnerChecked<UClass>();
			if (OwningClass->ClassGeneratedBy.Get() != Blueprint)
			{
				return EPropertyWritableState::Private;
			}
		}
	}
	return EPropertyWritableState::Writable;
}
```
