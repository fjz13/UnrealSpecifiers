---
title: "NiagaraInternalType"
id: "meta.NiagaraInternalType"
kind: "meta"
symbol: "NiagaraInternalType"
category: "Niagara"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定该结构的类型为Niagara的内部类型"
usage: "USTRUCT"
---

# NiagaraInternalType

## Decision Summary

- **Use when:** `NiagaraInternalType` metadata 的 `USTRUCT` 场景需要：指定该结构的类型为Niagara的内部类型。
- **Do not use when:** 目标声明不属于 `USTRUCT`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 指定该结构的类型为Niagara的内部类型。
- **使用位置：** USTRUCT
- **引擎模块：** Niagara
- **元数据类型：** bool
- **常用程度：** 0

指定该结构的类型为Niagara的内部类型。

用来和用户自定义的类型区分。用户不需要自己使用该元数据。
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。

## 源码例子：

```cpp
USTRUCT(meta = (DisplayName = "Half", NiagaraInternalType = "true"))
struct FNiagaraHalf
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = Parameters)
	uint16 Value = 0;
};

USTRUCT(meta = (DisplayName = "Half Vector2", NiagaraInternalType = "true"))
struct FNiagaraHalfVector2
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = Parameters)
	uint16 x = 0;

	UPROPERTY(EditAnywhere, Category = Parameters)
	uint16 y = 0;
};

USTRUCT(meta = (DisplayName = "Half Vector3", NiagaraInternalType = "true"))
struct FNiagaraHalfVector3
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = Parameters)
	uint16 x = 0;

	UPROPERTY(EditAnywhere, Category = Parameters)
	uint16 y = 0;

	UPROPERTY(EditAnywhere, Category = Parameters)
	uint16 z = 0;
};

USTRUCT(meta = (DisplayName = "Half Vector4", NiagaraInternalType = "true"))
struct FNiagaraHalfVector4
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = Parameters)
	uint16 x = 0;

	UPROPERTY(EditAnywhere, Category = Parameters)
	uint16 y = 0;

	UPROPERTY(EditAnywhere, Category = Parameters)
	uint16 z = 0;

	UPROPERTY(EditAnywhere, Category = Parameters)
	uint16 w = 0;
};

```

## 原理：

```cpp
#if WITH_EDITORONLY_DATA
bool FNiagaraTypeDefinition::IsInternalType() const
{
	if (const UScriptStruct* ScriptStruct = GetScriptStruct())
	{
		return ScriptStruct->GetBoolMetaData(TEXT("NiagaraInternalType"));
	}

	return false;
}
#endif
```
