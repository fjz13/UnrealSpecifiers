# BlueprintAuthorityOnly

- **Function Description:** Bound exclusively to events with BlueprintAuthorityOnly, ensuring the multicast delegate only responds to events executed on the server side

- **Metadata Type:** boolean
- **Engine Module:** Blueprint, Network
- **Restriction Type:** Multicast Delegates
- **Action Mechanism:** Include [CPF_BlueprintAuthorityOnly](../../../../Flags/EPropertyFlags/CPF_BlueprintAuthorityOnly.md) in the PropertyFlags
- **Common Usage:** ★★★

## Testing Code:

```cpp
UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, BlueprintCallable)
		FMyDynamicMulticastDelegate_One MyMulticastDelegateAssignAndCall;

UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, BlueprintCallable, BlueprintAuthorityOnly)
		FMyDynamicMulticastDelegate_One MyMulticastDelegateAuthorityOnly;
```

## Performance Manifestation in the Blueprint:

![Untitled](Untitled.png)