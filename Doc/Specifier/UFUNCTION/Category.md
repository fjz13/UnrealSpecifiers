# Category

Type: strings=“a|b|c”
Feature: Editor
Description: 右键蓝图节点中为函数指定类别，可以嵌套多级
Example: Category = "TopCategory|SubCategory|Etc”
MetaOperation: =X
Meta: Category (../../Meta/Meta/Category.md)
Status: Done

右键蓝图节点中为函数指定类别

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