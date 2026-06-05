---
title: "immutable"
id: "USTRUCT.immutable"
kind: "specifier"
symbol: "immutable"
scope: "USTRUCT"
category: "Serialization"
source_status: "removed_or_deprecated"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "UE5.8 中正在淘汰。Immutable 只允许 NoExportTypes.h 中的 mirror structs，项目自定义 USTRUCT 不应使用"
usage: "USTRUCT / Serialization"
---

# immutable

## Decision Summary

- **Use when:** 迁移、诊断或阅读旧代码时需要识别 `immutable`。
- **Do not use when:** 不要在新的 UE5.8 代码中把它作为常规方案。
- **Requires:** 确认目标代码确实依赖旧版本或兼容路径，并阅读正文的版本说明。
- **Conflicts:** 与当前 UE5.8 推荐写法冲突时，以当前引擎行为为准。
- **Prefer instead:** 新代码优先使用正文或索引中指向的当前替代项。

- **功能描述：** UE5.8 中正在淘汰。`Immutable` 只允许 NoExportTypes.h 中的 mirror structs，项目自定义 USTRUCT 不应使用。
- **元数据类型：** bool
- **引擎模块：** Serialization
- **作用机制：** 在StructFlags中加入STRUCT_Immutable

当前只在noexporttypes.h里找到一堆Struct

指定这个结构的字段已经定义完毕，以后不会再修改，因此可以UseBinarySerialization来序列化，不需要支持字段的增删。

```cpp
//USTRUCT(BlueprintType,Immutable)	//error : Immutable is being phased out in favor of SerializeNative, and is only legal on the mirror structs declared in UObject
//struct INSIDER_API FMyStruct_Immutable
//{
//	GENERATED_BODY()
//
//	UPROPERTY(BlueprintReadWrite,EditAnywhere)
//	float Score;
//
//};

Struct[67] WithFlags:STRUCT_Immutable
Struct:	ScriptStruct /Script/CoreUObject.Guid
Struct:	ScriptStruct /Script/CoreUObject.DateTime
Struct:	ScriptStruct /Script/CoreUObject.Box
Struct:	ScriptStruct /Script/CoreUObject.Vector
Struct:	ScriptStruct /Script/CoreUObject.Box2D
Struct:	ScriptStruct /Script/CoreUObject.Vector2D
Struct:	ScriptStruct /Script/CoreUObject.Box2f
Struct:	ScriptStruct /Script/CoreUObject.Vector2f
Struct:	ScriptStruct /Script/CoreUObject.Box3d
Struct:	ScriptStruct /Script/CoreUObject.Vector3d
Struct:	ScriptStruct /Script/CoreUObject.Box3f
Struct:	ScriptStruct /Script/CoreUObject.Vector3f
Struct:	ScriptStruct /Script/CoreUObject.Color
Struct:	ScriptStruct /Script/CoreUObject.Int32Point
Struct:	ScriptStruct /Script/CoreUObject.Int32Vector
Struct:	ScriptStruct /Script/CoreUObject.Int32Vector2
Struct:	ScriptStruct /Script/CoreUObject.Int32Vector4
Struct:	ScriptStruct /Script/CoreUObject.Int64Point
Struct:	ScriptStruct /Script/CoreUObject.Int64Vector
Struct:	ScriptStruct /Script/CoreUObject.Int64Vector2
Struct:	ScriptStruct /Script/CoreUObject.Int64Vector4
Struct:	ScriptStruct /Script/CoreUObject.LinearColor
Struct:	ScriptStruct /Script/CoreUObject.Quat
Struct:	ScriptStruct /Script/CoreUObject.TwoVectors
Struct:	ScriptStruct /Script/CoreUObject.IntPoint
Struct:	ScriptStruct /Script/CoreUObject.IntVector
Struct:	ScriptStruct /Script/CoreUObject.IntVector2
Struct:	ScriptStruct /Script/CoreUObject.IntVector4
Struct:	ScriptStruct /Script/CoreUObject.Matrix
Struct:	ScriptStruct /Script/CoreUObject.Plane
Struct:	ScriptStruct /Script/CoreUObject.Matrix44d
Struct:	ScriptStruct /Script/CoreUObject.Plane4d
Struct:	ScriptStruct /Script/CoreUObject.Matrix44f
Struct:	ScriptStruct /Script/CoreUObject.Plane4f
Struct:	ScriptStruct /Script/CoreUObject.OrientedBox
Struct:	ScriptStruct /Script/CoreUObject.PackedNormal
Struct:	ScriptStruct /Script/CoreUObject.PackedRGB10A2N
Struct:	ScriptStruct /Script/CoreUObject.PackedRGBA16N
Struct:	ScriptStruct /Script/CoreUObject.Quat4d
Struct:	ScriptStruct /Script/CoreUObject.Quat4f
Struct:	ScriptStruct /Script/CoreUObject.Ray
Struct:	ScriptStruct /Script/CoreUObject.Ray3d
Struct:	ScriptStruct /Script/CoreUObject.Ray3f
Struct:	ScriptStruct /Script/CoreUObject.Rotator
Struct:	ScriptStruct /Script/CoreUObject.Rotator3d
Struct:	ScriptStruct /Script/CoreUObject.Rotator3f
Struct:	ScriptStruct /Script/CoreUObject.Sphere
Struct:	ScriptStruct /Script/CoreUObject.Sphere3d
Struct:	ScriptStruct /Script/CoreUObject.Sphere3f
Struct:	ScriptStruct /Script/CoreUObject.Timespan
Struct:	ScriptStruct /Script/CoreUObject.Transform3d
Struct:	ScriptStruct /Script/CoreUObject.Transform3f
Struct:	ScriptStruct /Script/CoreUObject.Uint32Point
Struct:	ScriptStruct /Script/CoreUObject.Uint32Vector
Struct:	ScriptStruct /Script/CoreUObject.Uint32Vector2
Struct:	ScriptStruct /Script/CoreUObject.Uint32Vector4
Struct:	ScriptStruct /Script/CoreUObject.Uint64Point
Struct:	ScriptStruct /Script/CoreUObject.Uint64Vector
Struct:	ScriptStruct /Script/CoreUObject.Uint64Vector2
Struct:	ScriptStruct /Script/CoreUObject.Uint64Vector4
Struct:	ScriptStruct /Script/CoreUObject.UintPoint
Struct:	ScriptStruct /Script/CoreUObject.UintVector
Struct:	ScriptStruct /Script/CoreUObject.UintVector2
Struct:	ScriptStruct /Script/CoreUObject.UintVector4
Struct:	ScriptStruct /Script/CoreUObject.Vector4
Struct:	ScriptStruct /Script/CoreUObject.Vector4d
Struct:	ScriptStruct /Script/CoreUObject.Vector4f
```

## 行为

UE5.8 UHT 仍解析 `Immutable` 并写入 `Atomic | Immutable` struct flags，但后续校验报错：该 specifier 正在被淘汰，且仅 NoExportTypes.h mirror structs 合法。

## UE5.8 审计结论

- 状态：`removed_or_deprecated`。
- 结论：UE5.8 下已标记为废弃/不可推荐。
- 证据：
  - UE5.8 `UhtScriptStructSpecifiers.cs` `ImmutableSpecifier` writes `Atomic | Immutable`
  - UE5.8 `UhtScriptStruct.cs` validates it as phased out and only legal in NoExportTypes.h
  - 本地样例辅助对照：source note contains local commented repro; UE5.8 source is canonical evidence。

## 常见误用

在项目自定义 USTRUCT 上使用；UE5.8 下会被 UHT 拒绝，应避免推荐。
