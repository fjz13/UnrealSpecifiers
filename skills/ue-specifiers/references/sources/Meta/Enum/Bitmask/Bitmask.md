---
title: "Bitmask"
id: "meta.Bitmask"
kind: "meta"
symbol: "Bitmask"
scope: "Bitmask"
category: "Enum"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "设定一个属性采用Bitmask赋值"
usage: "UPROPERTY"
---

# Bitmask

- **功能描述：** 设定一个属性采用Bitmask赋值
- **使用位置：** UPROPERTY
- **引擎模块：** Enum Property
- **元数据类型：** bool
- **限制类型：** 用来表示枚举值的int32
- **关联项：** [BitmaskEnum](../BitmaskEnum/BitmaskEnum.md)
- **常用程度：** ★★★★★

这个标记和enum身上的定义并没有一定的关系，因此可以单独定义。

```cpp
UENUM(BlueprintType)
enum class EMyEnum_Normal:uint8
{
	First,
	Second,
	Third,
};

UENUM(BlueprintType,Flags)
enum class EMyEnum_Flags:uint8
{
	First,
	Second,
	Third,
};

UENUM(BlueprintType,Meta = (Bitflags))
enum class EMyEnum_BitFlags:uint8
{
	First,
	Second,
	Third,
};

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyActor_EnumBitFlags_Test:public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Meta = (Bitmask, BitmaskEnum = "EMyEnum_Normal"))
	int32 MyNormal;

	UPROPERTY(EditAnywhere, Meta = (Bitmask, BitmaskEnum = "EMyEnum_Flags"))
	int32 MyFlags;

	UPROPERTY(EditAnywhere, Meta = (Bitmask, BitmaskEnum = "EMyEnum_BitFlags"))
	int32 MyBitFlags;
};
```

都是可以在蓝图中用标记来定义


可以用BitmaskEnum进一步提供枚举值
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。
