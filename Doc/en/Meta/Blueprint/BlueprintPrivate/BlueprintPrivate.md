# BlueprintPrivate

- **Function Description:** Specifies that this function or property is accessible exclusively within the class it is defined, akin to the private access specifier in C++. It cannot be accessed from other Blueprint classes.
- **Usage Locations:** UFUNCTION, UPROPERTY
- **Metadata Type:** bool
- **Related Item:** [BlueprintProtected](../BlueprintProtected/BlueprintProtected.md)
- **Commonality:** ★★

Access permissions for the function can be configured in the function details panel:

![Untitled](Untitled.png)

As a result, "BlueprintPrivate=true" is added to the function

Properties can also be configured in the details panel:

![Untitled](Untitled%201.png)

As a result, "BlueprintPrivate=true" is added to the property