# Constant

功能描述: 标识一个属性成为一个常量的引脚。
使用位置: UPROPERTY, USTRUCT
Feature: RigVM Pin
引擎模块: RigVMStruct
元数据类型: bool
Status: Linked
Parent item: Input (Input.md)
常用程度: 3

放在UPROPERTY上的时候，和Visible一样，标识一个属性成为一个常量的引脚。

放在USTRUCT上的时候，发现用在IsDefinedAsConstant这种函数上，但是F5没有发现调用的地方。

```cpp
USTRUCT(meta = (DisplayName = "Rotation Order", Category = "Math|Quaternion", Constant))
struct RIGVM_API FRigVMFunction_MathQuaternionRotationOrder : public FRigVMFunction_MathBase
{
}
```