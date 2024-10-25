# Input

- **功能描述：** 指定FRigUnit下的该属性作为输入引脚。
- **使用位置：** UPROPERTY
- **引擎模块：** RigVMStruct
- **元数据类型：** bool
- **限制类型：** FRigUnit中属性
- **关联项：** [Output](../Output.md), [Visible](../Visible/Visible.md), [Hidden](../Hidden.md), [DetailsOnly](../DetailsOnly/DetailsOnly.md), [Constant](../Constant.md)
- **常用程度：** ★★★★★

指定FRigUnit下的该属性作为输入引脚。

值得注意的是，一个引脚如果同时加上Input和Output，那它就变成IO引脚，同时可作为输入和输出。

## 测试代码：

```cpp
USTRUCT(meta = (DisplayName="MyRig"))
struct INSIDER_API FRigUnit_MyRig : public FRigUnit
{
	GENERATED_BODY()

	RIGVM_METHOD()
	virtual void Execute() override;

public:
	UPROPERTY()
	float MyFloat_Normal;

	UPROPERTY(meta = (Input))
	float MyFloat_Input;

	UPROPERTY(meta = (Output))
	float MyFloat_Output;

	UPROPERTY(meta = (Input, Output))
	float MyFloat_IO;

	UPROPERTY(meta = (Visible))
	float MyFloat_Visible;

	UPROPERTY(meta = (Hidden))
	float MyFloat_Hidden;
};
```

## 测试效果：

在ControlRig蓝图里就可以调用MyRig节点，注意观察属性在蓝图节点上的引脚表现以及在右侧细节面板的显示。

- MyFloat_Normal不标meta，在两个地方都没有显示。
- MyFloat_Input，作为输入引脚，且在右侧细节面板也显示。
- MyFloat_Output，作为输出引脚，右侧细节面板不显示。
- MyFloat_IO，可以同时作为输入和输出引脚，右侧细节面板会显示。
- MyFloat_Visible，可以作为输入引脚显示，右侧细节面板会显示。但是无法连接变量，意思是只能作为常量使用。
- MyFloat_Hidden，如同MyFloat_Normal一样，在蓝图节点和细节面板都隐藏起来，只是作为自己的内部值使用。

![Untitled](Untitled.png)

## 原理：

根据属性上的Meta标记来区分引脚的方向。可以在源码里查看ERigVMPinDirection 的各个类型。

```cpp
UENUM(BlueprintType)
enum class ERigVMPinDirection : uint8
{
	Input, // A const input value
	Output, // A mutable output value
	IO, // A mutable input and output value
	Visible, // A const value that cannot be connected to
	Hidden, // A mutable hidden value (used for interal state)
	Invalid // The max value for this enum - used for guarding.
};

ERigVMPinDirection FRigVMStruct::GetPinDirectionFromProperty(FProperty* InProperty)
{
	bool bIsInput = InProperty->HasMetaData(InputMetaName);
	bool bIsOutput = InProperty->HasMetaData(OutputMetaName);
	bool bIsVisible = InProperty->HasMetaData(VisibleMetaName);

	if (bIsVisible)
	{
		return ERigVMPinDirection::Visible;
	}

	if (bIsInput)
	{
		return bIsOutput ? ERigVMPinDirection::IO : ERigVMPinDirection::Input;
	}

	if(bIsOutput)
	{
		return ERigVMPinDirection::Output;
	}

	return ERigVMPinDirection::Hidden;
}
```