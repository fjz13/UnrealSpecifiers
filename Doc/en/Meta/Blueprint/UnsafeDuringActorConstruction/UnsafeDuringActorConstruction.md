# UnsafeDuringActorConstruction

- **Function Description:** Indicates that this function should not be invoked within an Actor's constructor
- **Usage Location:** UFUNCTION
- **Engine Module:** Blueprint
- **Metadata Type:** bool
- **Commonality:** ★★

Signifies that this function is not to be called during the construction of an Actor. Typically, functions related to rendering and physics are prohibited from being called during this phase.

## Test Code:

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyFunction_Unsafe :public UBlueprintFunctionLibrary
{
public:
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	static void MySafeFunction();
	UFUNCTION(BlueprintCallable, meta=(UnsafeDuringActorConstruction = "true"))
	static void MyUnsafeFunction();
};
```

The Meta: UnsafeDuringActorConstruction attribute can also be set in the function's details panel within a Blueprint, achieving the same effect as setting it in C++.

It is observed that the MyUnsafeFunction cannot be invoked within an Actor's constructor, and custom functions within Blueprints will also produce warnings and compilation errors when marked with the UnsafeDuringActorConstruction attribute.

![Untitled](Untitled.png)

## Principle:

In Blueprints, there are clear checks in place for this series of conditions, making them easily identifiable.

```cpp
bool UEdGraphSchema_K2::CanFunctionBeUsedInGraph(const UClass* InClass, const UFunction* InFunction, const UEdGraph* InDestGraph, uint32 InAllowedFunctionTypes, bool bInCalledForEach, FText* OutReason) const
{
const bool bIsUnsafeForConstruction = InFunction->GetBoolMetaData(FBlueprintMetadata::MD_UnsafeForConstructionScripts);
if (bIsUnsafeForConstruction && bIsConstructionScript)
{
	if(OutReason != nullptr)
	{
		*OutReason = LOCTEXT("FunctionUnsafeForConstructionScript", "Function cannot be used in a Construction Script.");
	}

	return false;
}
}
```