# ReturnDisplayName

Usage: UFUNCTION
Feature: Blueprint
Type: string="abc"
Description: 改变函数返回值的名字，默认是ReturnValue
Status: Done
Group: Blueprint

函数的返回值引脚名字默认是ReturnValue，如果想自己提供一个更有意义的名字，则可以用ReturnDisplayName 来自定义一个名字。

测试代码：

```cpp
	UFUNCTION(BlueprintCallable, meta = (ReturnDisplayName = "IsSuccess"))
	static bool MyFunc_HasReturnDisplayName(FString Name) { return true; }

	UFUNCTION(BlueprintCallable, meta = ())
	static bool MyFunc_NoReturnDisplayName(FString Name) { return true; }
```

蓝图效果：

对比返回值的名字可以验证效果。

![Untitled](ReturnDisplayName/Untitled.png)

原理：

原理也很简单，在Pin上判断Meta并设置PinFriendlyName 

```cpp
if (Function->GetReturnProperty() == Param && Function->HasMetaData(FBlueprintMetadata::MD_ReturnDisplayName))
{
	Pin->PinFriendlyName = Function->GetMetaDataText(FBlueprintMetadata::MD_ReturnDisplayName);
}
```