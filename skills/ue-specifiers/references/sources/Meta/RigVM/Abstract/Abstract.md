---
title: "Abstract"
id: "meta.Abstract"
kind: "meta"
symbol: "Abstract"
category: "RigVM"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "标识该FRigUnit为抽象类，不用实现Execute"
usage: "USTRUCT"
---

# Abstract

- **功能描述：** 标识该FRigUnit为抽象类，不用实现Execute。
- **使用位置：** USTRUCT
- **引擎模块：** RigVMStruct
- **元数据类型：** bool
- **限制类型：** FRigUnit类型上
- **常用程度：** ★★

标识该FRigUnit为抽象类，不用实现Execute，常常用作别的FRigUnit类的基类使用。

但如果还是实现了Execute，其实也还是可以在蓝图中调用的。
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。

## 测试代码：

```cpp
USTRUCT(meta = (DisplayName = "MyRigAbstract",Abstract))
struct INSIDER_API FRigUnit_MyRigAbstract: public FRigUnit
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (Input))
	float MyFloat_Input = 123.f;

	UPROPERTY(meta = (Output))
	float MyFloat_Output = 123.f;
};
```

## 测试效果：


## 原理：

在一些内部处理的时候，当然会略过这种抽象基类。

```cpp
void FRigVMBlueprintUtils::ForAllRigVMStructs(TFunction<void(UScriptStruct*)> InFunction)
{
	// Run over all unit types
	for(TObjectIterator<UStruct> StructIt; StructIt; ++StructIt)
	{
		if (*StructIt)
		{
			if(StructIt->IsChildOf(FRigVMStruct::StaticStruct()) && !StructIt->HasMetaData(FRigVMStruct::AbstractMetaName))
			{
				if (UScriptStruct* ScriptStruct = Cast<UScriptStruct>(*StructIt))
				{
					InFunction(ScriptStruct);
				}
			}
		}
	}
}
```
