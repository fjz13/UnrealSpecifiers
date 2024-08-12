# Icon

Usage: USTRUCT
Feature: RigVM
Type: string="abc"
Description: 设定FRigUnit蓝图节点的图标。
LimitedType: FRigUnit
Status: Done
Group: RigVMStruct

设定FRigUnit蓝图节点的图标。

根据源码中的注释得知，Icon的格式是“StyleSetName|StyleName|SmallStyleName|StatusOverlayStyleName”，最后两项是可选的，可参考FSlateIcon的更多介绍。

测试代码：

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

测试效果：

可见加了Icon之后，左上角图标变成了其他，不是默认的f函数目标。

![Untitled](Icon/Untitled.png)

原理：

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