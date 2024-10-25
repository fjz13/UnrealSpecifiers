# Blueprintable

- **Function Description:** Can be realized in blueprints
- **Metadata Type:** boolean
- **Engine Module:** Blueprint
- **Action Mechanism:** Include [IsBlueprintBase](../../../../Meta/Blueprint/IsBlueprintBase.md) and [BlueprintType](../../../../Meta/Blueprint/BlueprintType.md) in Meta
- **Associated Items:** [NotBlueprintable](../NotBlueprintable/NotBlueprintable.md)
- **Common Usage:** ★★★★★

Whether it can be realized in blueprints.

## Sample Code:

```cpp
UINTERFACE(Blueprintable,MinimalAPI)
class UMyInterface_Blueprintable:public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class INSIDER_API IMyInterface_Blueprintable
{
	GENERATED_IINTERFACE_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void Func_ImplementableEvent() const;

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void Func_NativeEvent() const;
};

UINTERFACE(NotBlueprintable,MinimalAPI)
class UMyInterface_NotBlueprintable:public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class INSIDER_API IMyInterface_NotBlueprintable
{
	GENERATED_IINTERFACE_BODY()
public:
//Blueprint functions should not be defined either, as they can no longer be realized in blueprints
//UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	//void Func_ImplementableEvent() const;

//	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
//	void Func_NativeEvent() const;
};
```

## Example Effect:

Tested in blueprints and found that UMyInterface_NotBlueprintable cannot be located.

![Untitled](Untitled.png)