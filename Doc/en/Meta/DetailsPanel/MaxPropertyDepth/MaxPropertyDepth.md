# MaxPropertyDepth

- **Function Description:** Specifies the depth of levels to expand an object or structure within the Details Panel.
- **Usage Location:** UPROPERTY
- **Engine Module:** DetailsPanel
- **Metadata Type:** int32
- **Restriction Type:** Object or structure property
- **Commonliness:** ★

Specifies the depth of levels at which the object or structure is expanded in the Details Panel.

- By default, there is no limit, allowing for expansion recursively down to the deepest nested fields.
- If an object has sub-objects that also have sub-objects, this recursive expansion can go many levels deep, and we may wish to limit the depth to prevent excessive expansion. Thus, we can specify a depth limit.
- A value of -1 indicates no limit, 0 means no expansion at all, and >0 denotes the number of layers to be restricted.
- No examples were found in the source code, but this feature is functional.

## Test Code:

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

## Test Results:

![Untitled](Untitled.png)

## Principle:

When constructing child nodes for each FPropertyNode, the current MaxChildDepthAllowed is checked. If the limit is exceeded, construction does not proceed further.

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