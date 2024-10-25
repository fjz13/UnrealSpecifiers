# ExpandByDefault

- **Function Description:** Defaults to expanding the attribute pins within FRigUnit.
- **Usage Location:** UPROPERTY
- **Engine Module:** RigVMStruct
- **Metadata Type:** boolean
- **Commonly Used:** ★★★

Defaults to expanding the attribute pins within FRigUnit.

## Test Code:

```cpp
USTRUCT(meta = (DisplayName = "MyRig"))
struct INSIDER_API FRigUnit_MyRig : public FRigUnit
{
	UPROPERTY(meta = (Input))
	FMyCommonStruct MyStruct_Normal;

	UPROPERTY(meta = (Input, ExpandByDefault))
	FMyCommonStruct MyStruct_ExpandByDefault;

		UPROPERTY(meta = (Output))
	float MyFloat_Output = 123.f;
｝
```

## Test Code:

Visible that MyStruct_ExpandByDefault expands the structure by default.

![Untitled](Untitled.png)

## 测试效果:

Identifies the metadata and sets the bIsExpanded state for the pin.

```cpp
FRigVMPinInfo::FRigVMPinInfo(FProperty* InProperty, ERigVMPinDirection InDirection, int32 InParentIndex, const uint8* InDefaultValueMemory)
{
	if (InProperty->HasMetaData(FRigVMStruct::ExpandPinByDefaultMetaName))
	{
		bIsExpanded = true;
	}
}
```