---
title: "Deprecated"
id: "meta.RigVM.Deprecated"
kind: "meta"
symbol: "Deprecated"
category: "RigVM"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "标识该FRigUnit为弃用状态，不在蓝图右键菜单中显示"
usage: "USTRUCT"
---

# Deprecated

## Decision Summary

- **Use when:** `Deprecated` metadata 的 `USTRUCT` 场景需要：标识该FRigUnit为弃用状态，不在蓝图右键菜单中显示。
- **Do not use when:** 目标声明不属于 `USTRUCT`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 标识该FRigUnit为弃用状态，不在蓝图右键菜单中显示。
- **使用位置：** USTRUCT
- **引擎模块：** RigVMStruct
- **元数据类型：** bool
- **限制类型：** FRigUnit类型上
- **常用程度：** ★★

标识该FRigUnit为弃用状态，不在蓝图右键菜单中显示。

但如果之前已经在蓝图中使用了，则还是可以继续使用。

注意这个时候要相应的实现GetUpgradeInfo()，否则会报错。
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。

## 测试代码：

```cpp
USTRUCT(meta = (DisplayName = "MyRigDeprecated",Deprecated))
struct INSIDER_API FRigUnit_MyRigDeprecated : public FRigUnit
{
	GENERATED_BODY()

	RIGVM_METHOD()
	virtual void Execute() override;

	RIGVM_METHOD()
	virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;
public:
	UPROPERTY(meta = (Input))
	float MyFloat_Input = 123.f;

	UPROPERTY(meta = (Output))
	float MyFloat_Output = 123.f;
};
```

## 测试效果：


## 原理：

在构建菜单项的时候略过Deprecated的节点。

```cpp
void FRigVMEditorModule::GetTypeActions(URigVMBlueprint* RigVMBlueprint, FBlueprintActionDatabaseRegistrar& ActionRegistrar)
{
		// Add all rig units
	for(const FRigVMFunction& Function : Registry.GetFunctions())
	{
			// skip deprecated units
		if(Function.Struct->HasMetaData(FRigVMStruct::DeprecatedMetaName))
		{
			continue;
		}
	}
}
```
