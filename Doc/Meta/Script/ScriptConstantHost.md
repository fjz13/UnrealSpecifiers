# ScriptConstantHost

- **功能描述：** 在ScriptConstant的基础上，指定常量生成的所在类型。
- **使用位置：** UFUNCTION
- **引擎模块：** Script
- **元数据类型：** string="abc"
- **关联项：** [ScriptConstant](ScriptConstant.md)
- **常用程度：** ★

在ScriptConstant的基础上，指定常量生成的所在类型。

测试代码见ScriptConstant。ScriptConstantHost指定的字符串应该是个对象路径。

```cpp
	UFUNCTION(BlueprintPure, meta = (ScriptConstant="FirstString", ScriptConstantHost = "/Script/Insider.MyPython_ConstantOwner"))
	static FString MyStringConst() { return TEXT("First"); }
```
