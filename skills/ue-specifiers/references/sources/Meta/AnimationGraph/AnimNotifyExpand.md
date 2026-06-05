---
title: "AnimNotifyExpand"
id: "meta.AnimNotifyExpand"
kind: "meta"
symbol: "AnimNotifyExpand"
category: "AnimationGraph"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "使得UAnimNotify或UAnimNotifyState下的属性直接展开到细节面板里"
usage: "UPROPERTY"
---

# AnimNotifyExpand

## Decision Summary

- **Use when:** `AnimNotifyExpand` metadata 的 `UPROPERTY` 场景需要：使得UAnimNotify或UAnimNotifyState下的属性直接展开到细节面板里。
- **Do not use when:** 目标声明不属于 `UPROPERTY`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 使得UAnimNotify或UAnimNotifyState下的属性直接展开到细节面板里。
- **使用位置：** UPROPERTY
- **引擎模块：** AnimationGraph
- **元数据类型：** bool
- **限制类型：** UAnimNotify或UAnimNotifyState子类下的FName属性

使得UAnimNotify或UAnimNotifyState下的属性直接展开到细节面板里。

在源码里也没有找到应用的例子。
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。

## 原理：

看源码，里面写死了只对有限的引擎自带的几个类起效，因此自己的测试代码并不能生效。

这种写法确实不应该这么写死，希望以后改进吧。到时应该就有源码里的例子了。

```cpp

PropertyModule.RegisterCustomClassLayout( "EditorNotifyObject", FOnGetDetailCustomizationInstance::CreateStatic(&FAnimNotifyDetails::MakeInstance));

bool FAnimNotifyDetails::CustomizeProperty(IDetailCategoryBuilder& CategoryBuilder, UObject* Notify, TSharedPtr<IPropertyHandle> Property)
{
	if(Notify && Notify->GetClass() && Property->IsValidHandle())
{
	FString ClassName = Notify->GetClass()->GetName();
	FString PropertyName = Property->GetProperty()->GetName();
	bool bIsBoneName = Property->GetBoolMetaData(TEXT("AnimNotifyBoneName"));

	if(ClassName.Find(TEXT("AnimNotify_PlayParticleEffect")) != INDEX_NONE && PropertyName == TEXT("SocketName"))
	{
		AddBoneNameProperty(CategoryBuilder, Notify, Property);
		return true;
	}
	else if(ClassName.Find(TEXT("AnimNotifyState_TimedParticleEffect")) != INDEX_NONE && PropertyName == TEXT("SocketName"))
	{
		AddBoneNameProperty(CategoryBuilder, Notify, Property);
		return true;
	}
	else if(ClassName.Find(TEXT("AnimNotify_PlaySound")) != INDEX_NONE && PropertyName == TEXT("AttachName"))
	{
		AddBoneNameProperty(CategoryBuilder, Notify, Property);
		return true;
	}
	else if (ClassName.Find(TEXT("_SoundLibrary")) != INDEX_NONE && PropertyName == TEXT("SoundContext"))
	{
		CategoryBuilder.AddProperty(Property);
		FixBoneNamePropertyRecurse(Property);
		return true;
	}
	else if (ClassName.Find(TEXT("AnimNotifyState_Trail")) != INDEX_NONE)
	{
		if(PropertyName == TEXT("FirstSocketName") || PropertyName == TEXT("SecondSocketName"))
		{
			AddBoneNameProperty(CategoryBuilder, Notify, Property);
			return true;
		}
		else if(PropertyName == TEXT("WidthScaleCurve"))
		{
			AddCurveNameProperty(CategoryBuilder, Notify, Property);
			return true;
		}
	}
	else if (bIsBoneName)
	{
		AddBoneNameProperty(CategoryBuilder, Notify, Property);
		return true;
	}
}
}

```
