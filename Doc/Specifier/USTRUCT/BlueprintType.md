# BlueprintType

Type: bool
Feature: Blueprint
Description: 将此结构体作为可以在蓝图中被用于变量的类型公开。可称为变量类型
Status: Done

和UCLASS里的一样，可以允许这个结构在蓝图中声明变量

```cpp
USTRUCT(BlueprintType)
struct INSIDER_API FMyStruct_BlueprintType
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float Score;
};

USTRUCT()
struct INSIDER_API FMyStruct_NoBlueprintType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float Score;
};
```

测试蓝图：

![Untitled](BlueprintType/Untitled.png)