# MustBeLevelActor

- **Usage Location:** UPROPERTY
- **Engine Module:** Object Property
- **Metadata Type:** bool

Indicates that this must be an Actor within the scene, as opposed to a LevelScriptActor.

The trigger occurs when the currently selected Actor is being highlighted with the arrow cursor.

## Found in the Source Code:

```cpp
if (FObjectPropertyBase* ObjectProperty = CastField<FObjectPropertyBase>(Property))
{
	ObjectClass = ObjectProperty->PropertyClass;
	bMustBeLevelActor = ObjectProperty->GetOwnerProperty()->GetBoolMetaData(TEXT("MustBeLevelActor"));
	RequiredInterface = ObjectProperty->GetOwnerProperty()->GetClassMetaData(TEXT("MustImplement"));
}
```