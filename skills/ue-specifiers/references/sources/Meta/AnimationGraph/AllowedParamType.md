---
title: "AllowedParamType"
id: "meta.AllowedParamType"
kind: "meta"
symbol: "AllowedParamType"
category: "AnimationGraph"
source_status: "imported_from_unreal_specifiers"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "// Sets a parameter's value in the supplied scope."
usage: "UFUNCTION"
---

# AllowedParamType

- **使用位置：** UFUNCTION
- **引擎模块：** AnimationGraph
- **元数据类型：** string="abc"

```cpp
// Sets a parameter's value in the supplied scope.
// @param    Scope    Scopes corresponding to an existing scope in a schedule, or "None". Passing "None" will apply the parameter to the whole schedule.
// @param    Ordering Where to apply the parameter in relation to the supplied scope. Ignored for scope "None".
// @param    Name     The name of the parameter to apply
// @param    Value    The value to set the parameter to
UFUNCTION(BlueprintCallable, Category = "AnimNext", CustomThunk, meta = (CustomStructureParam = Value, UnsafeDuringActorConstruction))
void SetParameterInScope(UPARAM(meta = (CustomWidget = "ParamName", AllowedParamType = "FAnimNextScope")) FName Scope, EAnimNextParameterScopeOrdering Ordering, UPARAM(meta = (CustomWidget = "ParamName")) FName Name, int32 Value);
```

查了一下，只在AnimNext中用到。