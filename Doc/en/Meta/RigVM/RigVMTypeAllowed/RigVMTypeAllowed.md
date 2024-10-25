# RigVMTypeAllowed

- **Function Description:** Specifies a UENUM that can be selected for the UEnum* property within an FRigUnit.
- **Usage Location:** UENUM
- **Engine Module:** RigVMStruct
- **Metadata Type:** bool
- **Commonality:** ★★

Specifies that a UENUM can be chosen for the UEnum* attribute of an FRigUnit.

## Test Code:

```cpp

UENUM(BlueprintType)
enum class ERigMyEnum : uint8
{
	First,
	Second,
	Third,
};

UENUM(BlueprintType, meta = (RigVMTypeAllowed))
enum class ERigMyEnumAllowed : uint8
{
	Cat,
	Dog,
	Tiger,
};

USTRUCT(meta = (DisplayName = "MyRigEnum"))
struct INSIDER_API FRigUnit_MyRigEnum : public FRigUnit
{
	GENERATED_BODY()

	RIGVM_METHOD()
		virtual void Execute() override;
public:
	UPROPERTY(meta = (Input))
	UEnum* MyEnum;

	UPROPERTY(meta = (Output))
	float MyFloat_Output = 123.f;
};
```

## Test Code:

Only ERigMyEnumAllowed is visible in the options list, with ERigMyEnum being absent.

![Untitled](Untitled.png)

## 测试效果:

When generating options, check if !Enum->IsAsset() indicates an enumeration in C++, and then RigVMTypeAllowed must be present.

```cpp
void SRigVMEnumPicker::PopulateEnumOptions()
{
	EnumOptions.Reset();
	EnumOptions.Add(MakeShareable(new FString(TEXT("None"))));
	for (TObjectIterator<UEnum> EnumIt; EnumIt; ++EnumIt)
	{
		UEnum* Enum = *EnumIt;

		if (Enum->HasAnyFlags(RF_BeginDestroyed | RF_FinishDestroyed) || !Enum->HasAllFlags(RF_Public))
		{
			continue;
		}

		// Any asset based enum is valid
		if (!Enum->IsAsset())
		{
			// Native enums only allowed if contain RigVMTypeAllowed metadata
			if (!Enum->HasMetaData(TEXT("RigVMTypeAllowed")))
			{
				continue;
			}
		}

		EnumOptions.Add(MakeShareable(new FString(Enum->GetPathName())));
	}
}
```