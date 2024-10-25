# Constant

- **Function Description:** Indicates that a property is to be treated as a constant pin.
- **Usage Locations:** UPROPERTY, USTRUCT
- **Engine Module:** RigVMStruct
- **Metadata Type:** bool
- **Associated Items:** [Input](Input/Input.md)
- **Commonality:** ★★★

When applied to UPROPERTY, similar to Visible, it designates a property as a constant pin.

When applied to USTRUCT, it is observed in functions like IsDefinedAsConstant, but no calls to it were found using F5.

```cpp
USTRUCT(meta = (DisplayName = "Rotation Order", Category = "Math|Quaternion", Constant))
struct RIGVM_API FRigVMFunction_MathQuaternionRotationOrder : public FRigVMFunction_MathBase
{
}
```