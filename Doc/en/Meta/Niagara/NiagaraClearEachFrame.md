# NiagaraClearEachFrame

- **Function Description:** ScriptStruct /Script/Niagara.NiagaraSpawnInfo
- **Usage Location:** USTRUCT
- **Engine Module:** Niagara
- **Metadata Type:** bool
- **Commonality:** Rarely Used

Specifies that the data of a certain structure should not be read in each subsequent frame of Niagara, serving only as initial data.

Currently applied exclusively to FNiagaraSpawnInfo, for internal use only.

## Source Code Example:

```cpp
/** Data controlling the spawning of particles */
USTRUCT(BlueprintType, meta = (DisplayName = "Spawn Info", NiagaraClearEachFrame = "true"))
struct FNiagaraSpawnInfo
{
}
```

## Principle: The Fundamental Concept

```cpp
// If the NiagaraClearEachFrame value is set on the data set, we don't bother reading it in each frame as we know that it is is invalid. However,
// this is only used for the base data set. Other reads are potentially from events and are therefore perfectly valid.
if (DataSetIndex == 0 && Var.GetType().GetScriptStruct() != nullptr && Var.GetType().GetScriptStruct()->GetMetaData(TEXT("NiagaraClearEachFrame")).Equals(TEXT("true"), ESearchCase::IgnoreCase))
{
	Fmt = VariableName + TEXT("{0} = {4};\n");
}
```