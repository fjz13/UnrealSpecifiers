---
title: "EnumValueDisplayNameOverrides"
id: "meta.EnumValueDisplayNameOverrides"
kind: "meta"
symbol: "EnumValueDisplayNameOverrides"
scope: "EnumValueDisplayNameOverrides"
category: "Enum"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "改变枚举属性值上的显示名字"
usage: "UPROPERTY"
---

# EnumValueDisplayNameOverrides

- **功能描述：** 改变枚举属性值上的显示名字
- **使用位置：** UPROPERTY
- **引擎模块：** Enum Property
- **元数据类型：** string="abc"
- **关联项：** [ValidEnumValues](ValidEnumValues.md)
- **常用程度：** ★★

给枚举属性上的枚举值进行一些改名，可以改变多个，按照“A=B;C=D”的格式列出即可。收集到的信息是TMap<FName, FText>映射，因此要同时提供原枚举值名称和新的显示名称配对。
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。

## 测试代码：

```cpp
UENUM(BlueprintType)
enum class EMyPropertyTestEnum : uint8
{
	First,
	Second,
	Third,
	Forth,
	Fifth,
};

UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EnumValueDisplayNameOverrides = "First=Cat;Second=Dog"))
EMyPropertyTestEnum MyEnumWithDisplayNameOverrides;
```

## 蓝图效果：

可见实际上改变了First、Second的显示名字。


原理代码见ValidEnumValues上的代码
