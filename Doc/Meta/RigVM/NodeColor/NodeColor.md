# NodeColor

功能描述: 指定FRigUnit蓝图节点的RGB颜色值。
使用位置: USTRUCT
Feature: RigVM
引擎模块: RigVMStruct
元数据类型: string="abc"
限制类型: FRigUnit
Status: Done
常用程度: 2

指定FRigUnit蓝图节点的RGB颜色值。

测试代码：

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

测试效果：

加上NodeColor之后，颜色从左变成右。

![Untitled](NodeColor/Untitled.png)

原理：

从Meta中获取颜色值。

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