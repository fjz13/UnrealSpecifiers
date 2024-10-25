# BlueprintThreadSafe

- **Function Description:** Used on classes or functions to indicate that all functions within the class are thread-safe.
Thus, they can be invoked in non-game threads, such as animation blueprints.
- **Usage Location:** UCLASS, UFUNCTION
- **Engine Module:** Blueprint
- **Metadata Type:** bool
- **Restriction Type:** Typically, classes are usually of type BlueprintFunctionLibrary
- **Associated Items:** [NotBlueprintThreadSafe](../NotBlueprintThreadSafe.md)
- **Commonly Used:** ★★★

The AimGraph in animation blueprints has thread-safe updates enabled by default. This setting is found in ClassSettings (enabled by default)

![Untitled](Untitled.png)

Refer to the official documentation under **CPU Thread Usage and Performance** for more information

[Graphing in Animation Blueprints](https://docs.unrealengine.com/5.3/en-US/graphing-in-animation-blueprints-in-unreal-engine/#cputhreadusageandperformance)

Therefore, all functions within AimGraph must be thread-safe. Your C++ functions or functions within blueprint libraries need to be manually marked as ThreadSafe; those without the ThreadSafe mark are not considered thread-safe by default.

In blueprints, if ThreadSafe is checked in the function panel, the function's object will be set to bThreadSafe=True, which in turn sets (BlueprintThreadSafe = true) on the compiled BlueprintGeneratedClass

![Untitled](Untitled%201.png)

## Test the Blueprint Function Library:

For the same function, one with ThreadSafe enabled and one without, the function without ThreadSafe will trigger a warning during compilation when used in the AnimGraph of an animation blueprint.

![Untitled](Untitled%202.png)

Test Results:

![Untitled](Untitled%203.png)

## In C++, the C++ test code:

```cpp
//(BlueprintThreadSafe = , IncludePath = Class/Blueprint/MyClass_ThreadSafe.h, ModuleRelativePath = Class/Blueprint/MyClass_ThreadSafe.h)
UCLASS(meta=(BlueprintThreadSafe))
class INSIDER_API UMyBlueprintFunctionLibrary_ThreadSafe : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure)
	static float MyFunc_ClassThreadSafe_Default(float value) {return value+100;}

	//(ModuleRelativePath = Class/Blueprint/MyClass_ThreadSafe.h, NotBlueprintThreadSafe = )
	UFUNCTION(BlueprintPure,meta=(NotBlueprintThreadSafe))
	static float MyFunc_ClassThreadSafe_FuncNotThreadSafe(float value) {return value+100;}
};

UCLASS()
class INSIDER_API UMyBlueprintFunctionLibrary_NoThreadSafe : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	//(BlueprintThreadSafe = , ModuleRelativePath = Class/Blueprint/MyClass_ThreadSafe.h)
	UFUNCTION(BlueprintPure,meta=(BlueprintThreadSafe))
	static float MyFunc_ClassDefault_FuncThreadSafe(float value) {return value+100;}

	//(ModuleRelativePath = Class/Blueprint/MyClass_ThreadSafe.h, NotBlueprintThreadSafe = )
	UFUNCTION(BlueprintPure,meta=(NotBlueprintThreadSafe))
	static float MyFunc_ClassDefault_FuncNotThreadSafe(float value) {return value+100;}
};

UCLASS()
class INSIDER_API UMyBlueprintFunctionLibrary_Default : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure)
	static float MyFunc_ClassDefault_FuncDefault(float value) {return value+100;}
};
```

## Test Results for the Animation Blueprint:

![Untitled](Untitled%204.png)

## Analysis of Principles:

```cpp
bool FBlueprintEditorUtils::HasFunctionBlueprintThreadSafeMetaData(const UFunction* InFunction)
{
	if(InFunction)
	{
		const bool bHasThreadSafeMetaData = InFunction->HasMetaData(FBlueprintMetadata::MD_ThreadSafe);
		const bool bHasNotThreadSafeMetaData = InFunction->HasMetaData(FBlueprintMetadata::MD_NotThreadSafe);
		const bool bClassHasThreadSafeMetaData = InFunction->GetOwnerClass() && InFunction->GetOwnerClass()->HasMetaData(FBlueprintMetadata::MD_ThreadSafe);

		// Native functions need to just have the correct class/function metadata
		const bool bThreadSafeNative = InFunction->HasAnyFunctionFlags(FUNC_Native) && (bHasThreadSafeMetaData || (bClassHasThreadSafeMetaData && !bHasNotThreadSafeMetaData));

		// Script functions get their flag propagated from their entry point, and dont pay heed to class metadata
		const bool bThreadSafeScript = !InFunction->HasAnyFunctionFlags(FUNC_Native) && bHasThreadSafeMetaData;

		return bThreadSafeNative || bThreadSafeScript;
	}

	return false;
}
```

It can be logically deduced that if a UCLASS is marked with BlueprintThreadSafe, its internal functions are thread-safe by default, unless explicitly marked with NotBlueprintThreadSafe to opt out. If a UCLASS is not marked, each UFUNCTION must be manually marked with BlueprintThreadSafe. Both methods are acceptable.

Note that UCLASS(meta=(NotBlueprintThreadSafe)) is not recognized for this purpose and therefore holds no significance.