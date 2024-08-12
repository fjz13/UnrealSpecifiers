# HiddenByDefault

Usage: USTRUCT
Feature: Blueprint
Type: bool
Description: Struct的Make Struct和Break Struct节点中的引脚默认为隐藏状态
Status: Done
Group: PIn

测试代码：

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

蓝图结果：

![Untitled](HiddenByDefault/Untitled.png)

所谓隐藏，指的是在节点的细节面板里需要手动选择某些属性。而不是像默认的一样一开始就全部自动打开。

![Untitled](HiddenByDefault/Untitled%201.png)