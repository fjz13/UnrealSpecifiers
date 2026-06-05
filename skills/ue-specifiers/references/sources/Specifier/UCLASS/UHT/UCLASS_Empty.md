---
title: "UCLASS()"
id: "UCLASS.UCLASS()"
kind: "specifier"
symbol: "UCLASS()"
scope: "UCLASS"
category: "UHT"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "留空的默认行为是不能在蓝图中被继承，不能在蓝图中定义变量，但拥有反射的功能"
usage: "UCLASS / UHT"
---

# UCLASS()

## Decision Summary

- **Use when:** 类需要 UE 反射/UObject 体系，但不需要额外 class specifier。
- **Do not use when:** 类不需要反射、GC、Blueprint/editor 或 UObject 生命周期支持。
- **Requires:** 类必须符合 UObject/UCLASS 声明和生成代码要求。
- **Conflicts:** 空 `UCLASS()` 不代表 Blueprint、config、abstract 或 editor 暴露。
- **Prefer instead:** C++-only 非 UObject 类型不要加 UCLASS。

- **功能描述：** 留空的默认行为是不能在蓝图中被继承，不能在蓝图中定义变量，但拥有反射的功能。

- **引擎模块：** UHT
- **元数据类型：** bool
- **作用机制：** 在ClassFlags中增加CLASS_MatchedSerializers, CLASS_Native, CLASS_RequiredAPI, CLASS_TokenStreamAssembled, CLASS_Intrinsic, CLASS_Constructed
- **关联项：** [Without_UCLASS](Without_UCLASS.md)
- **常用程度：★★★★★**

不能在蓝图中被继承，不能在蓝图中定义变量。

但依然都可以通过蓝图ConstructObject创建出来。对于想要拥有反射功能，但是并不想在蓝图中被使用会挺适合。

## 示例代码：

```cpp
/*
[MyClass_Default	Class->Struct->Field->Object	/Script/Insider.MyClass_Default] [IncludePath = Class/MyClass_Default.h, ModuleRelativePath = Class/MyClass_Default.h]
ObjectFlags:	RF_Public | RF_Standalone | RF_Transient
Outer:	Package /Script/Insider
ClassFlags:	CLASS_MatchedSerializers | CLASS_Native | CLASS_RequiredAPI | CLASS_TokenStreamAssembled | CLASS_Intrinsic | CLASS_Constructed
Size:	48
{
public: void ExecuteUbergraph(int32 EntryPoint);
};
*/

UCLASS()
class INSIDER_API UMyClass_Default :public UObject
{
	GENERATED_BODY()
public:
};
```

默认的拥有这些标志：CLASS_MatchedSerializers | CLASS_Native | CLASS_RequiredAPI | CLASS_TokenStreamAssembled | CLASS_Intrinsic | CLASS_Constructed
## UE5.8 审计结论

UE5.8 UHT 或宏路径仍保留该条目；本轮按 UE5.8 标记为已验证。P3 中不少条目属于引擎内部、NoExportTypes 或插件专用用法，不建议普通项目代码直接套用。
