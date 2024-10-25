# EditConditionHides

- **Function Description:** When an EditCondition already exists, this attribute specifies that it should be hidden if the EditCondition is not met.
- **Usage Location:** UPROPERTY
- **Metadata Type:** bool
- **Associated Item:** [EditCondition](../EditCondition/EditCondition.md)
- **Commonality:** ★★★★★

With an existing EditCondition, this attribute is specified to be hidden if the EditCondition is not satisfied.

## Test Code:

```cpp
UCLASS(BlueprintType)
class INSIDER_API UMyProperty_EditCondition_Test :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)
	bool MyBool;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property, meta = (EditConditionHides, EditCondition = "MyBool"))
	int32 MyInt_EditCondition_Hides = 123;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PropertyExpression)
	int32 MyFirstInt = 123;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PropertyExpression)
	int32 MySecondInt = 123;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PropertyExpression, meta = (EditConditionHides, EditCondition = "(MyFirstInt+MySecondInt)==500"))
	int32 MyInt_EditConditionExpression_Hides = 123;
};
```

## Test Effects:

The figure below clearly shows that two attributes are displayed as the conditions are met.

![EditConditionHides](EditConditionHides.gif)

## Principle:

Effectively, it adds a conditional check for visibility.

```cpp
bool FPropertyNode::IsOnlyVisibleWhenEditConditionMet() const
{
	static const FName Name_EditConditionHides("EditConditionHides");
	if (Property.IsValid() && Property->HasMetaData(Name_EditConditionHides))
	{
		return HasEditCondition();
	}

	return false;
}
```