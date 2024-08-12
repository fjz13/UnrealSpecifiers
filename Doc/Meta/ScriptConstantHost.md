# ScriptConstantHost

Description: 在ScriptConstant的基础上，指定常量生成的所在类型。
Usage: UFUNCTION
Feature: Script
Group: Script
Type: string="abc"
Status: Done
Parent item: ScriptConstant (ScriptConstant.md)

在ScriptConstant的基础上，指定常量生成的所在类型。

测试代码见ScriptConstant。ScriptConstantHost指定的字符串应该是个对象路径。

```cpp
	UFUNCTION(BlueprintPure, meta = (ScriptConstant="FirstString", ScriptConstantHost = "/Script/Insider.MyPython_ConstantOwner"))
	static FString MyStringConst() { return TEXT("First"); }
```