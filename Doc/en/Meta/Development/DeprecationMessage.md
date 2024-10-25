# DeprecationMessage

- **Function Description:** Defines deprecated messages

- **Usage Locations:** UCLASS, UFUNCTION, UPROPERTY

- **Engine Module:** Development

- **Metadata Type:** string="abc"

- **Associated Items:**

  UCLASS: [Deprecated](../../Specifier/UCLASS/Development/Deprecated/Deprecated.md)

- **Commonality:** ★

## Example:

```cpp
UFUNCTION(meta=(DeprecatedFunction,DeprecationMessage="This function is deprecated, please use OtherFunctionName instead."))
ReturnType FunctionName([Parameter, Parameter, ...])

UPROPERTY(BlueprintReadWrite, meta=(DeprecatedProperty, DeprecationMessage="This is deprecated"))
FString PlantName;
```