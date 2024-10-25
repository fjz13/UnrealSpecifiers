# SystemGameplayAttribute

- **Function Description:** Exposes attributes from UAbilitySystemComponent subclasses to the FGameplayAttribute dropdown menu.
- **Usage Location:** UPROPERTY
- **Engine Module:** GAS
- **Metadata Type:** bool
- **Restriction Type:** Attributes within UAbilitySystemComponent subclasses
- **Associated Items:** [HideInDetailsView](../HideInDetailsView/HideInDetailsView.md)
- **Commonality:** ★★★

Expose attributes from UAbilitySystemComponent subclasses to the FGameplayAttribute dropdown menu.

## Source Code Example:

```cpp
UCLASS(ClassGroup=AbilitySystem, hidecategories=(Object,LOD,Lighting,Transform,Sockets,TextureStreaming), editinlinenew, meta=(BlueprintSpawnableComponent))
class GAMEPLAYABILITIES_API UAbilitySystemComponent : public UGameplayTasksComponent, public IGameplayTagAssetInterface, public IAbilitySystemReplicationProxyInterface
{
	/** Internal Attribute that modifies the duration of gameplay effects created by this component */
	UPROPERTY(meta=(SystemGameplayAttribute="true"))
	float OutgoingDuration;

	/** Internal Attribute that modifies the duration of gameplay effects applied to this component */
	UPROPERTY(meta = (SystemGameplayAttribute = "true"))
	float IncomingDuration;
}
```

## Test Code:

```cpp
UCLASS(Blueprintable, BlueprintType)
class UMyAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GAS")
	float MyFloat;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GAS", meta = (SystemGameplayAttribute))
	float MyFloat_System;
};

UCLASS()
class UMyAttributeSetTest : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GAS")
	FGameplayAttribute MyAttribute;
};

```

## Test Results:

"MyFloat_System" is visible and can be exposed in the options list.

![Untitled](Untitled.png)

## Principle:

The principle is based on checking the SystemGameplayAttribute tag on attributes within the GetAllAttributeProperties function.

```cpp
void FGameplayAttribute::GetAllAttributeProperties(TArray<FProperty*>& OutProperties, FString FilterMetaStr, bool UseEditorOnlyData)
{
	// UAbilitySystemComponent can add 'system' attributes
	if (Class->IsChildOf(UAbilitySystemComponent::StaticClass()) && !Class->ClassGeneratedBy)
	{
		for (TFieldIterator<FProperty> PropertyIt(Class, EFieldIteratorFlags::ExcludeSuper); PropertyIt; ++PropertyIt)
		{
			FProperty* Property = *PropertyIt;


			// SystemAttributes have to be explicitly tagged
			if (Property->HasMetaData(TEXT("SystemGameplayAttribute")) == false)
			{
				continue;
			}
			OutProperties.Add(Property);
		}
	}
}
```