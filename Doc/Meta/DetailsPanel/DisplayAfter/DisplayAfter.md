# DisplayAfter

功能描述: 使本属性在指定的属性之后显示。
使用位置: UPROPERTY
Feature: Editor
引擎模块: DetailsPanel
元数据类型: string="abc"
Example: DisplayAfter="PropertyName”
Status: Done
常用程度: 3

使本属性在指定的属性之后显示。

- 默认情况下，属性在细节面板中的顺序是依照头文件中的定义顺序。但如果我们想自己调节这个顺序，就可以用该标记。
- 限制条件是这两个属性必须得是在同一个Category下。这也很好理解，Category组织的优先级肯定更大。

测试代码：

```cpp
UCLASS(BlueprintType)
class INSIDER_API UMyProperty_Priority :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AfterTest)
	int32 MyInt = 123;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AfterTest)
	FString MyString;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AfterTest, meta = (DisplayAfter = "MyInt"))
	int32 MyInt_After = 123;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AfterTest2, meta = (DisplayAfter = "MyInt"))
	int32 MyInt_After2 = 123;

};
```

测试效果：

可见MyInt_After直接在Int后显示。

而MyInt_After2 因为在不同的Category下，因此就保留原样。

![Untitled](DisplayAfter/Untitled.png)

原理：

检查该属性如果有DisplayAfter，就把它插入在指定的属性之后。

```cpp
	void PropertyEditorHelpers::OrderPropertiesFromMetadata(TArray<FProperty*>& Properties)
	{
		const FString& DisplayAfterPropertyName = Prop->GetMetaData(NAME_DisplayAfter);
		if (DisplayAfterPropertyName.IsEmpty())
		{
			InsertProperty(OrderedProperties);
		}
		else
		{
			TArray<TPair<FProperty*, int32>>& DisplayAfterProperties = DisplayAfterPropertyMap.FindOrAdd(FName(*DisplayAfterPropertyName));
			InsertProperty(DisplayAfterProperties);
		}
	}
```