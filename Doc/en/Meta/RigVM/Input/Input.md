# Input

- **Function Description:** Designate this attribute under FRigUnit as an input pin.
- **Usage Location:** UPROPERTY
- **Engine Module:** RigVMStruct
- **Metadata Type:** bool
- **Restriction Type:** Attribute within FRigUnit
- **Associated Items:** [Output](../Output.md), [Visible](../Visible/Visible.md), [Hidden](../Hidden.md), [DetailsOnly](../DetailsOnly/DetailsOnly.md), [Constant](../Constant.md)
- **Commonliness:** ★★★★★

This attribute under FRigUnit is specified as an input pin.

It is worth noting that if a pin has both Input and Output designations, it becomes an IO pin, serving as both input and output simultaneously.

## Test Code:

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

## Test Results:

In the ControlRig blueprint, you can invoke the MyRig node. Observe the pin behavior of the attribute on the blueprint node and its display in the details panel on the right.

- MyFloat_Normal is not marked with meta and does not appear in either location.
- MyFloat_Input serves as an input pin and is also displayed in the right details panel.
- MyFloat_Output serves as an output pin and is not shown in the right details panel.
- MyFloat_IO can function as both an input and output pin and is displayed in the right details panel.
- MyFloat_Visible can be displayed as an input pin and is shown in the right details panel. However, it cannot be connected to a variable, meaning it can only be used as a constant.
- MyFloat_Hidden, like MyFloat_Normal, is hidden in both the blueprint node and the details panel, used only as its internal value.

![Untitled](Untitled.png)

## Principle:

The direction of the pin is determined by the Meta tag on the property. You can refer to the various types of ERigVMPinDirection in the source code.

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