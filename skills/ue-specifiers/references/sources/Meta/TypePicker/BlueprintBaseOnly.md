---
title: "BlueprintBaseOnly"
id: "meta.BlueprintBaseOnly"
kind: "meta"
symbol: "BlueprintBaseOnly"
category: "TypePicker"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "用于类属性，指定是否只接受可创建蓝图子类的基类"
usage: "UPROPERTY"
---

# BlueprintBaseOnly

## Decision Summary

- **Use when:** `BlueprintBaseOnly` metadata 的 `UPROPERTY` 场景需要：用于类属性，指定是否只接受可创建蓝图子类的基类。
- **Do not use when:** 目标声明不属于 `UPROPERTY`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 用于类属性，指定是否只接受可创建蓝图子类的基类
- **使用位置：** UPROPERTY
- **引擎模块：** TypePicker
- **元数据类型：** bool
- **限制类型：** TSubClassOf, FSoftClassPath，UClass*
- **常用程度：** ★★

这个限定在只想要可当作蓝图基类的类时会比较有用。
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。

## 测试代码：

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyCommonObject :public UObject
{
	GENERATED_BODY()
};

UCLASS(BlueprintType)
class INSIDER_API UMyCommonObjectChild :public UMyCommonObject
{
	GENERATED_BODY()
};

UCLASS(BlueprintType, NotBlueprintable)
class INSIDER_API UMyCommonObjectChild_NotBlueprintable :public UMyCommonObject
{
	GENERATED_BODY()
public:
};

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlueprintBaseOnlyTest")
	TSubclassOf<UMyCommonObject> MyClass_NotBlueprintBaseOnly;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlueprintBaseOnlyTest", meta = (BlueprintBaseOnly))
	TSubclassOf<UMyCommonObject> MyClass_BlueprintBaseOnly;
```

## 测试效果：

加了BlueprintBaseOnly的限定后，UMyCommonObjectChild_NotBlueprintable 这个类因为NotBlueprintable就不能被选择了。


## 原理：

如果bBlueprintBaseOnly 则需要进一步判断CanCreateBlueprintOfClass，后者判断一个类是否可以创建蓝图子类。

通常情况下，如果一个C++类，没有定义Blueprintable，则无法创建蓝图子类，则不会被该属性选择到。

本身是蓝图类的都是可以再创建蓝图子类的。

```cpp
bool FPropertyHandleBase::GeneratePossibleValues(TArray<FString>& OutOptionStrings, TArray< FText >& OutToolTips, TArray<bool>& OutRestrictedItems, TArray<FText>* OutDisplayNames)
{
	 if( Property->IsA(FClassProperty::StaticClass()) || Property->IsA(FSoftClassProperty::StaticClass()) )
	{
		UClass* MetaClass = Property->IsA(FClassProperty::StaticClass())
			? CastFieldChecked<FClassProperty>(Property)->MetaClass
			: CastFieldChecked<FSoftClassProperty>(Property)->MetaClass;

		FString NoneStr( TEXT("None") );
		OutOptionStrings.Add( NoneStr );
		if (OutDisplayNames)
		{
			OutDisplayNames->Add(FText::FromString(NoneStr));
		}

		const bool bAllowAbstract = Property->GetOwnerProperty()->HasMetaData(TEXT("AllowAbstract"));
		const bool bBlueprintBaseOnly = Property->GetOwnerProperty()->HasMetaData(TEXT("BlueprintBaseOnly"));
		const bool bAllowOnlyPlaceable = Property->GetOwnerProperty()->HasMetaData(TEXT("OnlyPlaceable"));
		UClass* InterfaceThatMustBeImplemented = Property->GetOwnerProperty()->GetClassMetaData(TEXT("MustImplement"));

		if (!bAllowOnlyPlaceable || MetaClass->IsChildOf<AActor>())
		{
			for (TObjectIterator<UClass> It; It; ++It)
			{
				if (It->IsChildOf(MetaClass)
					&& PropertyEditorHelpers::IsEditInlineClassAllowed(*It, bAllowAbstract)
					&& (!bBlueprintBaseOnly || FKismetEditorUtilities::CanCreateBlueprintOfClass(*It))
					&& (!InterfaceThatMustBeImplemented || It->ImplementsInterface(InterfaceThatMustBeImplemented))
					&& (!bAllowOnlyPlaceable || !It->HasAnyClassFlags(CLASS_Abstract | CLASS_NotPlaceable)))
				{
					OutOptionStrings.Add(It->GetName());
					if (OutDisplayNames)
					{
						OutDisplayNames->Add(FText::FromString(It->GetName()));
					}
				}
			}
		}
	}
}
```
