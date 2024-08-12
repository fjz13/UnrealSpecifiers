# NiagaraClearEachFrame

Usage: USTRUCT
Feature: Niagara
Type: bool
Description: ScriptStruct /Script/Niagara.NiagaraSpawnInfo
Status: OnlyInternal
Group: Niagara

指定某结构的数据在Niagara后续每一帧不应该读取，只作为初始数据。

当前只用在FNiagaraSpawnInfo上，仅仅内部用。

源码例子：

```cpp
/** Data controlling the spawning of particles */
USTRUCT(BlueprintType, meta = (DisplayName = "Spawn Info", NiagaraClearEachFrame = "true"))
struct FNiagaraSpawnInfo
{
}
```

原理：

```cpp
// If the NiagaraClearEachFrame value is set on the data set, we don't bother reading it in each frame as we know that it is is invalid. However,
// this is only used for the base data set. Other reads are potentially from events and are therefore perfectly valid.
if (DataSetIndex == 0 && Var.GetType().GetScriptStruct() != nullptr && Var.GetType().GetScriptStruct()->GetMetaData(TEXT("NiagaraClearEachFrame")).Equals(TEXT("true"), ESearchCase::IgnoreCase))
{
	Fmt = VariableName + TEXT("{0} = {4};\n");
}
```