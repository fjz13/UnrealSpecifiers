# NonTransactional

- **Function Description:** Any modifications made to this attribute will not be incorporated into the editor's Undo/Redo commands.

- **Metadata Type:** bool
- **Engine Module:** Editor
- **Action Mechanism:** Include [CPF_NonTransactional](../../../../Flags/EPropertyFlags/CPF_NonTransactional.md) in PropertyFlags
- **Common Usage:** ★★

Changes to this attribute cannot be reversed using Ctrl+Z or redone using Ctrl+Y within the editor. This applies to Class Defaults in both Actors and Blueprints.

## Test Code:

```jsx
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyProperty_Transaction :public AActor
{
public:
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,NonTransactional,Category = Transaction)
		int32 MyInt_NonTransactional= 123;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = Transaction)
		int32 MyInt_Transactional = 123;
};
```

## Blueprint Performance:

Inputs on MyInt_Transactional can be undone, whereas inputs on MyInt_NonTransactional cannot be undone with Ctrl+Z.

![Untitled](Untitled.png)