# CustomWidget

- **Function Description:** Specifies that the properties within this FRigUnit should be edited using a custom control.
- **Usage Location:** UPROPERTY
- **Engine Module:** RigVMStruct
- **Metadata Type:** string="abc"
- **Restriction Type:** Attributes within FRigUnit
- **Commonality:** ★★

Indicates that the properties in the FRigUnit should be edited using a custom control.

The value for CustomWidget is chosen from a selection of options. These custom controls are already implemented within the engine.

The list of available options includes: BoneName, ControlName, SpaceName/NullName, CurveName, ElementName, ConnectorName, DrawingName, ShapeName, AnimationChannelName, MetadataName, MetadataTagName.

In the test code, BoneName is used solely for demonstration purposes:

```cpp
USTRUCT(meta = (DisplayName = "MyRigCustomWidget"))
struct INSIDER_API FRigUnit_MyRigCustomWidget : public FRigUnit
{
	GENERATED_BODY()

	RIGVM_METHOD()
		virtual void Execute() override;
public:
	UPROPERTY(meta = (Input))
	FString MyString;

	UPROPERTY(meta = (Input, CustomWidget = "BoneName"))
	FString MyString_Custom;

	UPROPERTY(meta = (Output))
	float MyFloat_Output = 123.f;
};
```

## Test Results:

The Pin type for MyString_Custom is changed to a selectable list of BoneName.

![Untitled](Untitled.png)

## Principle:

```cpp
TSharedPtr<SGraphPin> FControlRigGraphPanelPinFactory::CreatePin_Internal(UEdGraphPin* InPin) const
{
		if (CustomWidgetName == TEXT("BoneName"))
		{
			return SNew(SRigVMGraphPinNameList, InPin)
				.ModelPin(ModelPin)
				.OnGetNameFromSelection_UObject(RigGraph, &UControlRigGraph::GetSelectedElementsNameList)
				.OnGetNameListContent_UObject(RigGraph, &UControlRigGraph::GetBoneNameList)
				.OnGetSelectedClicked_UObject(RigGraph, &UControlRigGraph::HandleGetSelectedClicked)
				.OnBrowseClicked_UObject(RigGraph, &UControlRigGraph::HandleBrowseClicked);
		}
//Additional details to follow
}
```