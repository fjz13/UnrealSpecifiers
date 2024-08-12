# Constant

Description: 标识一个属性成为一个常量的引脚。
Usage: UPROPERTY, USTRUCT
Feature: RigVM Pin
Group: RigVMStruct
Type: bool
Status: Linked
Parent item: Input (Input.md)

放在UPROPERTY上的时候，和Visible一样，标识一个属性成为一个常量的引脚。

放在USTRUCT上的时候，发现用在IsDefinedAsConstant这种函数上，但是F5没有发现调用的地方。

```cpp
USTRUCT(meta = (DisplayName = "Rotation Order", Category = "Math|Quaternion", Constant))
struct RIGVM_API FRigVMFunction_MathQuaternionRotationOrder : public FRigVMFunction_MathBase
{
}
```