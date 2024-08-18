# DeprecatedProperty

功能描述: 标记弃用，引用到该属性的蓝图会触发一个警告
使用位置: UPROPERTY
Feature: Blueprint
引擎模块: Development
元数据类型: bool
Status: Linked
Related To UCLASS: Deprecated (../../Specifier/UCLASS/Deprecated.md)
常用程度: 1

标记弃用，引用到该属性的蓝图会触发一个警告

示例代码：

```cpp
// Simple
UPROPERTY(BlueprintReadWrite, meta=(DeprecatedProperty, DeprecationMessage="This is deprecated"))
FString PlantName;

// Better
UPROPERTY(BlueprintReadWrite, meta=(DisplayName="PlantName", DeprecatedProperty, DeprecationMessage="PlantName is deprecated, instead use PlantDisplayName."))
FString DEPRECATED_PlantName;
```

![Untitled](DeprecatedProperty/Untitled.png)

![Untitled](DeprecatedProperty/Untitled%201.png)