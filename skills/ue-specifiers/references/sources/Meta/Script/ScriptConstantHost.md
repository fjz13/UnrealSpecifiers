---
title: "ScriptConstantHost"
id: "meta.ScriptConstantHost"
kind: "meta"
symbol: "ScriptConstantHost"
category: "Script"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "在ScriptConstant的基础上，指定常量生成的所在类型"
usage: "UFUNCTION"
---

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
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。
