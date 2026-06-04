---
title: "CustomConstructor"
id: "UCLASS.CustomConstructor"
kind: "specifier"
symbol: "CustomConstructor"
scope: "UCLASS"
category: "UHT"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "阻止构造函数声明自动生成"
usage: "UCLASS / UHT"
---

# CustomConstructor

- **功能描述：** 阻止构造函数声明自动生成。
- **引擎模块：** UHT
- **元数据类型：** bool
- **作用机制：** 在ClassFlags中添加CLASS_CustomConstructor

UHT不会生成 NO_API UMyClass_ModuleAPI(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());的默认构造函数。但是这个一般都是配合GENERATED_UCLASS_BODY使用的，因为GENERATED_BODY会自动生成默认构造函数。一般在自己需要自定义这个函数的时候使用。（但其实用GENERATED_BODY也行）

当前已经弃用：

```cpp
CLASS_CustomConstructor UE_DEPRECATED(5.1, "CLASS_CustomConstructor should no longer be used. It is no longer being set by engine code.") = 0x00008000u,
```
## UE5.8 审计结论

UE5.8 UHT 或宏路径仍保留该条目；本轮按 UE5.8 标记为已验证。P3 中不少条目属于引擎内部、NoExportTypes 或插件专用用法，不建议普通项目代码直接套用。
