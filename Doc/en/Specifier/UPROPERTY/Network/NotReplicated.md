# NotReplicated

- **Function Description:** Skip the copy operation. This applies exclusively to the structure members and parameters within service request functions.

- **Metadata Type:** bool
- **Engine Module:** Network
- **Restriction Type:** Struct Members
- **Action Mechanism:** Include [CPF_RepSkip](../../../Flags/EPropertyFlags/CPF_RepSkip.md) in PropertyFlags
- **Common Usage:** ★★★

Used only within struct members to specify that a certain attribute should not be copied; otherwise, all attributes will be copied by default. This is used to exclude a specific attribute from the structure.

## Sample Code:

```cpp
USTRUCT(BlueprintType)
struct FMyReplicatedStruct
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString MyString_Default;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,NotReplicated)
		FString MyString_NotReplicated;
};

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyProperty_Network :public AActor
{
public:
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
		FMyReplicatedStruct MyStruct_Replicated;
};
```

MyStruct_Replicated will be replicated, but MyString_NotReplicated will not.