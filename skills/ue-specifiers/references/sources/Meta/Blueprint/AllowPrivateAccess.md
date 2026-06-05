---
title: "AllowPrivateAccess"
id: "meta.AllowPrivateAccess"
kind: "meta"
symbol: "AllowPrivateAccess"
category: "Blueprint"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "允许一个在C++中private的属性，可以在蓝图中访问"
usage: "UPROPERTY"
---

# AllowPrivateAccess

## Decision Summary

- **Use when:** C++ 属性保持 `private`，但确实需要 Blueprint 读取或编辑暴露。
- **Do not use when:** 只是为了绕过封装，或属性不需要 Blueprint 访问。
- **Requires:** 通常与 `BlueprintReadOnly`/`BlueprintReadWrite` 等 Blueprint 暴露 specifier 搭配。
- **Conflicts:** 不改变 C++ 可见性，也不替代 getter/setter 设计。
- **Prefer instead:** 需要写入校验时保持属性私有并暴露受控函数。

- **功能描述：** 允许一个在C++中private的属性，可以在蓝图中访问。
- **使用位置：** UPROPERTY
- **元数据类型：** bool
- **关联项：** [BlueprintProtected](BlueprintProtected.md)
- **常用程度：** ★★★★★

允许一个在C++中private的属性，可以在蓝图中访问。

AllowPrivateAccess的意义是允许这个属性在C++是private的，不允许C++子类访问，但又允许其暴露到蓝图中访问。

## 测试代码：

```cpp
public:
	//CPF_BlueprintVisible | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
	UPROPERTY(BlueprintReadWrite)
	int32 MyNativeInt_NativePublic;
private:
	//CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPrivate
	//error : BlueprintReadWrite should not be used on private members
	UPROPERTY()
	int32 MyNativeInt_NativePrivate;

	//(AllowPrivateAccess = TRUE, Category = MyFunction_Access, ModuleRelativePath = Function/MyFunction_Access.h)
	//CPF_BlueprintVisible | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPrivate
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 MyNativeInt_NativePrivate_AllowPrivateAccess;
```

在MyNativeInt_NativePrivate上如果尝试加上BlueprintReadWrite或BlueprintReadOnly都会触发UHT编译报错。

## 蓝图里的效果：

默认情况下MyNativeInt_NativePrivate_AllowPrivateAccess在蓝图里的访问权限和MyNativeInt_NativePublic一致。

如果读者想要修改改属性在蓝图中的访问权限，则可以配合加上BlueprintProtected和BlueprintPrivate。


## 原理：

UHT在识别属性的BlueprintReadWrite或BlueprintReadOnly标识符的时候，会同时检测是否有AllowPrivateAccess，没有的话会触发报错。

因此AllowPrivateAccess的意义其实只是在阻止UHT的报错，这层检测报错过了之后，属性上的BlueprintReadWrite或BlueprintReadOnly就会被识别并发挥作用，从而可以在蓝图中访问。

```cpp
	private static void BlueprintReadWriteSpecifier(UhtSpecifierContext specifierContext)
	{
			bool allowPrivateAccess = context.MetaData.TryGetValue(UhtNames.AllowPrivateAccess, out string? privateAccessMD) && !privateAccessMD.Equals("false", StringComparison.OrdinalIgnoreCase);
			if (specifierContext.AccessSpecifier == UhtAccessSpecifier.Private && !allowPrivateAccess)
			{
				context.MessageSite.LogError("BlueprintReadWrite should not be used on private members");
			}
	}

	private static void BlueprintReadOnlySpecifier(UhtSpecifierContext specifierContext)
	{
			bool allowPrivateAccess = context.MetaData.TryGetValue(UhtNames.AllowPrivateAccess, out string? privateAccessMD) && !privateAccessMD.Equals("false", StringComparison.OrdinalIgnoreCase);
			if (specifierContext.AccessSpecifier == UhtAccessSpecifier.Private && !allowPrivateAccess)
			{
				context.MessageSite.LogError("BlueprintReadOnly should not be used on private members");
			}
	}

```

## 行为

UE5.8 UHT 在 `BlueprintReadWrite`/`BlueprintReadOnly` 检查 private member 时读取 `AllowPrivateAccess`，且值不是 `false` 时允许通过。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `UhtPropertyMemberSpecifiers.cs` private Blueprint exposure 检查

## 常见误用

把 private 暴露当成默认推荐；或写 `AllowPrivateAccess=false` 后还期待绕过 private 检查。
