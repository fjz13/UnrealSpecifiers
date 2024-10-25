# PrioritizeCategories

- **Function description:** Display the specified attribute directory at the forefront of the details panel.
- **Engine module:** Category
- **Metadata type:** strings = (abc, "d|e", "x|y|z")
- **Action mechanism:** Add [PrioritizeCategories](../../../../Meta/DetailsPanel/PrioritizeCategories.md) in Meta
- **Commonly used:** ★★★

Display the specified attribute directory at the forefront of the details panel.

## Sample Code:

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

## Sample Code:

Property_Group333 is now at the top.

![Untitled](Untitled.png)

## Example Results:

exist UClass::GetPrioritizeCategories ( TArray<FString> & OutPrioritizedCategories ) to get the priority directory. The principle is to put them in SortedCategories in the specified order, so the attribute directory will be created first.

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