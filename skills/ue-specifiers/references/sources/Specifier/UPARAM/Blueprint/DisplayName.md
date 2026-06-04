---
title: "DisplayName"
id: "UPARAM.DisplayName"
kind: "specifier"
symbol: "DisplayName"
scope: "UPARAM"
category: "Blueprint"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "更改函数参数在蓝图节点上的显示名字"
usage: "UPARAM / Blueprint"
---

# DisplayName

- **功能描述：** 更改函数参数在蓝图节点上的显示名字

- **元数据类型：** string="abc"
- **引擎模块：** Blueprint, Parameter
- **作用机制：** 在Meta中加入[DisplayName](../../../Meta/Blueprint/DisplayName.md)
- **常用程度：** ★★★★★

注意：UPARAM也可以用在返回值上，默认值是ReturnValue。

## 测试代码：

```cpp
//(DisplayName = My Other Name)
	UFUNCTION(BlueprintCallable)
	UPARAM(DisplayName = "My Return String") FString MyFuncTestParam_DisplayName(UPARAM(DisplayName = "My Other Name") int value);
```

## 蓝图节点：


## 行为

UE5.8 UHT 的默认 `DisplayName` specifier 写入 `DisplayName` metadata。用于 UPARAM 时改变 Blueprint 节点参数或返回值的显示名，不改变 C++ 参数名。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `UhtDefaultSpecifiers.cs` `DisplayNameSpecifier` writes `DisplayName` metadata
  - 本地样例辅助对照：`D:/github/GitWorkspace/Hello/Source/Insider/Function/Param/MyFunction_TestParam.h`。

## 常见误用

用显示名做逻辑查找；或以为它会改变生成代码中的参数符号。
