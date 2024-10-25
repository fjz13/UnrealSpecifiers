# DebugTreeLeaf

- **Function Description:** Prevent the BlueprintDebugger from expanding the properties of this class to enhance the debugger's performance in the editor
- **Usage Location:** UCLASS
- **Engine Module:** Debug
- **Metadata Type:** bool
- **Commonliness:** ★

Prevents the BlueprintDebugger from expanding the properties of this class to enhance the debugger's performance in the editor. When a class possesses an excessive number of properties (or has too many properties with recursive nesting), the BlueprintDebugger consumes significant performance resources when displaying the class's property data, leading to editor lag. Therefore, for such classes, we can manually add this flag to halt the further expansion of the property tree, stopping at this point. As the name implies, this class becomes the leaf of the property tree during debugging.

In the source code, only UAnimDataModel utilizes this tag, but it can also be added to our custom classes when they have a large number of properties and we do not wish to debug their data.

## Test Code:

```cpp

UCLASS(BlueprintType, meta = (DebugTreeLeaf))
class INSIDER_API UMyClass_DebugTreeLeaf :public UObject
{
	GENERATED_BODY()
	UMyClass_DebugTreeLeaf();
public:
	UPROPERTY(BlueprintReadWrite)
	TArray<int32> IntArray;
	UPROPERTY(BlueprintReadWrite)
	TMap<int32, FString> IntStringMap;
	UPROPERTY(BlueprintReadWrite)
	TSet<int32> IntSet;
};

```

## Effect in Blueprint:

UMyClass_DebugTreeLeaf object, when used as a class member variable (or otherwise), will behave differently during debugging in the blueprint. Without the DebugTreeLeaf flag, all internal properties are expanded by default when viewing variable attributes with BlueprintDebugger. However, with the DebugTreeLeaf flag added, the recursion is stopped, preventing the expansion of attribute variables.

![Snipaste_2024-02-29_21-17-51](Snipaste_2024-02-29_21-17-51.png)