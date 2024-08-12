# HideCategories

Description: 列出应在虚幻编辑器“属性（Property）”窗口中对于此类的对象隐藏的一个或多个类别。要隐藏未使用类别声明的属性，请使用声明变量的类的名称。此说明符会传播到子类。
Feature: DetailsPanel
Type: strings=(abc，"d|e"，"x|y|z")
Example: HideCategories=(Category1, Category2, ...)
Status: Done
Sub-item: ShowCategories (ShowCategories.md)

在类的ClassDefaults属性面板里隐藏某些Category的属性。注意，要先在类里定义属性然后设置它的Category。HideCategories的信息会被UHT分析，并保存到UClass的元数据里去。HideCategories的信息可以被子类继承下来。

```cpp
UCLASS(Blueprintable, hideCategories = MyGroup1)
class INSIDER_API UMyClass_HideCategories :public UObject
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
class INSIDER_API UMyClass_HideCategoriesChild :public UMyClass_ShowCategories
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

FEditorCategoryUtils::GetClassHideCategories
```

注意这里，单独的MyGroup2和MyGroup3也都没有显示。所以判断的标准只要目录符合某个目录名字匹配就行。

![Untitled](HideCategories/Untitled.png)