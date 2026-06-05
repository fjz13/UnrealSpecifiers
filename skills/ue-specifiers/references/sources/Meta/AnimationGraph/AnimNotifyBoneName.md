---
title: "AnimNotifyBoneName"
id: "meta.AnimNotifyBoneName"
kind: "meta"
symbol: "AnimNotifyBoneName"
category: "AnimationGraph"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "使得UAnimNotify或UAnimNotifyState下的FName属性作为BoneName的作用"
usage: "UPROPERTY"
---

# AnimNotifyBoneName

## Decision Summary

- **Use when:** `AnimNotifyBoneName` metadata 的 `UPROPERTY` 场景需要：使得UAnimNotify或UAnimNotifyState下的FName属性作为BoneName的作用。
- **Do not use when:** 目标声明不属于 `UPROPERTY`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 使得UAnimNotify或UAnimNotifyState下的FName属性作为BoneName的作用。
- **使用位置：** UPROPERTY
- **引擎模块：** AnimationGraph
- **元数据类型：** bool
- **限制类型：** UAnimNotify或UAnimNotifyState子类下的FName属性
- **常用程度：** ★★

使得UAnimNotify或UAnimNotifyState下的FName属性作为BoneName的作用。

在动画通知的时候，也常常需要一个传递骨骼名字参数，用普通的字符串参数显然不够定制化。因此给一个FName属性标上AnimNotifyBoneName就可以在配合的细节面板定制化里为它创建专门的更便于填写BoneName的UI。

## 源码中例子：

```cpp
UCLASS(const, hidecategories = Object, collapsecategories, meta = (DisplayName = "Play Niagara Particle Effect"), MinimalAPI)
class UAnimNotify_PlayNiagaraEffect : public UAnimNotify
{
		// SocketName to attach to
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify", meta = (AnimNotifyBoneName = "true"))
	FName SocketName;
}

UCLASS(Blueprintable, meta = (DisplayName = "Timed Niagara Effect"), MinimalAPI)
class UAnimNotifyState_TimedNiagaraEffect : public UAnimNotifyState
{
	// The socket within our mesh component to attach to when we spawn the Niagara component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NiagaraSystem, meta = (ToolTip = "The socket or bone to attach the system to", AnimNotifyBoneName = "true"))
	FName SocketName;
}
```
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。

## 测试代码：

```cpp
UCLASS(BlueprintType)
class INSIDER_API UAnimNotify_MyTest:public UAnimNotify
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName MyName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta=(AnimNotifyBoneName="true"))
	FName MyName_Bone;
};

UCLASS(BlueprintType)
class INSIDER_API UAnimNotifyState_MyTest:public UAnimNotifyState
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName MyName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta=(AnimNotifyBoneName="true"))
	FName MyName_Bone;
};
```

## 测试效果：

在一个动画序列里加上动画通知，可以加两种：UAnimNotify或UAnimNotifyState。首先引擎里的自带例子UAnimNotify_PlayNiagaraEffect 和UAnimNotifyState_TimedNiagaraEffect ，可以看见在右侧的细节面板上的SocketName的UI不是普通的字符串。

我们自己定义的MyBoneName的动画通知，也可以达成同样的效果。MyName_Bone因为加了AnimNotifyBoneName，就和普通的MyName不一样了。


## 原理：

在定制化的时候，根据AnimNotify下的属性是否有这个标记，生成专门的的UI。

```cpp
bool FAnimNotifyDetails::CustomizeProperty(IDetailCategoryBuilder& CategoryBuilder, UObject* Notify, TSharedPtr<IPropertyHandle> Property)
{
	else if (InPropertyHandle->GetBoolMetaData(TEXT("AnimNotifyBoneName")))
	{
		// Convert this property to a bone name property
		AddBoneNameProperty(CategoryBuilder, Notify, InPropertyHandle);
	}

	 if (bIsBoneName)
		{
			AddBoneNameProperty(CategoryBuilder, Notify, Property);
			return true;
		}
}
```
