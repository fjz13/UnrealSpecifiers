# DeprecationMessage

功能描述: 定义弃用的消息
使用位置: UCLASS, UFUNCTION, UPROPERTY
Feature: Editor
引擎模块: Development
元数据类型: string="abc"
Example: DeprecationMessage="Message Text”
Status: Linked
Related To UCLASS: Deprecated (../../Specifier/UCLASS/Deprecated.md)
常用程度: 1

例子：

```cpp
UFUNCTION(meta=(DeprecatedFunction,DeprecationMessage="This function is deprecated, please use OtherFunctionName instead."))
ReturnType FunctionName([Parameter, Parameter, ...])

UPROPERTY(BlueprintReadWrite, meta=(DeprecatedProperty, DeprecationMessage="This is deprecated"))
FString PlantName;
```