# AutoCollapseCategories

功能描述: AutoCollapseCategories说明符使父类上的 AutoExpandCategories 说明符的列出类别的效果无效。
引擎模块: Category
元数据类型: strings=(abc，"d|e"，"x|y|z")
Example: AutoCollapseCategories=(Category1, Category2, ...)
MetaOperation: +=&-=
Meta: AutoCollapseCategories (../../Meta/Meta/AutoCollapseCategories.md), AutoExpandCategories (../../Meta/Meta/AutoExpandCategories.md)
Status: Done
Parent item: AutoExpandCategories (AutoExpandCategories.md)
Sub-item: DontAutoCollapseCategories (DontAutoCollapseCategories.md)
常用程度: 1

示例代码：

```cpp
UCLASS(Blueprintable, AutoCollapseCategories = ("MyGroup2|MyGroup22"))
class INSIDER_API UMyClass_AutoCollapseCategories :public UMyClass_AutoExpandCategories
{
	GENERATED_BODY()
public:
};
```

示例结果：

关闭了Group22的展开，但是444的展开依然继承了

![Untitled](AutoCollapseCategories/Untitled.png)