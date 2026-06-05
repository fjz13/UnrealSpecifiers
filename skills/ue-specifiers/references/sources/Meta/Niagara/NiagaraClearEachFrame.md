---
title: "NiagaraClearEachFrame"
id: "meta.NiagaraClearEachFrame"
kind: "meta"
symbol: "NiagaraClearEachFrame"
category: "Niagara"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "ScriptStruct /Script/Niagara.NiagaraSpawnInfo"
usage: "USTRUCT"
---

# NiagaraClearEachFrame

## Decision Summary

- **Use when:** `NiagaraClearEachFrame` metadata 的 `USTRUCT` 场景需要：ScriptStruct /Script/Niagara.NiagaraSpawnInfo。
- **Do not use when:** 目标声明不属于 `USTRUCT`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** ScriptStruct /Script/Niagara.NiagaraSpawnInfo
- **使用位置：** USTRUCT
- **引擎模块：** Niagara
- **元数据类型：** bool
- **常用程度：** 0

指定某结构的数据在Niagara后续每一帧不应该读取，只作为初始数据。

当前只用在FNiagaraSpawnInfo上，仅仅内部用。
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。

## 源码例子：

```cpp
/** Data controlling the spawning of particles */
USTRUCT(BlueprintType, meta = (DisplayName = "Spawn Info", NiagaraClearEachFrame = "true"))
struct FNiagaraSpawnInfo
{
}
```

## 原理：

```cpp
// If the NiagaraClearEachFrame value is set on the data set, we don't bother reading it in each frame as we know that it is is invalid. However,
// this is only used for the base data set. Other reads are potentially from events and are therefore perfectly valid.
if (DataSetIndex == 0 && Var.GetType().GetScriptStruct() != nullptr && Var.GetType().GetScriptStruct()->GetMetaData(TEXT("NiagaraClearEachFrame")).Equals(TEXT("true"), ESearchCase::IgnoreCase))
{
	Fmt = VariableName + TEXT("{0} = {4};\n");
}
```
