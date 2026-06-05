---
title: "CustomWidget"
id: "meta.RigVM.CustomWidget"
kind: "meta"
symbol: "CustomWidget"
category: "RigVM"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定该FRigUnit里的属性要用自定义的控件来编辑"
usage: "UPROPERTY"
---

# CustomWidget

## Decision Summary

- **Use when:** `CustomWidget` metadata 的 `UPROPERTY` 场景需要：指定该FRigUnit里的属性要用自定义的控件来编辑。
- **Do not use when:** 目标声明不属于 `UPROPERTY`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 指定该FRigUnit里的属性要用自定义的控件来编辑。
- **使用位置：** UPROPERTY
- **引擎模块：** RigVMStruct
- **元数据类型：** string="abc"
- **限制类型：** FRigUnit中的属性
- **常用程度：** ★★

指定该FRigUnit里的属性要用自定义的控件来编辑。

CustomWidget的值是在一些选项中选择的，这些自定义控件是已经在引擎中实现的。

可用的列表为：BoneName，ControlName，SpaceName/NullName，CurveName，ElementName，ConnectorName，DrawingName，ShapeName，AnimationChannelName，MetadataName，MetadataTagName。

测试代码里就只用BoneName作为测试展示：

```cpp
USTRUCT(meta = (DisplayName = "MyRigCustomWidget"))
struct INSIDER_API FRigUnit_MyRigCustomWidget : public FRigUnit
{
	GENERATED_BODY()

	RIGVM_METHOD()
		virtual void Execute() override;
public:
	UPROPERTY(meta = (Input))
	FString MyString;

	UPROPERTY(meta = (Input, CustomWidget = "BoneName"))
	FString MyString_Custom;

	UPROPERTY(meta = (Output))
	float MyFloat_Output = 123.f;
};
```
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。

## 测试效果：

可见MyString_Custom的Pin类型变成可选BoneName的列表。


## 原理：

```cpp
TSharedPtr<SGraphPin> FControlRigGraphPanelPinFactory::CreatePin_Internal(UEdGraphPin* InPin) const
{
		if (CustomWidgetName == TEXT("BoneName"))
		{
			return SNew(SRigVMGraphPinNameList, InPin)
				.ModelPin(ModelPin)
				.OnGetNameFromSelection_UObject(RigGraph, &UControlRigGraph::GetSelectedElementsNameList)
				.OnGetNameListContent_UObject(RigGraph, &UControlRigGraph::GetBoneNameList)
				.OnGetSelectedClicked_UObject(RigGraph, &UControlRigGraph::HandleGetSelectedClicked)
				.OnBrowseClicked_UObject(RigGraph, &UControlRigGraph::HandleBrowseClicked);
		}
//等等其他
}
```
