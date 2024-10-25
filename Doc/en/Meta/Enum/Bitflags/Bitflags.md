# Bitflags

- **Function Description:** Allows an enumeration to be set with bit flags for assignment, enabling its recognition as a BitMask within blueprints
- **Usage Location:** UENUM
- **Engine Module:** Enum Property
- **Metadata Type:** bool
- **Associated Items:** [UseEnumValuesAsMaskValuesInEditor](../UseEnumValuesAsMaskValuesInEditor/UseEnumValuesAsMaskValuesInEditor.md)
- **Commonality:** ★★★★★

Frequently used in conjunction with bitmask on UPROPERTY.

Please pay attention to the distinction between this and UENUM(flags), which influences how string output functions work in C++.

This indicates that the enumeration supports bit flags, allowing it to be selected in blueprints.

```cpp
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

//Example in Source Code:
UENUM(Meta = (Bitflags))
enum class EColorBits
{
ECB_Red,
ECB_Green,
ECB_Blue
};
UPROPERTY(EditAnywhere, Meta = (Bitmask, BitmaskEnum = "EColorBits"))
int32 ColorFlags;
```

As shown in the figure below: EMyEnum_Flags will not be listed in the options. EMyEnum_BitFlags, however, can be included.

![Untitled](Untitled.png)

If UPROPERTY(bitmask) is not used in conjunction, only single-item selection will be available in blueprints

![Untitled1](Untitled1.png)