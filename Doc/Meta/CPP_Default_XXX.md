# CPP_Default_XXX

Description: XXX=参数名字
Usage: UPARAM
Feature: Blueprint
Group: Blueprint
Type: string="abc"
Status: Done

在UFUNCTION的meta上保存参数的默认值。

测试代码：

```cpp
//(CPP_Default_intValue = 123, CPP_Default_intValue2 = 456, ModuleRelativePath = Function/Param/MyFunction_TestParam.h)
UFUNCTION(BlueprintCallable)
FString MyFuncTestParam_DefaultInt2(int intValue=123,int intValue2=456);
```