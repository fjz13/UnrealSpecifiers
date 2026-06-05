---
title: "ShowAsInputPin"
id: "meta.ShowAsInputPin"
kind: "meta"
symbol: "ShowAsInputPin"
category: "Material"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "使得UMaterialExpression里的一些基础类型属性变成材质节点上的引脚"
usage: "UPROPERTY"
---

# ShowAsInputPin

## Decision Summary

- **Use when:** `ShowAsInputPin` metadata 的 `UPROPERTY` 场景需要：使得UMaterialExpression里的一些基础类型属性变成材质节点上的引脚。
- **Do not use when:** 目标声明不属于 `UPROPERTY`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** 目标应属于 material expression 属性；值影响 material editor 中是否作为输入 pin 展示。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 使得UMaterialExpression里的一些基础类型属性变成材质节点上的引脚。
- **使用位置：** UPROPERTY
- **引擎模块：** Material
- **元数据类型：** bool
- **限制类型：** UMaterialExpression里的属性
- **常用程度：** ★★★

使得UMaterialExpression里的一些基础类型属性变成材质节点上的引脚。

- 所谓基础类型，指的是float，FVector这种常用的类型。
- 默认这些基础类型属性是不显示为引脚的。
- ShowAsInputPin 值有两个选项，Primary可以直接显示出来，Advanced需要展开箭头后显示。
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。

## 测试代码：

```cpp

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PinTest)
	float MyFloat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PinTest, meta = (ShowAsInputPin = "Primary"))
	float MyFloat_Primary;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PinTest, meta = (ShowAsInputPin = "Advanced"))
	float MyFloat_Advanced;
```

## 测试结果：

可见MyFloat没有显示在节点上。

MyFloat_Primary显示在节点上。

MyFloat_Advanced需要展开箭头后才显示出来。


## 原理：

遍历UMaterialExpression里的属性，根据含有ShowAsInputPin 的类型来生成引脚。

```cpp
TArray<FProperty*> UMaterialExpression::GetPropertyInputs() const
{
	TArray<FProperty*> PropertyInputs;

	static FName OverridingInputPropertyMetaData(TEXT("OverridingInputProperty"));
	static FName ShowAsInputPinMetaData(TEXT("ShowAsInputPin"));
	for (TFieldIterator<FProperty> InputIt(GetClass(), EFieldIteratorFlags::IncludeSuper, EFieldIteratorFlags::ExcludeDeprecated); InputIt; ++InputIt)
	{
		bool bCreateInput = false;
		FProperty* Property = *InputIt;
		// Don't create an expression input if the property is already associated with one explicitly declared
		bool bOverridingInputProperty = Property->HasMetaData(OverridingInputPropertyMetaData);
		// It needs to have the 'EditAnywhere' specifier
		const bool bEditAnywhere = Property->HasAnyPropertyFlags(CPF_Edit);
		// It needs to be marked with a valid pin category meta data
		const FString ShowAsInputPin = Property->GetMetaData(ShowAsInputPinMetaData);
		const bool bShowAsInputPin = ShowAsInputPin == TEXT("Primary") || ShowAsInputPin == TEXT("Advanced");

		if (!bOverridingInputProperty && bEditAnywhere && bShowAsInputPin)
		{
			// Check if the property type fits within the allowed widget types
			FFieldClass* PropertyClass = Property->GetClass();
			if (PropertyClass == FFloatProperty::StaticClass()
				|| PropertyClass == FDoubleProperty::StaticClass()
				|| PropertyClass == FIntProperty::StaticClass()
				|| PropertyClass == FUInt32Property::StaticClass()
				|| PropertyClass == FByteProperty::StaticClass()
				|| PropertyClass == FBoolProperty::StaticClass()
				)
			{
				bCreateInput = true;
			}
			else if (PropertyClass == FStructProperty::StaticClass())
			{
				FStructProperty* StructProperty = CastField<FStructProperty>(Property);
				UScriptStruct* Struct = StructProperty->Struct;
				if (Struct == TBaseStructure<FLinearColor>::Get()
					|| Struct == TBaseStructure<FVector4>::Get()
					|| Struct == TVariantStructure<FVector4d>::Get()
					|| Struct == TBaseStructure<FVector>::Get()
					|| Struct == TVariantStructure<FVector3f>::Get()
					|| Struct == TBaseStructure<FVector2D>::Get()
					)
				{
					bCreateInput = true;
				}
			}
		}
		if (bCreateInput)
		{
			PropertyInputs.Add(Property);
		}
	}

	return PropertyInputs;
}
```
