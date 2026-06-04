---
title: "GetByRef"
id: "meta.GetByRef"
kind: "meta"
symbol: "GetByRef"
category: "Blueprint"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定UHT为该属性生成返回引用的C++代码"
usage: "UPROPERTY"
---

# GetByRef

- **功能描述：** 指定UHT为该属性生成返回引用的C++代码
- **使用位置：** UPROPERTY
- **引擎模块：** UHT
- **元数据类型：** bool
- **限制类型：** 只用在SparseClassDataTypes 指定的结构里的属性。
- **关联项：** [SparseClassDataTypes](SparseClassDataTypes.md)

指定UHT为该属性生成返回引用的C++代码。

只用在SparseClassDataTypes 指定的结构里的属性。

## 代码例子：

```cpp
USTRUCT(BlueprintType)
struct FMySparseClassData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString MyString_EditDefault = TEXT("MyName");
	//FString GetMyString_EditDefault() const { return GetMySparseClassData(EGetSparseClassDataMethod::ArchetypeIfNull)->MyString_EditDefault; } \

	// "GetByRef" means that Blueprint graphs access a const ref instead of a copy.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (GetByRef))
	FString MyString_EditDefault_ReadOnly = TEXT("MyName");
	//const FString& GetMyString_EditDefault_ReadOnly() const { return GetMySparseClassData(EGetSparseClassDataMethod::ArchetypeIfNull)->MyString_EditDefault_ReadOnly; }
};

UCLASS(Blueprintable, BlueprintType, SparseClassDataTypes = MySparseClassData)
class INSIDER_API AMyActor_SparseClassDataTypes :public AActor
{
	GENERATED_BODY()
}
```

## 生成的代码：

可见，后者生成返回值是const FString&而不是FString。

```cpp
#define FID_Hello_Source_Insider_Class_Trait_MyClass_SparseClassDataTypes_h_36_SPARSE_DATA_PROPERTY_ACCESSORS \
FString GetMyString_EditDefault() const { return GetMySparseClassData(EGetSparseClassDataMethod::ArchetypeIfNull)->MyString_EditDefault; } \
const FString& GetMyString_EditDefault_ReadOnly() const { return GetMySparseClassData(EGetSparseClassDataMethod::ArchetypeIfNull)->MyString_EditDefault_ReadOnly; }
```

## 原理：

UHT中为SparseDataType生成代码的时候会判断GetByRef来分别生成不同的格式代码。

```cpp
private StringBuilder AppendSparseDeclarations(StringBuilder builder, UhtClass classObj, IEnumerable<UhtScriptStruct> sparseScriptStructs, UhtUsedDefineScopes<UhtProperty> sparseProperties)
{
	if (property.MetaData.ContainsKey(UhtNames.GetByRef))
	{
				builder.Append("const ").AppendSparse(property).Append("& Get").Append(cleanPropertyName).Append("() const");
	}
	else
	{
				builder.AppendSparse(property).Append(" Get").Append(cleanPropertyName).Append("() const");
	}
}
```

## 行为

UE5.8 property metadata；Blueprint getter path 可按引用返回属性值。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `ObjectMacros.h` metadata declaration/comment
  - UE5.8 `BlueprintGraph` metadata constants or node usage

## 常见误用

参数名、属性名或目标宏写错导致 metadata 被保留但没有对应编辑器/Blueprint 行为。
