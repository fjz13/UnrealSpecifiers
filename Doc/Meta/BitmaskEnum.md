# BitmaskEnum

Description: 使用位标记后采用的枚举名字
Usage: UPROPERTY
Feature: Blueprint
Type: string="abc"
LimitedType: 用来表示枚举值的int32
Example: UPROPERTY(EditAnywhere, Meta = (Bitmask, BitmaskEnum = "EColorBits"))
int32 ColorFlags;
Status: Done
Parent item: Bitmask (Bitmask.md)

如果没有标上BitmaskEnum，则无法提供标记的的名称值

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

如果没有标上BitmaskEnum，则无法提供标记的的名称值

![Untitled](BitmaskEnum/Untitled.png)