# Interp

- **Function Description:** Specifies that the attribute value can be exposed for editing within the timeline, typically used in standard Timeline or UMG animations.

- **Metadata Type:** bool
- **Engine Module:** Sequencer
- **Action Mechanism:** Includes [CPF_Edit](../../../../Flags/EPropertyFlags/CPF_Edit.md), [CPF_BlueprintVisible](../../../../Flags/EPropertyFlags/CPF_BlueprintVisible.md), [CPF_Interp](../../../../Flags/EPropertyFlags/CPF_Interp.md) in the PropertyFlags
- **Common Usage:** ★★★

The property can be revealed in the timeline, generally for animation editing purposes.

## Example Code:

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyProperty_Interp :public AActor
{
public:
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = Animation)
		FVector MyInterpVector;
};
```

## Example Effect:

It affects the flag on the property

![Untitled](Untitled.png)

Thus, a Track can be added to this property within the Sequencer

![Untitled](Untitled%201.png)