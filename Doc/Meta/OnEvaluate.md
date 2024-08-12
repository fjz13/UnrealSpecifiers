# OnEvaluate

Usage: UPROPERTY
Feature: Blueprint
Group: AnimationGraph
Status: Invalid

原理：

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