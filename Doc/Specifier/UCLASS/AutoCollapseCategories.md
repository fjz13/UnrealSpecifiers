# AutoCollapseCategories

Type: strings=(abc，"d|e"，"x|y|z")
Feature: DetailsPanel
Description: AutoCollapseCategories说明符使父类上的 AutoExpandCategories 说明符的列出类别的效果无效。
Example: AutoCollapseCategories=(Category1, Category2, ...)
MetaOperation: +=&-=
Meta: AutoCollapseCategories (../../Meta/Meta/AutoCollapseCategories.md), AutoExpandCategories (../../Meta/Meta/AutoExpandCategories.md)
Status: Done
Parent item: AutoExpandCategories (AutoExpandCategories.md)
Sub-item: DontAutoCollapseCategories (DontAutoCollapseCategories.md)

```cpp
UCLASS(Blueprintable, AutoCollapseCategories = ("MyGroup2|MyGroup22"))
class INSIDER_API UMyClass_AutoCollapseCategories :public UMyClass_AutoExpandCategories
{
	GENERATED_BODY()
public:
};
```

关闭了Group22的展开，但是444的展开依然继承了

![Untitled](AutoCollapseCategories/Untitled.png)