# Placeable

- **Function Description:** Indicates that this Actor can be placed within a level.
- **Engine Module:** Scene
- **Metadata Type:** bool
- **Action Mechanism:** Remove [CLASS_NotPlaceable](../../../../Flags/EClassFlags/CLASS_NotPlaceable.md) from ClassFlags
- **Associated Items:** [NotPlaceable](../NotPlaceable/NotPlaceable.md)
- **Common Usage:** ★★★

Indicates that the Actor is placeable in the level.

It is placeable by default, so Placeable is not currently used in the source code.

Subclasses can override this flag using the NotPlaceable specifier, just as AInfo and the like set NotPlaceable themselves.

Indicates that this class can be created in the Editor and can be placed into a level, UI scene, or Blueprint (depending on the class type). This flag is inherited by all subclasses

placeable cannot clear the notplaceable mark of the parent class.

## Example Code:

```cpp
UCLASS(Blueprintable, BlueprintType,placeable)
class INSIDER_API AMyActor_Placeable :public AMyActor_NotPlaceable
{
	GENERATED_BODY()
};
error : The 'placeable' specifier cannot override a 'nonplaceable' base class. Classes are assumed to be placeable by default. Consider whether using the 'abstract' specifier on the base class would work.
```

## Example Effect:

![Untitled](Untitled.png)