# UseEnumValuesAsMaskValuesInEditor

- **Function description:** Indicates that the enumeration values are already shifted values, rather than the index subscripts of bit flags.
- **Use location:** UENUM
- **Metadata type:** bool
- **Related items:** [Bitflags](../Bitflags/Bitflags.md)
- **Frequency of use:** ★★

Specifies that the enumeration values used in the editor are the final bit flag values, not the bits themselves. However, note that the definition in C++ retains the same format:

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

## Testing Code:

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

## Test Blueprint 1:

![Untitled_a](Untitled_a.png)

## Test Blueprint 2:

![Untitled_b](Untitled_b.png)

Thus, it can be observed that the former is 1<<2 + 1<<2, whereas the latter is simply 1|2, indicating that the latter treats the enumeration value as the already shifted value