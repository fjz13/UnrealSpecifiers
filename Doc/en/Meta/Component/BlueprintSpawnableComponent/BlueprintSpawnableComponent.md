# BlueprintSpawnableComponent

- **Function description:** Allows this component to appear in the component addition panel within an Actor Blueprint.
- **Usage location:** UCLASS
- **Engine module:** Component Property
- **Metadata type:** boolean
- **Restriction type:** Component class
- **Commonly used:** ★★★★

Enables the component to be displayed in the Add Component panel in the Actor Blueprint.

In the blueprint node, the component can be added whether or not the BlueprintSpawnableComponent is present.

## Test Code:

```cpp
UCLASS(Blueprintable, meta = (BlueprintSpawnableComponent))
class INSIDER_API UMyActorComponent_Spawnable : public UActorComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MyFloat;
};

UCLASS(Blueprintable)
class INSIDER_API UMyActorComponent_NotSpawnable : public UActorComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MyFloat;
};
```

## Effect in Blueprint:

As seen, under the Add button on the left side of the Actor, UMyActorComponent_Spawnable can be added, but UMyActorComponent_NotSpawnable is prevented from being added. However, it is also worth noting that both components can be added if using the AddComponent node in the blueprint.

![Untitled](Untitled.png)

![Untitled](Untitled%201.png)

## Principle:

```cpp
bool FKismetEditorUtilities::IsClassABlueprintSpawnableComponent(const UClass* Class)
{
	// @fixme: Cooked packages don't have any metadata (yet; they might become available via the sidecar editor data)
	// However, all uncooked BPs that derive from ActorComponent have the BlueprintSpawnableComponent metadata set on them
	// (see FBlueprintEditorUtils::RecreateClassMetaData), so include any ActorComponent BP that comes from a cooked package
	return (!Class->HasAnyClassFlags(CLASS_Abstract) &&
			Class->IsChildOf<UActorComponent>() &&
			(Class->HasMetaData(FBlueprintMetadata::MD_BlueprintSpawnableComponent) || Class->GetPackage()->bIsCookedForEditor));
}
```