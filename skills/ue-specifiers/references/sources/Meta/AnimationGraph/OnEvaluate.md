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

## Decision Summary

- **Use when:** 迁移、诊断或阅读旧代码时需要识别 `OnEvaluate`。
- **Do not use when:** 不要在新的 UE5.8 代码中把它作为常规方案。
- **Requires:** 确认目标代码确实依赖旧版本或兼容路径，并阅读正文的版本说明。
- **Conflicts:** 与当前 UE5.8 推荐写法冲突时，以当前引擎行为为准。
- **Prefer instead:** 新代码优先使用正文或索引中指向的当前替代项。

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
