# NeedsDeferredDependencyLoading

- **Engine Module:** Blueprint
- **Metadata Type:** bool
- **Function Mechanism:** Add [CLASS_NeedsDeferredDependencyLoading](../../../Flags/EClassFlags/CLASS_NeedsDeferredDependencyLoading.md) to ClassFlags

## Source Code Example:

```cpp
UCLASS(NeedsDeferredDependencyLoading, MinimalAPI)
class UBlueprintGeneratedClass : public UClass, public IBlueprintPropertyGuidProvider
{
}
```

## Principle:

```cpp
if (ClassFlags.HasAnyFlags(EClassFlags.NeedsDeferredDependencyLoading) && !IsChildOf(Session.UClass))
{
	// CLASS_NeedsDeferredDependencyLoading can only be set on classes derived from UClass
	this.LogError($"'NeedsDeferredDependencyLoading' is set on '{SourceName}' but the flag can only be used with classes derived from UClass.");
}
```