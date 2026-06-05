---
title: "MaterialControlFlow"
id: "meta.MaterialControlFlow"
kind: "meta"
symbol: "MaterialControlFlow"
category: "Material"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "标识该UMaterialExpression为一个控制流节点，当前在材质蓝图右键菜单中隐藏"
usage: "UCLASS"
---

# MaterialControlFlow

## Decision Summary

- **Use when:** `MaterialControlFlow` metadata 的 `UCLASS` 场景需要：标识该UMaterialExpression为一个控制流节点，当前在材质蓝图右键菜单中隐藏。
- **Do not use when:** 目标声明不属于 `UCLASS`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 标识该UMaterialExpression为一个控制流节点，当前在材质蓝图右键菜单中隐藏。
- **使用位置：** UCLASS
- **引擎模块：** Material
- **元数据类型：** bool
- **限制类型：** UMaterialExpression子类
- **常用程度：** ★

标识该UMaterialExpression为一个控制流节点，当前在材质蓝图右键菜单中隐藏。

一般是在IfThenElse，ForLoop这种节点上，当前引擎实现还未完善，因此该功能禁用。
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。

## 源码例子：

```cpp
UCLASS(collapsecategories, hidecategories=Object, MinimalAPI)
class UMaterialExpressionIf : public UMaterialExpression
{}

UCLASS(collapsecategories, hidecategories = Object, MinimalAPI, meta=(MaterialControlFlow))
class UMaterialExpressionIfThenElse : public UMaterialExpression
{}
```

## 测试效果：

可以找到If节点，但是无法调用IfThenElse节点。


## 原理：

在遍历所有可用FMaterialExpression的时候，如果有MaterialControlFlow则略过。当前引擎下AllowMaterialControlFlow一直未false，未实现。

```cpp

// r.MaterialEnableControlFlow is removed and the feature is forced disabled as how control flow should be
// implemented in the material editor is still under discussion.
inline bool AllowMaterialControlFlow()
{
	return false;
}

void MaterialExpressionClasses::InitMaterialExpressionClasses()
{
		static const auto CVarMaterialEnableNewHLSLGenerator = IConsoleManager::Get().FindTConsoleVariableDataInt(TEXT("r.MaterialEnableNewHLSLGenerator"));
		const bool bEnableControlFlow = AllowMaterialControlFlow();
		const bool bEnableNewHLSLGenerator = CVarMaterialEnableNewHLSLGenerator->GetValueOnAnyThread() != 0;

		for( TObjectIterator<UClass> It ; It ; ++It )
		{
			if( Class->IsChildOf(UMaterialExpression::StaticClass()) )
			{
					// Hide node types related to control flow, unless it's enabled
					if (!bEnableControlFlow && Class->HasMetaData("MaterialControlFlow"))
					{
									continue;
					}

					if (!bEnableNewHLSLGenerator && Class->HasMetaData("MaterialNewHLSLGenerator"))
					{
									continue;
					}

					// Hide node types that are tagged private
					if(Class->HasMetaData(TEXT("Private")))
					{
									continue;
					}
				AllExpressionClasses.Add(MaterialExpression);
			}
		}
}
```
