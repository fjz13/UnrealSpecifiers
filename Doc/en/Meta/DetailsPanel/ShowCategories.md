# ShowCategories

- **Function Description:** Display categories
- **Usage Location:** UCLASS
- **Metadata Type:** strings = "a, b, c"
- **Associated Items:** [HideCategories](HideCategories.md)

ShowCategories marked on the class will not be saved to the meta file; it is solely used to override the settings of the base class HideCategories. Therefore, ShowCategories within the meta file is not utilized.

```cpp
//(BlueprintType = true, IncludePath = Class/Display/MyClass_HideCategories.h, IsBlueprintBase = true, ModuleRelativePath = Class/Display/MyClass_HideCategories.h)
UCLASS(Blueprintable, ShowCategories = MyGroup1)
class INSIDER_API UMyClass_ShowCategories :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Property_NotInGroup;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyGroup1)
		int Property_Group1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyGroup2 | MyGroup22")
		int Property_Group222;
};
```