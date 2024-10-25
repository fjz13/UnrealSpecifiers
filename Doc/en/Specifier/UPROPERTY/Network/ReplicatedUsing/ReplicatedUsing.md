# ReplicatedUsing

- **Function Description:** Defines a notification callback function that executes after an attribute is updated over the network.
- **Metadata Type:** string="abc"
- **Engine Module:** Network
- **Action Mechanism:** Include [CPF_Net](../../../../Flags/EPropertyFlags/CPF_Net.md), [CPF_RepNotify](../../../../Flags/EPropertyFlags/CPF_RepNotify.md) in PropertyFlags
- **Common Usage:** ★★★★★

ReplicatedUsing can accept a function without parameters, or a function with one parameter that carries the old value. Typically, within the OnRep function, actions such as enabling or disabling are handled. For instance, replicating the 'enabled' property will trigger the subsequent logic accordingly.

## Test Code:

```jsx
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyProperty_Network :public AActor
{
public:
	GENERATED_BODY()
protected:
	UFUNCTION()
		void OnRep_MyInt(int32 oldValue);
UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_MyInt)
		int32 MyInt_ReplicatedUsing = 123;
};

void AMyProperty_Network::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMyProperty_Network, MyInt_ReplicatedUsing);
}
```

Functions equivalently to RepNotify within blueprints.

![Untitled](Untitled.png)