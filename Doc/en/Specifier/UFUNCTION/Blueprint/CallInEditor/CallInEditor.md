# CallInEditor

- **Function Description:** Can be invoked as a button on the property details panel.

- **Metadata Type:** bool
- **Engine Module:** Editor
- **Functionality Mechanism:** Add [CallInEditor](../../../../Meta/Blueprint/CallInEditor.md) in Meta
- **Common Usage:** ★★★★★

Can be invoked as a button on the property details panel.

The function can be implemented in either an AActor or a UObject subclass, provided there is an associated property details panel.

Note that this is typically within the Editor execution environment. A classic example is the Recapture button in ASkyLight. Functions may sometimes call editor-specific functions. However, care should be taken to avoid mixing them with runtime functions, as this can easily lead to errors.

## Test Code:

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyFunction_Default :public AActor
{
public:
	GENERATED_BODY()
public:
	UFUNCTION(CallInEditor)
	void MyFunc_CallInEditor(){}
};
```

## Blueprint Demonstration:

![Untitled](Untitled.png)