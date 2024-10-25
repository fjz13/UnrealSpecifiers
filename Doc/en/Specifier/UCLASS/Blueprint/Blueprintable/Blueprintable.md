# Blueprintable

- **Function description:** Can be inherited within blueprints, and its latent effects can also serve as variable types
- **Engine module:** Blueprint
- **Metadata type:** bool
- **Mechanism of action:** [IsBlueprintBase](../../../../Meta/Blueprint/IsBlueprintBase.md) and [BlueprintType](../../../../Meta/Blueprint/BlueprintType.md) are added to Meta
- **Associated items:** [NotBlueprintable](../NotBlueprintable.md)
- **Commonality:** ★★★★★

Can be inherited in blueprints, and its latent effects can also be used as variable types.

When the Blueprintable tag is set, the metadata for BlueprintType = true is implicitly set. Conversely, when the tag is removed, the BlueprintType = true metadata is also removed.

## Sample Code:

```cpp
/*
(BlueprintType = true, IncludePath = Class/MyClass_Blueprintable.h, IsBlueprintBase = true, ModuleRelativePath = Class/MyClass_Blueprintable.h)
*/
UCLASS(Blueprintable)
class INSIDER_API UMyClass_Blueprintable :public UObject
{
	GENERATED_BODY()
};

/*
(IncludePath = Class/MyClass_Blueprintable.h, IsBlueprintBase = false, ModuleRelativePath = Class/MyClass_Blueprintable.h)
*/
UCLASS(NotBlueprintable)
class INSIDER_API UMyClass_NotBlueprintable :public UObject
{
	GENERATED_BODY()
};

/*
(BlueprintType = true, IncludePath = Class/MyClass_Blueprintable.h, IsBlueprintBase = true, ModuleRelativePath = Class/MyClass_Blueprintable.h)
*/
UCLASS(Blueprintable)
class INSIDER_API UMyClass_NotBlueprintable_To_Blueprintable :public UMyClass_NotBlueprintable
{
	GENERATED_BODY()
};

/*
(IncludePath = Class/MyClass_Blueprintable.h, IsBlueprintBase = false, ModuleRelativePath = Class/MyClass_Blueprintable.h)
*/
UCLASS(NotBlueprintable)
class INSIDER_API UMyClass_Blueprintable_To_NotBlueprintable :public UMyClass_Blueprintable
{
	GENERATED_BODY()
};
```

## Example Effect:

Only items marked as Blueprintable can be chosen as base classes.

![Untitled](Untitled.png)

However, the rule for whether it can be used as a variable still depends on the Blueprint tag of the parent class. Therefore, the following three can be used as variables.

UMyClass_Blueprintable_To_NotBlueprintable can be used as a variable because its parent class, UMyClass_Blueprintable, can be used as a variable, thus inheriting the property.

![Untitled](Untitled%201.png)

## Principle:

The MD_IsBlueprintBase attribute is used to determine whether subclasses can be created

```cpp
bool FKismetEditorUtilities::CanCreateBlueprintOfClass(const UClass* Class)
{
	bool bCanCreateBlueprint = false;

	if (Class)
	{
		bool bAllowDerivedBlueprints = false;
		GConfig->GetBool(TEXT("Kismet"), TEXT("AllowDerivedBlueprints"), /*out*/ bAllowDerivedBlueprints, GEngineIni);

		bCanCreateBlueprint = !Class->HasAnyClassFlags(CLASS_Deprecated)
			&& !Class->HasAnyClassFlags(CLASS_NewerVersionExists)
			&& (!Class->ClassGeneratedBy || (bAllowDerivedBlueprints && !IsClassABlueprintSkeleton(Class)));

		const bool bIsBPGC = (Cast<UBlueprintGeneratedClass>(Class) != nullptr);

		const bool bIsValidClass = Class->GetBoolMetaDataHierarchical(FBlueprintMetadata::MD_IsBlueprintBase)
			|| (Class == UObject::StaticClass())
			|| (Class == USceneComponent::StaticClass() || Class == UActorComponent::StaticClass())
			|| bIsBPGC;  // BPs are always considered inheritable

		bCanCreateBlueprint &= bIsValidClass;
	}

	return bCanCreateBlueprint;
}
```