# BlueprintType

- **Function description:** Can serve as a variable type
- **Engine module:** Blueprint
- **Metadata type:** bool
- **Action mechanism:** Add [BlueprintType](../../../../Meta/Blueprint/BlueprintType.md) to Meta
- **Associated items:** [NotBlueprintType](../NotBlueprintType.md)
- **Commonly used:** ★★★★★

Can serve as a variable type.

The key is to set the two metadata, BlueprintType and NotBlueprintType.

## Sample Code:

```cpp

/*
(BlueprintType = true, IncludePath = Class/MyClass_BlueprintType.h, ModuleRelativePath = Class/MyClass_BlueprintType.h)
 */
UCLASS(BlueprintType)
class INSIDER_API UMyClass_BlueprintType :public UObject
{
	GENERATED_BODY()
};

/*
(IncludePath = Class/MyClass_BlueprintType.h, ModuleRelativePath = Class/MyClass_BlueprintType.h)
*/
UCLASS()
class INSIDER_API UMyClass_BlueprintType_Child :public UMyClass_BlueprintType
{
	GENERATED_BODY()
};

/*
(IncludePath = Class/MyClass_BlueprintType.h, ModuleRelativePath = Class/MyClass_BlueprintType.h, NotBlueprintType = true)
*/
UCLASS(NotBlueprintType)
class INSIDER_API UMyClass_NotBlueprintType :public UObject
{
	GENERATED_BODY()
};

/*
(BlueprintType = true, IncludePath = Class/MyClass_BlueprintType.h, ModuleRelativePath = Class/MyClass_BlueprintType.h)
*/
UCLASS(BlueprintType)
class INSIDER_API UMyClass_NotBlueprintType_To_BlueprintType:public UMyClass_NotBlueprintType
{
	GENERATED_BODY()
};

/*
(IncludePath = Class/MyClass_BlueprintType.h, ModuleRelativePath = Class/MyClass_BlueprintType.h, NotBlueprintType = true)
*/
UCLASS(NotBlueprintType)
class INSIDER_API UMyClass_BlueprintType_To_NotBlueprintType:public UMyClass_BlueprintType
{
	GENERATED_BODY()
};

```

## Example Results:

Only items with BlueprintType set to true can be used as variables

![Untitled](Untitled.png)

## Principle:

The three overloaded functions in UEdGraphSchema_K2::IsAllowableBlueprintVariableType each determine whether UEnum, UClass, and UScriptStruct can be used as variables.

```cpp
用UEdGraphSchema_K2::IsAllowableBlueprintVariableType来判断

const UClass* ParentClass = InClass;
while(ParentClass)
{
	// Climb up the class hierarchy and look for "BlueprintType" and "NotBlueprintType" to see if this class is allowed.
	if(ParentClass->GetBoolMetaData(FBlueprintMetadata::MD_AllowableBlueprintVariableType)
		|| ParentClass->HasMetaData(FBlueprintMetadata::MD_BlueprintSpawnableComponent))
	{
		return true;
	}
	else if(ParentClass->GetBoolMetaData(FBlueprintMetadata::MD_NotAllowableBlueprintVariableType))
	{
		return false;
	}
	ParentClass = ParentClass->GetSuperClass();
}
```