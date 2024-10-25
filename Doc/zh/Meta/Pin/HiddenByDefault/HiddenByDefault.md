# HiddenByDefault

- **功能描述：** Struct的Make Struct和Break Struct节点中的引脚默认为隐藏状态
- **使用位置：** USTRUCT
- **引擎模块：** Pin
- **元数据类型：** bool
- **常用程度：** ★

## 测试代码：

```cpp
//(BlueprintType = true, HiddenByDefault = , ModuleRelativePath = Struct/MyStruct_HiddenByDefault.h)
USTRUCT(BlueprintType, meta = (HiddenByDefault))
struct INSIDER_API FMyStruct_HiddenByDefault
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MyFloat;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString MyString;
};

USTRUCT(BlueprintType)
struct INSIDER_API FMyStruct_NotHidden
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MyFloat;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString MyString;
};
```

## 蓝图结果：

![Untitled](Untitled.png)

所谓隐藏，指的是在节点的细节面板里需要手动选择某些属性。而不是像默认的一样一开始就全部自动打开。

![Untitled](Untitled%201.png)