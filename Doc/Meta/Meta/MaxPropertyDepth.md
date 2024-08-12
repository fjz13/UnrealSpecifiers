# MaxPropertyDepth

Usage: UPROPERTY
Feature: Editor
Type: int32
Description: 指定对象或结构在细节面板里展开的层数。
LimitedType: 对象或结构属性
Status: Done
Group: DetailsPanel

指定对象或结构在细节面板里展开的层数。

- 默认是没有限制的，可以一直递归展开到最深层次字段。
- 如果对象的子对象再有子对象，这样递归很多层级，可能我们会想要限制不想展开太深，因此我们可以指定一个层级限制。
- 取值-1表示没有限制，0表示完全不展开，>0表示限制的层数。
- 源码里没有找到例子，但却是可以工作的。

测试代码：

```cpp
USTRUCT(BlueprintType)
struct INSIDER_API FMyStructDepth1
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 MyInt1 = 123;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString MyString1;
};

USTRUCT(BlueprintType)
struct INSIDER_API FMyStructDepth2
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FMyStructDepth1 MyStruct1;
};

USTRUCT(BlueprintType)
struct INSIDER_API FMyStructDepth3
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FMyStructDepth2 MyStruct2;
};

USTRUCT(BlueprintType)
struct INSIDER_API FMyStructDepth4
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FMyStructDepth3 MyStruct3;
};

UCLASS(BlueprintType)
class INSIDER_API UMyProperty_MaxPropertyDepth :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FMyStructDepth4 MyStruct;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta=(MaxPropertyDepth=2))
	FMyStructDepth4 MyStruct_Depth;
};

```

测试效果：

![Untitled](MaxPropertyDepth/Untitled.png)

原理：

在每个FPropertyNode构建子节点的时候，检查一下当前的MaxChildDepthAllowed ，超过了就不继续往下构建。

```cpp
/** Safety Value representing Depth in the property tree used to stop diabolical topology cases
 * -1 = No limit on children
 *  0 = No more children are allowed.  Do not process child nodes
 *  >0 = A limit has been set by the property and will tick down for successive children
 */
int32 MaxChildDepthAllowed;

void FPropertyNode::InitNode(const FPropertyNodeInitParams& InitParams)
{
	
		//Get the property max child depth
		static const FName Name_MaxPropertyDepth("MaxPropertyDepth");
		if (Property->HasMetaData(Name_MaxPropertyDepth))
		{
			int32 NewMaxChildDepthAllowed = Property->GetIntMetaData(Name_MaxPropertyDepth);
			//Ensure new depth is valid.  Otherwise just let the parent specified value stand
			if (NewMaxChildDepthAllowed > 0)
			{
				//if there is already a limit on the depth allowed, take the minimum of the allowable depths
				if (MaxChildDepthAllowed >= 0)
				{
					MaxChildDepthAllowed = FMath::Min(MaxChildDepthAllowed, NewMaxChildDepthAllowed);
				}
				else
				{
					//no current limit, go ahead and take the new limit
					MaxChildDepthAllowed = NewMaxChildDepthAllowed;
				}
			}
		}
}

void FPropertyNode::RebuildChildren()
{
	if (MaxChildDepthAllowed != 0)
{
	//the case where we don't want init child nodes is when an Item has children that we don't want to display
	//the other option would be to make each node "Read only" under that item.
	//The example is a material assigned to a static mesh.
	if (HasNodeFlags(EPropertyNodeFlags::CanBeExpanded) && (ChildNodes.Num() == 0))
	{
		InitChildNodes();
		if (ExpandedPropertyItemSet.Size() > 0)
		{
			FPropertyNodeUtils::SetExpandedItems(ThisAsSharedRef, ExpandedPropertyItemSet);
		}
	}
}
}
```