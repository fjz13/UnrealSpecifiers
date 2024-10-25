# Bitmask

- **Function Description:** Assign an attribute using Bitmask
- **Usage Location:** UPROPERTY
- **Engine Module:** Enum Property
- **Metadata Type:** bool
- **Restricted Type:** int32 used to represent enumeration values
- **Associated Items:** [BitmaskEnum](../BitmaskEnum/BitmaskEnum.md)
- **Commonality:** ★★★★★

This attribute does not have a fixed relationship with the definition of an enum, and therefore can be defined independently.

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

It can be defined in blueprints using this attribute

![Untitled](Untitled.png)

BitmaskEnum can be used to further specify enumeration values