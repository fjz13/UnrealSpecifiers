# Category

功能描述: 在蓝图的右键菜单中为该函数指定类别分组，可以嵌套多级
元数据类型: strings=“a|b|c”
引擎模块: Editor
Example: Category = "TopCategory|SubCategory|Etc”
MetaOperation: =X
Meta: Category (../../Meta/Meta/Category.md)
Status: Done
常用程度: 5

在蓝图的右键菜单中为该函数指定类别分组。

测试代码：

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyFunction_Default :public AActor
{
public:
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = MyCategory)
	void MyFunc_WithCategory(){}
	UFUNCTION(BlueprintCallable)
	void MyFunc_Default(){}
};
```

蓝图中的展示：

![Untitled](Category/Untitled.png)