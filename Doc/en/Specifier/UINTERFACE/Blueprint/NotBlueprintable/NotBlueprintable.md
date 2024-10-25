# NotBlueprintable

- **Function Description:** Specifies that it cannot be implemented in blueprints
- **Metadata Type:** bool
- **Engine Module:** Blueprint
- **Action Mechanism:** Removes [IsBlueprintBase](../../../../Meta/Blueprint/IsBlueprintBase.md) and [BlueprintType](../../../../Meta/Blueprint/BlueprintType.md) from Meta, equivalent to [CannotImplementInterfaceInBlueprint](../../../../Meta/Blueprint/CannotImplementInterfaceInBlueprint.md)
- **Associated Items:** [Blueprintable](../Blueprintable/Blueprintable.md)
- **Common Usage:** ★★★

In the Class Settings under Interface, the interface that cannot be implemented is not found.

![Untitled](Untitled.png)

When is it necessary to employ this marker? Although it cannot be realized within blueprints, it is still feasible to implement it in C++, and reflection can also be utilized to ascertain whether an object has implemented the interface.