# DeprecationMessage

Description: 定义弃用的消息
Usage: UCLASS, UFUNCTION, UPROPERTY
Feature: Editor
Group: Development
Type: string="abc"
Example: DeprecationMessage="Message Text”
Status: Linked
Related To UCLASS: Deprecated (../../Specifier/UCLASS/Deprecated.md)

例子：

```cpp
UFUNCTION(meta=(DeprecatedFunction,DeprecationMessage="This function is deprecated, please use OtherFunctionName instead."))
ReturnType FunctionName([Parameter, Parameter, ...])

UPROPERTY(BlueprintReadWrite, meta=(DeprecatedProperty, DeprecationMessage="This is deprecated"))
FString PlantName;
```