# BlueprintType

功能描述: 允许这个结构在蓝图中声明变量
元数据类型: bool
引擎模块: Blueprint
MetaOperation: +=
Meta: BlueprintType (../../Meta/Meta/BlueprintType.md)
Status: Done
常用程度: 5

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