# ShowCategories

Type: strings=(abc，"d|e"，"x|y|z")
Feature: DetailsPanel
Description: 使列出的类别的继承自基类的HideCategories说明符无效。
Example: ShowCategories=(Category1, Category2, ...)
MetaOperation: +=
Meta: HideCategories (../../Meta/Meta/HideCategories.md)
Status: Done
Parent item: HideCategories (HideCategories.md)

在类的ClassDefaults属性面板里显示某些Category的属性。ShowCategories会被UHT分析，但不会被保存到UClass的元数据里去。它作用的方式是可以抹去之前基类设置的HideCategories的属性。ShowCategories可以被子类继承下来。

/*
//showCategories=CategoryName or showCategories=(category0, category1, ...)
//showCategories = ("Input|MouseInput", "Input|TouchInput")
//ShowCategories=(Category1, Category2, ...)
*/

```cpp
/*
(BlueprintType = true, HideCategories = MyGroup1, IncludePath = Class/Display/MyClass_ShowCategories.h, IsBlueprintBase = true, ModuleRelativePath = Class/Display/MyClass_ShowCategories.h)
*/
UCLASS(Blueprintable, hideCategories = MyGroup1)
class INSIDER_API UMyClass_ShowCategories :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyGroup1)
		int Property_Group1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyGroup2 | MyGroup3")
		int Property_Group23;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Property_NotInGroup;
};

/*
(BlueprintType = true, HideCategories = MyGroup2 | MyGroup3, IncludePath = Class/Display/MyClass_ShowCategories.h, IsBlueprintBase = true, ModuleRelativePath = Class/Display/MyClass_ShowCategories.h)
*/

UCLASS(Blueprintable, showCategories = MyGroup1, hideCategories = "MyGroup2 | MyGroup3")
class INSIDER_API UMyClass_ShowCategoriesChild :public UMyClass_ShowCategories
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyGroup2")
		int Property_Group2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyGroup3")
		int Property_Group3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyGroup4)
		int Property_Group4;
};

FEditorCategoryUtils::GetClassShowCategories
```

![Untitled](ShowCategories/Untitled.png)