# MenuDescSuffix

- **Function Description:** Identifies the name suffix for the FRigUnit in the context menu of the Blueprint when right-clicked.
- **Usage Location:** USTRUCT
- **Engine Module:** RigVMStruct
- **Metadata Type:** Boolean
- **Restriction Type:** Applicable to FRigUnit type
- **Commonly Used:** ★★★

Identifies the name suffix for the FRigUnit in the context menu of the Blueprint when right-clicked.

## Test Code:

```cpp
USTRUCT(meta = (DisplayName = "MyRigSuffix", MenuDescSuffix = "(MyVector)"))
struct INSIDER_API FRigUnit_MyRigSuffix: public FRigUnit
{
	GENERATED_BODY()

	RIGVM_METHOD()
		virtual void Execute() override;
public:
	UPROPERTY(meta = (Input))
	float MyFloat_Input = 123.f;

	UPROPERTY(meta = (Output))
	float MyFloat_Output = 123.f;
};
```

## Test Effects:

It is visible that the suffix "(MyVector)" has appeared.

![Untitled](Untitled.png)

## Principle:

The data is obtained and then appended to the DisplayName.

```cpp
FString CategoryMetadata, DisplayNameMetadata, MenuDescSuffixMetadata;
Struct->GetStringMetaDataHierarchical(FRigVMStruct::CategoryMetaName, &CategoryMetadata);
Struct->GetStringMetaDataHierarchical(FRigVMStruct::DisplayNameMetaName, &DisplayNameMetadata);
Struct->GetStringMetaDataHierarchical(FRigVMStruct::MenuDescSuffixMetaName, &MenuDescSuffixMetadata);

if(DisplayNameMetadata.IsEmpty())
{
	DisplayNameMetadata = Struct->GetDisplayNameText().ToString();
}
if (!MenuDescSuffixMetadata.IsEmpty())
{
	MenuDescSuffixMetadata = TEXT(" ") + MenuDescSuffixMetadata;
}

FText MenuDesc = FText::FromString(DisplayNameMetadata + MenuDescSuffixMetadata);
```