# BlueprintType

- **功能描述：**  允许这个结构在蓝图中声明变量
- **元数据类型：** bool
- **引擎模块：** Blueprint
- **作用机制：** 在Meta中加入[BlueprintType](../../../../Meta/Blueprint/BlueprintType.md)
- **常用程度：★★★★★**

和UCLASS里的一样，可以允许这个结构在蓝图中声明变量

## 示例代码：

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

## 测试蓝图：

![Untitled](Untitled.png)