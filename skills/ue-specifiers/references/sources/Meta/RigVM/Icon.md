---
title: "Icon"
id: "meta.Icon"
kind: "meta"
symbol: "Icon"
category: "RigVM"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "设定FRigUnit蓝图节点的图标"
usage: "USTRUCT"
---

# Icon

## Decision Summary

- **Use when:** `Icon` metadata 的 `USTRUCT` 场景需要：设定FRigUnit蓝图节点的图标。
- **Do not use when:** 目标声明不属于 `USTRUCT`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 设定FRigUnit蓝图节点的图标。
- **使用位置：** USTRUCT
- **引擎模块：** RigVMStruct
- **元数据类型：** string="abc"
- **限制类型：** FRigUnit
- **常用程度：** ★★

设定FRigUnit蓝图节点的图标。

根据源码中的注释得知，Icon的格式是“StyleSetName|StyleName|SmallStyleName|StatusOverlayStyleName”，最后两项是可选的，可参考FSlateIcon的更多介绍。
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。

## 测试代码：

```cpp
USTRUCT(meta = (DisplayName = "MyRigIcon",Icon="EditorStyle|GraphEditor.Macro.ForEach_16x"))
struct INSIDER_API FRigUnit_MyRigIcon: public FRigUnit
{
	GENERATED_BODY()

	RIGVM_METHOD()
		virtual void Execute() override;
public:
	UPROPERTY(meta = (Input))
	float MyFloat_Input = 123.f;

	UPROPERTY(meta = (Output))
	float MyFloat_Output = 123.f;
};
```

## 测试效果：

可见加了Icon之后，左上角图标变成了其他，不是默认的f函数目标。


## 原理：

```cpp
FSlateIcon URigVMEdGraphNode::GetIconAndTint(FLinearColor& OutColor) const
{

		if(MetadataScriptStruct && MetadataScriptStruct->HasMetaDataHierarchical(FRigVMStruct::IconMetaName))
		{
			FString IconPath;
			const int32 NumOfIconPathNames = 4;

			FName IconPathNames[NumOfIconPathNames] = {
				NAME_None, // StyleSetName
				NAME_None, // StyleName
				NAME_None, // SmallStyleName
				NAME_None  // StatusOverlayStyleName
			};

			// icon path format: StyleSetName|StyleName|SmallStyleName|StatusOverlayStyleName
			// the last two names are optional, see FSlateIcon() for reference
			MetadataScriptStruct->GetStringMetaDataHierarchical(FRigVMStruct::IconMetaName, &IconPath);
			return FSlateIcon(IconPathNames[0], IconPathNames[1], IconPathNames[2], IconPathNames[3]);
		}
}
```
