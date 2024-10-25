# Icon

- **Function description:** Sets the icon for the FRigUnit blueprint node.
- **Usage location:** USTRUCT
- **Engine module:** RigVMStruct
- **Metadata type:** string="abc"
- **Restriction type:** FRigUnit
- **Commonality:** ★★

Sets the icon for the FRigUnit blueprint node.

As indicated by the comments in the source code, the format for the Icon is "StyleSetName|StyleName|SmallStyleName|StatusOverlayStyleName", with the last two being optional. For more information, refer to the FSlateIcon documentation.

## Test Code:

```cpp
USTRUCT(meta = (DisplayName = "MyRigIcon",Icon="EditorStyle|GraphEditor.Macro.ForEach_16x"))
struct INSIDER_API FRigUnit_MyRigIcon: public FRigUnit
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

## Test Results:

It is evident that after adding the Icon, the upper-left corner icon changes to a different one, no longer the default function target 'f'.

![Untitled](Untitled.png)

## Principle:

```cpp
FSlateIcon URigVMEdGraphNode::GetIconAndTint(FLinearColor& OutColor) const
{

		if(MetadataScriptStruct && MetadataScriptStruct->HasMetaDataHierarchical(FRigVMStruct::IconMetaName))
		{
			FString IconPath;
			const int32 NumOfIconPathNames = 4;

			FName IconPathNames[NumOfIconPathNames] = {
				NAME_None, // StyleSetName
				NAME_None, // StyleName
				NAME_None, // SmallStyleName
				NAME_None  // StatusOverlayStyleName
			};

			// icon path format: StyleSetName|StyleName|SmallStyleName|StatusOverlayStyleName
			// the last two names are optional, see FSlateIcon() for reference
			MetadataScriptStruct->GetStringMetaDataHierarchical(FRigVMStruct::IconMetaName, &IconPath);
			return FSlateIcon(IconPathNames[0], IconPathNames[1], IconPathNames[2], IconPathNames[3]);
		}
}
```