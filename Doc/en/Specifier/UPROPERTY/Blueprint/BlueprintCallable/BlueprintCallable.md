# BlueprintCallable

- **Function Description:** This multicast delegate can be invoked within blueprints

- **Metadata Type:** bool
- **Engine Module:** Blueprint
- **Restriction Type:** Multicast Delegates
- **Action Mechanism:** Include [CPF_BlueprintCallable](../../../../Flags/EPropertyFlags/CPF_BlueprintCallable.md) in PropertyFlags
- **Common Usage:** ★★★

This multicast delegate can be invoked in blueprints.

## Sample Code:

```cpp
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMyDynamicMulticastDelegate_One, int32, Value);

UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, BlueprintCallable)
	FMyDynamicMulticastDelegate_One MyMulticastDelegateAssignAndCall;

UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintCallable)
	FMyDynamicMulticastDelegate_One MyMulticastDelegateCall;

UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable)
	FMyDynamicMulticastDelegate_One MyMulticastDelegateAssign;

UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FMyDynamicMulticastDelegate_One MyMulticastDelegate;
```

## Example Effect:

![Untitled](Untitled.png)

Please note that BlueprintAssignable and BlueprintCallable can only be used with multicast delegates

```cpp
DECLARE_DYNAMIC_DELEGATE_OneParam(FMyDynamicSinglecastDelegate_One, int32, Value);

//Compilation Error: 'BlueprintCallable' is only allowed on a property when it is a multicast delegate
UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintCallable)
	FMyDynamicSinglecastDelegate_One MyMyDelegate4;

	//Compilation Error: 'BlueprintAssignable' is only allowed on a property when it is a multicast delegate
UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable)
	FMyDynamicSinglecastDelegate_One MyMyDelegate5;
```