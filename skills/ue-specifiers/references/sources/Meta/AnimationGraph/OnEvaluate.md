---
title: "OnEvaluate"
id: "meta.OnEvaluate"
kind: "meta"
symbol: "OnEvaluate"
category: "AnimationGraph"
source_status: "imported_from_unreal_specifiers"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "在源码中发现，说明OnEvaluate已经放弃了"
usage: "UPROPERTY"
---

# OnEvaluate

- **使用位置：** UPROPERTY
- **引擎模块：** AnimationGraph

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