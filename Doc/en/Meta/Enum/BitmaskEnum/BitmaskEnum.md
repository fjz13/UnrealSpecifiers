# BitmaskEnum

- **Function description:** The name of the enumeration used after employing bit flags
- **Usage location:** UPROPERTY
- **Metadata type:** string="abc"
- **Restricted type:** An int32 used to represent enum values
- **Associated items:** [Bitmask](../Bitmask/Bitmask.md)
- **Commonly used:** ★★★★★

If the BitmaskEnum is not tagged, the tagged name value cannot be provided

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyActor_EnumBitFlags_Test:public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Meta = (Bitmask))
	int32 MyNormalWithoutEnum;
};
```

If the BitmaskEnum is not tagged, the tagged name value cannot be provided

![Untitled](Untitled.png)