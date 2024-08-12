# Keywords

Description: 指定一系列关键字用于在蓝图内右键找到该函数
Usage: UFUNCTION
Feature: Blueprint
Group: Blueprint
Type: string="abc"
Example: KeyWords="A,B C”
Status: Done

Keywords里的单词可以用空格隔开，也可以逗号隔开。这里面的文本是会被进行字符串匹配搜索。

测试代码：

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyFunction_Keywords :public UBlueprintFunctionLibrary
{
public:
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable,meta=(Keywords="This is a SuperFunc,OtherFunc"))
	static void MyFunc_HasKeyworlds();
};
```

蓝图效果：

![Untitled](Keywords/Untitled.png)

原理：

该Keywords的内容，最终会被FEdGraphSchemaAction所应用，用于蓝图内右键菜单的文本搜索。

另外每个K2Node都可以返回一个Keywords。效果应该跟函数上的Keywords一样。

```cpp
FText UEdGraphNode::GetKeywords() const
{
	return GetClass()->GetMetaDataText(TEXT("Keywords"), TEXT("UObjectKeywords"), GetClass()->GetFullGroupName(false));
}
```