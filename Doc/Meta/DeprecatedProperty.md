# DeprecatedProperty

Description: 标记弃用，引用到该属性的蓝图会触发一个警告
Usage: UPROPERTY
Feature: Blueprint
Group: Development
Type: bool
Status: Linked
Related To UCLASS: Deprecated (../../Specifier/UCLASS/Deprecated.md)

Marking a property with `DeprecatedProperty` and `DeprecationMessage` causes a warning to be shown when compiling a Blueprint that uses the variable.

It seems that without `DeprecationMessage`, there is no warning shown. So make sure you add one.

In the Unreal codebase I've seen a lot of instances of renaming the variable with a prefix `DEPRECATED_` and using `DisplayName` to make it look the same to Blueprints.

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