---
title: "RequiredInput"
id: "meta.RequiredInput"
kind: "meta"
symbol: "RequiredInput"
category: "Material"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "在UMaterialExpression中指定FExpressionInput属性是否要求输入，引脚显示白色或灰色"
usage: "UPROPERTY"
---

# RequiredInput

## Decision Summary

- **Use when:** `RequiredInput` metadata 的 `UPROPERTY` 场景需要：在UMaterialExpression中指定FExpressionInput属性是否要求输入，引脚显示白色或灰色。
- **Do not use when:** 目标声明不属于 `UPROPERTY`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** 目标通常是 `UMaterialExpression` 中的 `FExpressionInput` 或相关 material expression 属性。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 在UMaterialExpression中指定FExpressionInput属性是否要求输入，引脚显示白色或灰色。
- **使用位置：** UPROPERTY
- **引擎模块：** Material
- **元数据类型：** bool
- **限制类型：** UMaterialExpression::FExpressionInput
- **关联项：** [OverridingInputProperty](OverridingInputProperty.md)

在UMaterialExpression中指定FExpressionInput属性是否要求输入，引脚显示白色或灰色。

一般都配合OverridingInputProperty使用。

代码和效果参见OverridingInputProperty
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。

## 原理：

```cpp

bool UMaterialExpression::CanEditChange(const FProperty* InProperty) const
{
	bool bIsEditable = Super::CanEditChange(InProperty);
	if (bIsEditable && InProperty != nullptr)
	{
		// Automatically set property as non-editable if it has OverridingInputProperty metadata
		// pointing to an FExpressionInput property which is hooked up as an input.
		//
		// e.g. in the below snippet, meta=(OverridingInputProperty = "A") indicates that ConstA will
		// be overridden by an FExpressionInput property named 'A' if one is connected, and will thereby
		// be set as non-editable.
		//
		//	UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstA' if not specified"))
		//	FExpressionInput A;
		//
		//	UPROPERTY(EditAnywhere, Category = MaterialExpressionAdd, meta = (OverridingInputProperty = "A"))
		//	float ConstA;
		//

		static FName OverridingInputPropertyMetaData(TEXT("OverridingInputProperty"));

		if (InProperty->HasMetaData(OverridingInputPropertyMetaData))
		{
			const FString& OverridingPropertyName = InProperty->GetMetaData(OverridingInputPropertyMetaData);

			FStructProperty* StructProp = FindFProperty<FStructProperty>(GetClass(), *OverridingPropertyName);
			if (ensure(StructProp != nullptr))
			{
				static FName RequiredInputMetaData(TEXT("RequiredInput"));

				// Must be a single FExpressionInput member, not an array, and must be tagged with metadata RequiredInput="false"
				if (ensure(	StructProp->Struct->GetFName() == NAME_ExpressionInput &&
							StructProp->ArrayDim == 1 &&
							StructProp->HasMetaData(RequiredInputMetaData) &&
							!StructProp->GetBoolMetaData(RequiredInputMetaData)))
				{
					const FExpressionInput* Input = StructProp->ContainerPtrToValuePtr<FExpressionInput>(this);

					if (Input->Expression != nullptr && Input->GetTracedInput().Expression != nullptr)
					{
						bIsEditable = false;
					}
				}
			}
		}

		if (bIsEditable)
		{
			// If the property has EditCondition metadata, then whether it's editable depends on the other EditCondition property
			const FString EditConditionPropertyName = InProperty->GetMetaData(TEXT("EditCondition"));
			if (!EditConditionPropertyName.IsEmpty())
			{
				FBoolProperty* EditConditionProperty = FindFProperty<FBoolProperty>(GetClass(), *EditConditionPropertyName);
				{
					bIsEditable = *EditConditionProperty->ContainerPtrToValuePtr<bool>(this);
				}
			}
		}
	}

	return bIsEditable;
}

```
