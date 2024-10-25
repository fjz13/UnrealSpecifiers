# BlueprintInternalUseOnly

- **Function description:** Indicates that the element is intended for internal use within the blueprint system and is not exposed for direct definition or use at the user level.

- **Usage locations:** UFUNCTION, USTRUCT

- **Engine module:** Blueprint

- **Metadata type:** bool

- **Associated items:**

  Meta: [BlueprintType](BlueprintType.md), [BlueprintInternalUseOnlyHierarchical](BlueprintInternalUseOnlyHierarchical.md)

  UFUNCTION: [BlueprintInternalUseOnly](../../Specifier/UFUNCTION/UHT/BlueprintInternalUseOnly/BlueprintInternalUseOnly.md)

  USTRUCT: [BlueprintInternalUseOnly](../../Specifier/USTRUCT/Blueprint/BlueprintInternalUseOnly/BlueprintInternalUseOnly.md)

- **Commonly used:** ★★★

It can also be applied to USTRUCT, signifying that the structure is not to be used for defining new Blueprint variables but can be exposed and passed as member variables of other classes.

When used on UFUNCTION: This function is an internal implementation detail, utilized for the realization of another function or node, and it is never directly exposed within the Blueprint diagram.