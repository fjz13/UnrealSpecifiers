# PrioritizeCategories

- **功能描述：** 把指定的属性目录优先显示在细节面板的前面。
- **引擎模块：**Category
- **元数据类型：**strings=(abc，"d|e"，"x|y|z")
- **作用机制：**在Meta中增加[PrioritizeCategories](../../../../Meta/DetailsPanel/PrioritizeCategories.md)
- **常用程度：★★★**

把指定的属性目录优先显示在细节面板的前面。

## 示例代码：

```cpp
UCLASS(Blueprintable, PrioritizeCategories= ("MyGroup3|MyGroup33|MyGroup333","MyGroup1"))
class INSIDER_API UMyClass_PrioritizeCategories :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Property_NotInGroup;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyGroup1")
		int Property_Group1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyGroup2|MyGroup22")
		int Property_Group22;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyGroup3|MyGroup33|MyGroup333")
		int Property_Group333;
};
```

## 示例结果：

可见Property_Group333排到了最前面。

![Untitled](Untitled.png)

## 原理：

在UClass::GetPrioritizeCategories(TArray<FString>& OutPrioritizedCategories)中获取优先级目录。原理是按照指定的顺序放到SortedCategories里，所以就会被首先创建出属性目录来。

```cpp
TArray<FString> ClassPrioritizeCategories;
Class->GetPrioritizeCategories(ClassPrioritizeCategories);
for (const FString& ClassPrioritizeCategory : ClassPrioritizeCategories)
{
	FName PrioritizeCategoryName = FName(ClassPrioritizeCategory);
	SortedCategories.AddUnique(PrioritizeCategoryName);
	PrioritizeCategories.AddUnique(PrioritizeCategoryName);
}

```