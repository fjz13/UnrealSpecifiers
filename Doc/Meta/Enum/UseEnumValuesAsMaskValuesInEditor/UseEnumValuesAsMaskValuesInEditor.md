# UseEnumValuesAsMaskValuesInEditor

- **功能描述：** 指定枚举值已经是位移后的值，而不是位标记的索引下标。
- **使用位置：** UENUM
- **元数据类型：** bool
- **关联项：** [Bitflags](../Bitflags/Bitflags.md)
- **常用程度：** ★★

指定在编辑器里的枚举值直接就是位标记的最终值，而不是标记位。但是注意在C++里的定义是一样的形式：

```cpp
UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EMotionExtractor_MotionType : uint8
{
	None				= 0 UMETA(Hidden),
	Translation			= 1 << 0,
	Rotation			= 1 << 1,
	Scale				= 1 << 2,
	TranslationSpeed	= 1 << 3,
	RotationSpeed		= 1 << 4,
};

UENUM(meta = (Bitflags))
enum class EPCGChangeType : uint8
{
	None = 0,
	Cosmetic = 1 << 0,
	Settings = 1 << 1,
	Input = 1 << 2,
	Edge = 1 << 3,
	Node = 1 << 4,
	Structural = 1 << 5
};
```

## 测试的代码：

```cpp
UENUM(BlueprintType,Meta = (Bitflags))
enum class EMyEnum_BitFlags:uint8
{
	First,//0
	Second,//1
	Third,//2
};

UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EMyEnum_BitFlagsInEditor:uint8
{
	First,//0
	Second,//1
	Third,//2
};
```

## 测试的蓝图1：

![Untitled_a](Untitled_a.png)

## 测试的蓝图2：

![Untitled_b](Untitled_b.png)

因此可以看出前者是1<<2+1<<2，而后者是1|2，因此后者是直接把枚举值作为已经位移后的值
