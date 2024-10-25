# DisableSplitPin

- **Function Description:** Disable the split feature of a Struct
- **Usage Location:** USTRUCT
- **Engine Module:** Pin
- **Metadata Type:** bool
- **Commonliness:** ★★

For some Structs, especially structures with only one member variable, sometimes it will look strange if you expand them by default. At this time, I hope to disable this function. But note that you can still manually access member variables through Break in the blueprint. If you don’t want to expose member variable access in the blueprint, you should not add BlueprintReadWrite/BlueprintReadOnly to UPROPERTY

Search the source code for examples like FGameplayTag, FPostProcessSettings, FSlatePostSettings

## Test Code:

```cpp
USTRUCT(BlueprintType, meta = (DisableSplitPin))
struct INSIDER_API FMyStruct_DisableSplitPin
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MyFloat;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString MyString;
};

USTRUCT(BlueprintType)
struct INSIDER_API FMyStruct_WithSplitPin
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MyFloat;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString MyString;
};
```

![Untitled](Untitled.png)

Allowed comparisons

![Untitled](Untitled%201.png)