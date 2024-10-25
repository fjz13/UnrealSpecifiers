# immutable

- **功能描述：** Immutable is only legal in Object.h and is being phased out, do not use on new structs!
- **元数据类型：** bool
- **引擎模块：** Serialization
- **作用机制：** 在StructFlags中加入[STRUCT_Immutable](../../../Flags/EStructFlags/STRUCT_Immutable.md)

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