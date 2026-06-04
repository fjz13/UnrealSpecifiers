---
title: "HiddenByDefault"
id: "meta.HiddenByDefault"
kind: "meta"
symbol: "HiddenByDefault"
category: "Pin"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "Struct的Make Struct和Break Struct节点中的引脚默认为隐藏状态"
usage: "USTRUCT"
---

# HiddenByDefault

- **功能描述：** Struct的Make Struct和Break Struct节点中的引脚默认为隐藏状态
- **使用位置：** USTRUCT
- **引擎模块：** Pin
- **元数据类型：** bool
- **常用程度：** ★
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。

## 测试代码：

```cpp
//(BlueprintType = true, HiddenByDefault = , ModuleRelativePath = Struct/MyStruct_HiddenByDefault.h)
USTRUCT(BlueprintType, meta = (HiddenByDefault))
struct INSIDER_API FMyStruct_HiddenByDefault
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MyFloat;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString MyString;
};

USTRUCT(BlueprintType)
struct INSIDER_API FMyStruct_NotHidden
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MyFloat;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString MyString;
};
```

## 蓝图结果：


所谓隐藏，指的是在节点的细节面板里需要手动选择某些属性。而不是像默认的一样一开始就全部自动打开。

