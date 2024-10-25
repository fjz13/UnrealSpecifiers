# ScriptConstantHost

- **Function Description:** Extending ScriptConstant, this specifies the type in which the constant is generated.
- **Usage Location:** UFUNCTION
- **Engine Module:** Script
- **Metadata Type:** string="abc"
- **Associated Items:** [ScriptConstant](ScriptConstant.md)
- **Commonality:** ★

Building upon ScriptConstant, this designates the type where the constant is to be generated.

Refer to the test code in ScriptConstant. The string specified by ScriptConstantHost should represent an object path.

```cpp
	UFUNCTION(BlueprintPure, meta = (ScriptConstant="FirstString", ScriptConstantHost = "/Script/Insider.MyPython_ConstantOwner"))
	static FString MyStringConst() { return TEXT("First"); }
```