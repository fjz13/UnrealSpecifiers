# BlueprintType

- **Functional Description:** Permits the declaration of variables within this structure in Blueprints
- **Metadata Type:** boolean
- **Engine Module:** Blueprint
- **Functionality Mechanism:** Incorporate [BlueprintType](../../../../Meta/Blueprint/BlueprintType.md) into the Meta
- **Common Usage:** ★★★★★

Comparable to UCLASS, this structure enables the declaration of variables in Blueprints

## Sample Code:

```cpp
USTRUCT(BlueprintType)
struct INSIDER_API FMyStruct_BlueprintType
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float Score;
};

USTRUCT()
struct INSIDER_API FMyStruct_NoBlueprintType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float Score;
};
```

## Test Blueprint:

![Untitled](Untitled.png)