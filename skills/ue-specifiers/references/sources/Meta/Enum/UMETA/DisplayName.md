---
title: "DisplayName"
id: "meta.Enum.UMETA.DisplayName"
kind: "meta"
symbol: "DisplayName"
scope: "UMETA"
category: "Enum"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "改变枚举值的显示名称"
usage: "UENUM::UMETA"
---

# DisplayName

- **功能描述：** 改变枚举值的显示名称
- **使用位置：** UENUM::UMETA
- **引擎模块：** Enum Property
- **元数据类型：** string="abc"
- **常用程度：** ★★★★★

改变枚举值的显示名称

## 示例代码：

```cpp
/*
[enum 602d0d4e680 EMyEnum_HasDisplayName	Enum->Field->Object	/Script/Insider.EMyEnum_HasDisplayName]
(BlueprintType = true, First.DisplayName = Dog, First.Name = EMyEnum_HasDisplayName::First, IsBlueprintBase = true, ModuleRelativePath = Enum/MyEnum_Test.h, Second.DisplayName = Cat, Second.Name = EMyEnum_HasDisplayName::Second, Third.DisplayName = Pig, Third.Name = EMyEnum_HasDisplayName::Third)
	ObjectFlags:	RF_Public | RF_Transient
	Outer:	Package /Script/Insider
	EnumFlags:	None
	EnumDisplayNameFn:	0
	CppType:	EMyEnum_HasDisplayName
	CppForm:	EnumClass
{
	First = 0,
	Second = 1,
	Third = 2,
	EMyEnum_MAX = 3
};
*/
UENUM(Blueprintable)
enum class EMyEnum_HasDisplayName :uint8
{
	First UMETA(DisplayName="Dog"),
	Second UMETA(DisplayName="Cat"),
	Third UMETA(DisplayName="Pig"),
};

UCLASS(BlueprintType)
class INSIDER_API UMyEnum_Test :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	EMyEnum_HasDisplayName MyEnum_HasDisplayName;
}
```

## 示例效果：

可见改变了名称。


## 行为

UE5.8 UHT 同样用 `DisplayName` metadata 支持 enum/UMETA 显示名；生成代码和显示文本查询会读取 metadata。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `UhtDefaultSpecifiers.cs` `DisplayName` metadata writer
  - UE5.8 enum metadata/codegen display-name path

## 常见误用

以为它改变枚举值标识符；或依赖显示名做序列化/逻辑比较。
