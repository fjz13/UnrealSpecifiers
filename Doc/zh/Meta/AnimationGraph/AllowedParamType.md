---
title: "AllowedParamType"
id: "meta.AllowedParamType"
kind: "meta"
symbol: "AllowedParamType"
category: "AnimationGraph"
source_status: "changed_in_version"
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
## UE5.8 审计结论

在本机 UE5.8 安装源码中未检索到 `AllowedParamType`，当前原始条目只引用 AnimNext 示例。本轮按 `changed_in_version` 记录，不把它路由为已确认可用的 UE5.8 metadata。
