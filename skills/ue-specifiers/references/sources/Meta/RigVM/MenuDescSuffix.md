---
title: "MenuDescSuffix"
id: "meta.MenuDescSuffix"
kind: "meta"
symbol: "MenuDescSuffix"
category: "RigVM"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "标识FRigUnit在蓝图右键菜单项的名字后缀"
usage: "USTRUCT"
---

# MenuDescSuffix

## Decision Summary

- **Use when:** `MenuDescSuffix` metadata 的 `USTRUCT` 场景需要：标识FRigUnit在蓝图右键菜单项的名字后缀。
- **Do not use when:** 目标声明不属于 `USTRUCT`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 标识FRigUnit在蓝图右键菜单项的名字后缀。
- **使用位置：** USTRUCT
- **引擎模块：** RigVMStruct
- **元数据类型：** bool
- **限制类型：** FRigUnit类型上
- **常用程度：** ★★★

标识FRigUnit在蓝图右键菜单项的名字后缀。
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。

## 测试代码：

```cpp
USTRUCT(meta = (DisplayName = "MyRigSuffix", MenuDescSuffix = "(MyVector)"))
struct INSIDER_API FRigUnit_MyRigSuffix: public FRigUnit
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

可见出现了"(MyVector)"的后缀。


## 原理：

得到该数据，然后添加到DisplayName后面。

```cpp
FString CategoryMetadata, DisplayNameMetadata, MenuDescSuffixMetadata;
Struct->GetStringMetaDataHierarchical(FRigVMStruct::CategoryMetaName, &CategoryMetadata);
Struct->GetStringMetaDataHierarchical(FRigVMStruct::DisplayNameMetaName, &DisplayNameMetadata);
Struct->GetStringMetaDataHierarchical(FRigVMStruct::MenuDescSuffixMetaName, &MenuDescSuffixMetadata);

if(DisplayNameMetadata.IsEmpty())
{
	DisplayNameMetadata = Struct->GetDisplayNameText().ToString();
}
if (!MenuDescSuffixMetadata.IsEmpty())
{
	MenuDescSuffixMetadata = TEXT(" ") + MenuDescSuffixMetadata;
}

FText MenuDesc = FText::FromString(DisplayNameMetadata + MenuDescSuffixMetadata);
```
