---
title: "DetailsOnly"
id: "meta.DetailsOnly"
kind: "meta"
symbol: "DetailsOnly"
category: "RigVM"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定FRigUnit下的该属性只在细节面板中显示"
usage: "UPROPERTY"
---

# DetailsOnly

- **功能描述：** 指定FRigUnit下的该属性只在细节面板中显示。
- **使用位置：** UPROPERTY
- **引擎模块：** RigVMStruct
- **元数据类型：** bool
- **限制类型：** FRigUnit下的属性
- **关联项：** [Input](../Input/Input.md)
- **常用程度：** ★★★

指定FRigUnit下的该属性只在细节面板中显示。
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。

## 测试代码：

```cpp
	UPROPERTY(meta = (Input, DetailsOnly))
	float MyFloat_DetailsOnly = 456.f;
```

## 测试效果：


## 原理：

根据DetailsOnly判断返回是否ShowInDetailsPanelOnly。

```cpp
bool URigVMPin::ShowInDetailsPanelOnly() const
{
#if WITH_EDITOR
	if (GetParentPin() == nullptr)
	{
		if (URigVMUnitNode* UnitNode = Cast<URigVMUnitNode>(GetNode()))
		{
			if (UScriptStruct* ScriptStruct = UnitNode->GetScriptStruct())
			{
				if (FProperty* Property = ScriptStruct->FindPropertyByName(GetFName()))
				{
					if (Property->HasMetaData(FRigVMStruct::DetailsOnlyMetaName))
					{
						return true;
					}
				}
			}
		}
		else if(const URigVMTemplateNode* TemplateNode = Cast<URigVMTemplateNode>(GetNode()))
		{
			if(const FRigVMTemplate* Template = TemplateNode->GetTemplate())
			{
				return !Template->GetArgumentMetaData(GetFName(), FRigVMStruct::DetailsOnlyMetaName).IsEmpty();
			}
		}
	}
#endif
	return false;
}
```
