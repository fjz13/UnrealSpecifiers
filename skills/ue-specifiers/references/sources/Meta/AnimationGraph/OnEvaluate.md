---
title: "OnEvaluate"
id: "meta.OnEvaluate"
kind: "meta"
symbol: "OnEvaluate"
category: "AnimationGraph"
source_status: "removed_or_deprecated"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "UE5.8 AnimBlueprintExtension_Base.cpp 仍读取 OnEvaluate metadata，但同一代码路径会输出 “OnEvaluate meta data is deprecated” 警告；因此该条目保留"
usage: "UPROPERTY"
---

# OnEvaluate

- **使用位置：** UPROPERTY
- **引擎模块：** AnimationGraph
## UE5.8 审计结论

UE5.8 `AnimBlueprintExtension_Base.cpp` 仍读取 `OnEvaluate` metadata，但同一代码路径会输出 “OnEvaluate meta data is deprecated” 警告；因此该条目保留为兼容/历史说明，不建议新代码使用。

## 原理：

在源码中发现，说明OnEvaluate已经放弃了。

```cpp
// Dynamic value that needs to be wired up and evaluated each frame
	const FString& EvaluationHandlerStr = SourcePinProperty->GetMetaData(AnimGraphDefaultSchema->NAME_OnEvaluate);
	FName EvaluationHandlerName(*EvaluationHandlerStr);
	if (EvaluationHandlerName != NAME_None)
	{
		// warn that NAME_OnEvaluate is deprecated:
		InCompilationContext.GetMessageLog().Warning(*LOCTEXT("OnEvaluateDeprecated", "OnEvaluate meta data is deprecated, found on @@").ToString(), SourcePinProperty);
	}
```