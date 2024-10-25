# CollapseCategories

- **Function Description:** Hide all properties with the "Category" attribute in the class's property panel, but this effect is only applied to properties with multiple levels of nested "Category."
- **Engine Module:** Category
- **Metadata Type:** bool
- **Action Mechanism:** Add [CLASS_CollapseCategories](../../../../Flags/EClassFlags/CLASS_CollapseCategories.md) to ClassFlags
- **Associated Items:** [DontCollapseCategories](../DontCollapseCategories.md)
- **Common Usage:** ★★

All properties with "Category" in the class's property panel are hidden, but this applies only to properties with multiple nested "Category."

## Sample Code:

```cpp
/*
ClassFlags: CLASS_MatchedSerializers | CLASS_Native | CLASS_CollapseCategories | CLASS_RequiredAPI | CLASS_TokenStreamAssembled | CLASS_Intrinsic | CLASS_Constructed
*/
UCLASS(Blueprintable, CollapseCategories)
class INSIDER_API UMyClass_CollapseCategories :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Property_NotInGroup;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyGroup1")
		int Property_Group1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyGroup2|MyGroup22")
		int Property_Group22;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyGroup3|MyGroup33|MyGroup333")
		int Property_Group333;
};

/*
ClassFlags: CLASS_MatchedSerializers | CLASS_Native | CLASS_RequiredAPI | CLASS_TokenStreamAssembled | CLASS_Intrinsic | CLASS_Constructed
*/
UCLASS(Blueprintable, dontCollapseCategories)
class INSIDER_API UMyClass_DontCollapseCategories :public UMyClass_CollapseCategories
{
	GENERATED_BODY()
public:
};
```

## Example Effect:

The first is the effect of UMyClass_CollapseCategories, and the second is the effect of UMyClass_DontCollapseCategories, where it is evident that some properties are hidden.

![Untitled](Untitled.png)

## Fundamental Principle:

```cpp
if (Specifier == TEXT("collapseCategories"))
{
	// Class' properties should not be shown categorized in the editor.
	ClassFlags |= CLASS_CollapseCategories;
}
else if (Specifier == TEXT("dontCollapseCategories"))
{
	// Class' properties should be shown categorized in the editor.
	ClassFlags &= ~CLASS_CollapseCategories;
}
```