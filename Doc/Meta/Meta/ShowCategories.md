# ShowCategories

Usage: UCLASS
Feature: Editor
Type: strings="a，b，c"
Description: 显示类别
Example: ShowCategories=(Category1, Category2, ...)
Status: NotUsed
Parent item: HideCategories (HideCategories.md)

在类上面标记的ShowCategories，并不会保存到meta中去，只是用来抹除基类HideCategories的设置。因此meta里的ShowCategories是没有用到的。

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