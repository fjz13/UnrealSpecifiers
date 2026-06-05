---
title: "MaterialParameterCollectionFunction"
id: "meta.MaterialParameterCollectionFunction"
kind: "meta"
symbol: "MaterialParameterCollectionFunction"
category: "Material"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定该函数是用于操作UMaterialParameterCollection，从而支持ParameterName的提取和验证"
usage: "UFUNCTION"
---

# MaterialParameterCollectionFunction

## Decision Summary

- **Use when:** `MaterialParameterCollectionFunction` metadata 的 `UFUNCTION` 场景需要：指定该函数是用于操作UMaterialParameterCollection，从而支持ParameterName的提取和验证。
- **Do not use when:** 目标声明不属于 `UFUNCTION`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 指定该函数是用于操作UMaterialParameterCollection，从而支持ParameterName的提取和验证
- **使用位置：** UFUNCTION
- **引擎模块：** Material
- **元数据类型：** bool
- **限制类型：** 带有UMaterialParameterCollection参数的函数
- **常用程度：** ★★★

指定该函数是用于操作UMaterialParameterCollection，从而支持ParameterName的提取和验证。
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。

## 测试代码：

```cpp

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyFunction_Material :public UBlueprintFunctionLibrary
{
public:
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject", MaterialParameterCollectionFunction))
	static void MySetScalarParameterValue(UObject* WorldContextObject, UMaterialParameterCollection* Collection, FName ParameterName, float ParameterValue);

	UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
	static void MySetScalarParameterValue_NoError(UObject* WorldContextObject, UMaterialParameterCollection* Collection, FName ParameterName, float ParameterValue);
};
```

## 蓝图中效果：

引擎自带的UKismetMaterialLibrary::SetScalarParameterValue和我们自己手动编写的MySetScalarParameterValue，会触发材质参数集合的蓝图节点验证检测。如果没有指定ParameterName，则会产生编译错误。而没有MaterialParameterCollectionFunction标记的MySetScalarParameterValue_NoError函数版本则只是当作一个普通的函数一样，一是不会自动提取MPC中的Parameters集合来选择，二是没有ParameterName为空的错误验证。


## 原理：

```cpp
UBlueprintFunctionNodeSpawner* UBlueprintFunctionNodeSpawner::Create(UFunction const* const Function, UObject* Outer/* = nullptr*/)
{
	bool const bIsMaterialParamCollectionFunc = Function->HasMetaData(FBlueprintMetadata::MD_MaterialParameterCollectionFunction);
	if (bIsMaterialParamCollectionFunc)
	{
		NodeClass = UK2Node_CallMaterialParameterCollectionFunction::StaticClass();
	}
	else
	{
		NodeClass = UK2Node_CallFunction::StaticClass();
	}
}

TSharedPtr<SGraphNode> FNodeFactory::CreateNodeWidget(UEdGraphNode* InNode)
{
		if (UK2Node_CallMaterialParameterCollectionFunction* CallFunctionNode = Cast<UK2Node_CallMaterialParameterCollectionFunction>(InNode))
		{
			return SNew(SGraphNodeCallParameterCollectionFunction, CallFunctionNode);
		}
}
TSharedPtr<SGraphPin> SGraphNodeCallParameterCollectionFunction::CreatePinWidget(UEdGraphPin* Pin) const
{
	//提取MPC中参数列表等操作
		if (Collection)
		{
			// Populate the ParameterName pin combobox with valid options from the Collection
			const bool bVectorParameters = CallFunctionNode->FunctionReference.GetMemberName().ToString().Contains(TEXT("Vector"));
			Collection->GetParameterNames(NameList, bVectorParameters);
		}
}
```

MaterialParameterCollectionFunction这个标记的，会采用UK2Node_CallMaterialParameterCollectionFunction来验证材质函数的正确书写与否。同时UK2Node_CallMaterialParameterCollectionFunction这个蓝图节点也在引擎内部继续被识别以进一步定制化ParameterName的Pin节点。

引擎源码内采用MaterialParameterCollectionFunction标记的函数只有UKismetMaterialLibrary里的函数。
