# CustomWidget

Usage: UPROPERTY
Feature: RigVM Pin
Type: string="abc"
Description: 指定该FRigUnit里的属性要用自定义的控件来编辑。
LimitedType: FRigUnit中的属性
Status: Done
Group: RigVMStruct

指定该FRigUnit里的属性要用自定义的控件来编辑。

CustomWidget的值是在一些选项中选择的，这些自定义控件是已经在引擎中实现的。

可用的列表为：BoneName，ControlName，SpaceName/NullName，CurveName，ElementName，ConnectorName，DrawingName，ShapeName，AnimationChannelName，MetadataName，MetadataTagName。

测试代码里就只用BoneName作为测试展示：

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

测试效果：

可见MyString_Custom的Pin类型变成可选BoneName的列表。

![Untitled](CustomWidget/Untitled.png)

原理：

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
//等等其他
}
```