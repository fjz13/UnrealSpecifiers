# IgnoreForMemberInitializationTest

- **Functional Description:** Allows this property to bypass the uninitialized validation for the structure.
- **Usage Location:** UPROPERTY
- **Engine Module:** Struct
- **Metadata Type:** bool
- **Restricted Type:** Attributes within C++ structures
- **Commonality:** ★★

Allows this property to bypass the uninitialized validation for the structure.

- What is meant by "uninitialized" refers to variables in a C++ structure that are not initialized in the constructor and do not have initial values assigned directly
- Uninitialized structure validation refers to the verification tool provided by the engine, which can be invoked using the console command "CoreUObject.AttemptToFindUninitializedScriptStructMembers". This will output information on all uninitialized variables within the engine.
- In UE, USTRUCT is simply a pure C++ structure, unlike classes defined with UCLASS, which are all UObject, and whose UPROPERTY attributes are automatically initialized to 0. UPROPERTY within structures, however, are not automatically initialized and require manual initialization.
- In practice, if a developer is aware that the uninitialized state of a variable will not impact logic, there is no issue with it remaining uninitialized. However, in reality, it is often due to sheer laziness or forgetfulness that attributes are not initialized. It is therefore recommended to initialize all attributes within a structure. There are, however, special cases where certain attributes should not be initialized, such as some FGuid variables in source code examples, which are only assigned values when they are actually used. Initializing them before use holds little significance. In such cases, IgnoreForMemberInitializationTest can be used to make the property skip this validation, thereby avoiding error messages.

## Test Code:

```cpp
USTRUCT(BlueprintType)
struct INSIDER_API FMyStruct_InitTest
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MyProperty;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta=(IgnoreForMemberInitializationTest))
	int32 MyProperty_IgnoreTest;
};
```

## Test Results:

It is evident that MyProperty encountered an error due to the absence of IgnoreForMemberInitializationTest.

```cpp
在控制台调用CoreUObject.AttemptToFindUninitializedScriptStructMembers后：

LogClass: Error: IntProperty FMyStruct_InitTest::MyProperty is not initialized properly. Module:Insider File:Property/Struct/MyProperty_Struct.h
```

## Principle:

This command line invokes AttemptToFindUninitializedScriptStructMembers and subsequently calls FindUninitializedScriptStructMembers to identify uninitialized variables within UScriptStruct. The specific method of identification can be examined within this function.

```cpp

static void FindUninitializedScriptStructMembers(UScriptStruct* ScriptStruct, EScriptStructTestCtorSyntax ConstructorSyntax, TSet<const FProperty*>& OutUninitializedProperties)
{

		for (const FProperty* Property : TFieldRange<FProperty>(ScriptStruct, EFieldIteratorFlags::ExcludeSuper))
	{
#if	WITH_EDITORONLY_DATA
		static const FName NAME_IgnoreForMemberInitializationTest(TEXT("IgnoreForMemberInitializationTest"));
		if (Property->HasMetaData(NAME_IgnoreForMemberInitializationTest))
		{
			continue;
		}
#endif // WITH_EDITORONLY_DATA

}

//called by this
FStructUtils::AttemptToFindUninitializedScriptStructMembers();

// Command line invocation
CoreUObject.AttemptToFindUninitializedScriptStructMembers
```