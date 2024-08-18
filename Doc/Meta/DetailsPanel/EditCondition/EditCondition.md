# EditCondition

功能描述: 给一个属性指定另外一个属性或者表达式来作为是否可编辑的条件。
使用位置: UPROPERTY
Feature: Editor
引擎模块: DetailsPanel
元数据类型: string="abc"
Example: EditCondition="BooleanPropertyName”
Status: Done
Sub-item: EditConditionHides (EditConditionHides.md), InlineEditConditionToggle (InlineEditConditionToggle.md), HideEditConditionToggle (HideEditConditionToggle.md)
常用程度: 5

给一个属性指定另外一个属性或者表达式来作为是否可编辑的条件。

- 表达式里引用的属性必须得是同一个类或结构范围内的。

测试代码：

```cpp
UCLASS(BlueprintType)
class INSIDER_API UMyProperty_EditCondition_Test :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)
	bool MyBool;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)
	int32 MyInt = 123;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property, meta = (EditCondition = "MyBool"))
	int32 MyInt_EditCondition = 123;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property, meta = (EditCondition = "!MyBool"))
	int32 MyInt_EditCondition_Not = 123;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PropertyExpression)
	int32 MyFirstInt = 123;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PropertyExpression)
	int32 MySecondInt = 123;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PropertyExpression, meta = (EditCondition = "(MyFirstInt+MySecondInt)==500"))
	int32 MyInt_EditConditionExpression = 123;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PropertyExpression, meta = (EditCondition = "!((MyFirstInt+MySecondInt)==500)"))
	int32 MyInt_EditConditionExpression_Not = 123;
};
```

测试结果：

- 可以通过bool单个属性来控制其他属性是否可以编辑
- 也可以通过一个表达式引入更复杂的计算机制来决定是否来编辑。

![EditCondition.gif](EditCondition/EditCondition.gif)

原理：

在细节面板的属性初始化的时候，会判断该属性EditCondition设置，如果有值，会创建FEditConditionParser来解析表达式然后求值。

```cpp
void FPropertyNode::InitNode(const FPropertyNodeInitParams& InitParams)
{
	const FString& EditConditionString = MyProperty->GetMetaData(TEXT("EditCondition"));

	// see if the property supports some kind of edit condition and this isn't the "parent" property of a static array
	const bool bIsStaticArrayParent = MyProperty->ArrayDim > 1 && GetArrayIndex() != -1;
	if (!EditConditionString.IsEmpty() && !bIsStaticArrayParent)
	{
		EditConditionExpression = EditConditionParser.Parse(EditConditionString);
		if (EditConditionExpression.IsValid())
		{
			EditConditionContext = MakeShareable(new FEditConditionContext(*this));
		}
	}
		
}
```