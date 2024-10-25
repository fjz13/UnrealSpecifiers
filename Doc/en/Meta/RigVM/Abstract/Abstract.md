# Abstract

- **Function Description:** Identifies this FRigUnit as an abstract class, which does not require the implementation of Execute.
- **Usage Location:** USTRUCT
- **Engine Module:** RigVMStruct
- **Metadata Type:** bool
- **Restriction Type:** Applicable to FRigUnit type
- **Commonly Used:** ★★

Indicates that this FRigUnit is an abstract class and does not need to implement Execute, often serving as a base class for other FRigUnit classes.

However, if Execute is still implemented, it can indeed be invoked within blueprints.

## Test Code:

```cpp
USTRUCT(meta = (DisplayName = "MyRigAbstract",Abstract))
struct INSIDER_API FRigUnit_MyRigAbstract: public FRigUnit
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (Input))
	float MyFloat_Input = 123.f;

	UPROPERTY(meta = (Output))
	float MyFloat_Output = 123.f;
};
```

## Test Results:

![Untitled](Untitled.png)

## Principle:

During certain internal processes, this abstract base class will naturally be overlooked.

```cpp
void FRigVMBlueprintUtils::ForAllRigVMStructs(TFunction<void(UScriptStruct*)> InFunction)
{
	// Run over all unit types
	for(TObjectIterator<UStruct> StructIt; StructIt; ++StructIt)
	{
		if (*StructIt)
		{
			if(StructIt->IsChildOf(FRigVMStruct::StaticStruct()) && !StructIt->HasMetaData(FRigVMStruct::AbstractMetaName))
			{
				if (UScriptStruct* ScriptStruct = Cast<UScriptStruct>(*StructIt))
				{
					InFunction(ScriptStruct);
				}
			}
		}
	}
}
```