# Replicated

- **Function Description:** Specifies that this property should be replicated along with the network.

- **Metadata Type:** bool
- **Engine Module:** Network
- **Action Mechanism:** Include [CPF_Net](../../../Flags/EPropertyFlags/CPF_Net.md) in PropertyFlags
- **Common Usage:** ★★★★★

## Sample Code:

Remember to add the GetLifetimeReplicatedProps function accordingly in the cpp code

```jsx
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyProperty_Network :public AActor
{
public:
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyInt_Default = 123;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
		int32 MyInt_Replicated = 123;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
		FMyReplicatedStruct MyStruct_Replicated;
};

void AMyProperty_Network::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMyProperty_Network, MyInt_Replicated);
	DOREPLIFETIME(AMyProperty_Network, MyStruct_Replicated);
}
```

No need to demonstrate the sample effect; this is a fundamental network attribute.