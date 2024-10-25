# DeprecationMessage

- **功能描述：** 定义弃用的消息

- **使用位置：** UCLASS, UFUNCTION, UPROPERTY

- **引擎模块：** Development

- **元数据类型：** string="abc"

- **关联项：**

  UCLASS：[Deprecated](../../Specifier/UCLASS/Development/Deprecated/Deprecated.md)

- **常用程度：** ★

## 例子：

```cpp
UFUNCTION(meta=(DeprecatedFunction,DeprecationMessage="This function is deprecated, please use OtherFunctionName instead."))
ReturnType FunctionName([Parameter, Parameter, ...])

UPROPERTY(BlueprintReadWrite, meta=(DeprecatedProperty, DeprecationMessage="This is deprecated"))
FString PlantName;
```