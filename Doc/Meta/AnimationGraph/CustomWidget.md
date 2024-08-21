# CustomWidget

- **使用位置：** UFUNCTION, UPROPERTY
- **引擎模块：** AnimationGraph
- **元数据类型：** string="abc"

也可以放在属性上

```cpp
// @param    Scope    Scopes corresponding to an existing scope in a schedule, or "None". Passing "None" will apply the parameter to the whole schedule.
// @param    Ordering Where to apply the parameter in relation to the supplied scope. Ignored for scope "None".
// @param    Name     The name of the parameter to apply
// @param    Value    The value to set the parameter to
UFUNCTION(BlueprintCallable, Category = "AnimNext", CustomThunk, meta = (CustomStructureParam = Value, UnsafeDuringActorConstruction))
void SetParameterInScope(UPARAM(meta = (CustomWidget = "ParamName", AllowedParamType = "FAnimNextScope")) FName Scope, EAnimNextParameterScopeOrdering Ordering, UPARAM(meta = (CustomWidget = "ParamName")) FName Name, int32 Value);
```

只在AnimNext和RigVM里用到。
