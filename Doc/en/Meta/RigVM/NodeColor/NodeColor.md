# NodeColor

- **Function Description:** Specifies the RGB color value for the FRigUnit Blueprint node.
- **Usage Location:** USTRUCT
- **Engine Module:** RigVMStruct
- **Metadata Type:** string="abc"
- **Restriction Type:** FRigUnit
- **Commonliness:** ★★

Specifies the RGB color value of the FRigUnit Blueprint node.

## Test Code:

```cpp
USTRUCT(meta = (DisplayName = "MyRigColor",NodeColor="1 0 0"))
struct INSIDER_API FRigUnit_MyRigColor: public FRigUnit
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

## Testing Code:

With NodeColor added, the color transitions from left to right.

![Untitled](Untitled.png)

## 测试效果:

Extracts the color value from the Meta data.

```cpp
FLinearColor FRigVMDispatchFactory::GetNodeColor() const
{
	if(const UScriptStruct* ScriptStruct = GetScriptStruct())
	{
		FString NodeColor;
		if (ScriptStruct->GetStringMetaDataHierarchical(FRigVMStruct::NodeColorMetaName, &NodeColor))
		{
			return FRigVMTemplate::GetColorFromMetadata(NodeColor);
		}
	}
	return FLinearColor::White;
}

```