---
title: "Within"
id: "UCLASS.Within"
kind: "specifier"
symbol: "Within"
scope: "UCLASS"
category: "Instance"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定对象创建的时候必须依赖于OuterClassName的对象作为Outer"
usage: "UCLASS / Instance"
---

# Within

## Decision Summary

- **Use when:** `Within` specifier 的 `UCLASS / Instance` 场景需要：指定对象创建的时候必须依赖于OuterClassName的对象作为Outer。
- **Do not use when:** 声明宏、目标类型或代码契约不属于 `UCLASS / Instance`。
- **Requires:** specifier 必须放在 UE5.8 UHT 支持的宏和声明位置，并满足正文 caveat。
- **Conflicts:** 不要和同类互斥 specifier 或语义相反的暴露/持久化/网络规则混用。
- **Prefer instead:** 能用更窄暴露范围或更明确 metadata 表达时，优先选择更窄方案。

- **功能描述：**  指定对象创建的时候必须依赖于OuterClassName的对象作为Outer。
- **引擎模块：** Instance
- **元数据类型：** string="abc"
- **作用机制：** 保存在UClass* UClass::ClassWithin=XXX的XXX中
- **常用程度：★★★**

指定对象创建的时候必须依赖于OuterClassName的对象作为Outer。

此类的对象无法在OuterClassName对象的实例之外存在。这意味着，要创建此类的对象，需要提供OuterClassName的一个实例作为其Outer对象。

本类在这种情况一般是用来当做子对象来使用的。

## 示例代码：

```cpp
UCLASS(Within= MyClass_Within_Outer)
class INSIDER_API UMyClass_Within :public UObject
{
	GENERATED_BODY()
};

UCLASS()
class INSIDER_API UMyClass_Within_Outer :public UObject
{
	GENERATED_BODY()
public:
};


```

## 示例结果：

```cpp
//错误！Fatal error: Object MyClass_Within None created in Package instead of MyClass_Within_Outer
UMyClass_Within* obj=NewObject<UMyClass_Within>();

//正确：
UMyClass_Within_Outer* objOuter = NewObject<UMyClass_Within_Outer>();
UMyClass_Within* obj=NewObject<UMyClass_Within>(objOuter);
```

## 原理：

生成的UClass的字段：UClass* ClassWithin会保存这个信息，然后在创建的时候StaticAllocateObject会测试 check(bCreatingCDO || !InOuter || InOuter->IsA(InClass->ClassWithin))。因此需要先创建Within的对象。

```cpp
bool StaticAllocateObjectErrorTests( const UClass* InClass, UObject* InOuter, FName InName, EObjectFlags InFlags)
{
		if ( (InFlags & (RF_ClassDefaultObject|RF_ArchetypeObject)) == 0 )
		{
			if ( InOuter != NULL && !InOuter->IsA(InClass->ClassWithin) )
			{
				UE_LOG(LogUObjectGlobals, Fatal, TEXT("%s"), *FString::Printf( TEXT("Object %s %s created in %s instead of %s"), *InClass->GetName(), *InName.ToString(), *InOuter->GetClass()->GetName(), *InClass->ClassWithin->GetName()) );
				return true;
			}
		}
}
```

在源码里可以搜索到很多Within的用法

UCLASS(Within=Engine, config=Engine, transient)
class ENGINE_API ULocalPlayer

UCLASS(Abstract, DefaultToInstanced, Within=UserWidget)
class UMG_API UUserWidgetExtension : public UObject
{

## 行为

UE5.8 UHT 记录 `ClassWithinIdentifier`，指定 UObject outer 类型约束。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `UhtClassSpecifiers.cs` class specifier branch
  - UE5.8 `UhtClass.cs` class flag/metadata resolution and validation

## 常见误用

把 class specifier 的 metadata/flag 结果和 property/function specifier 混淆；或忽略继承/撤销类 specifier 的相互作用。
