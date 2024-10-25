# AnimNotifyBoneName

- **Function Description:** Enables the FName attribute under UAnimNotify or UAnimNotifyState to function as BoneName.
- **Usage Location:** UPROPERTY
- **Engine Module:** AnimationGraph
- **Metadata Type:** bool
- **Restriction Type:** FName attribute under UAnimNotify or UAnimNotifyState subclass
- **Commonality:** ★★

Enables the FName attribute under UAnimNotify or UAnimNotifyState to function as BoneName.

In animation notifications, there is often a need to pass a bone name parameter, which cannot be sufficiently customized using standard string parameters. Therefore, marking an FName attribute with AnimNotifyBoneName allows for the creation of a dedicated UI in the corresponding detail panel customization, facilitating easier input of BoneName.

## Example in Source Code:

```cpp
UCLASS(const, hidecategories = Object, collapsecategories, meta = (DisplayName = "Play Niagara Particle Effect"), MinimalAPI)
class UAnimNotify_PlayNiagaraEffect : public UAnimNotify
{
		// SocketName to attach to
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify", meta = (AnimNotifyBoneName = "true"))
	FName SocketName;
}

UCLASS(Blueprintable, meta = (DisplayName = "Timed Niagara Effect"), MinimalAPI)
class UAnimNotifyState_TimedNiagaraEffect : public UAnimNotifyState
{
	// The socket within our mesh component to attach to when we spawn the Niagara component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NiagaraSystem, meta = (ToolTip = "The socket or bone to attach the system to", AnimNotifyBoneName = "true"))
	FName SocketName;
}
```

## Test Code:

```cpp
UCLASS(BlueprintType)
class INSIDER_API UAnimNotify_MyTest:public UAnimNotify
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName MyName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta=(AnimNotifyBoneName="true"))
	FName MyName_Bone;
};

UCLASS(BlueprintType)
class INSIDER_API UAnimNotifyState_MyTest:public UAnimNotifyState
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName MyName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta=(AnimNotifyBoneName="true"))
	FName MyName_Bone;
};
```

## Test Results:

In an animation sequence, animation notifications can be added in two forms: UAnimNotify or UAnimNotifyState. The built-in examples UAnimNotify_PlayNiagaraEffect and UAnimNotifyState_TimedNiagaraEffect in the engine show that the UI for SocketName in the details panel on the right is not a regular string.

Our custom animation notification MyBoneName can achieve the same effect. MyName_Bone, with AnimNotifyBoneName added, differs from the standard MyName.

![Untitled](Untitled.png)

## Principle:

During customization, a special UI is generated based on whether the attributes under AnimNotify have this tag.

```cpp
bool FAnimNotifyDetails::CustomizeProperty(IDetailCategoryBuilder& CategoryBuilder, UObject* Notify, TSharedPtr<IPropertyHandle> Property)
{
	else if (InPropertyHandle->GetBoolMetaData(TEXT("AnimNotifyBoneName")))
	{
		// Convert this property to a bone name property
		AddBoneNameProperty(CategoryBuilder, Notify, InPropertyHandle);
	}

	 if (bIsBoneName)
		{
			AddBoneNameProperty(CategoryBuilder, Notify, Property);
			return true;
		}
}
```