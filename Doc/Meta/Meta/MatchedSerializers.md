# MatchedSerializers

Usage: UCLASS
Feature: Behavior
Type: bool
Description: 只在NoExportTypes.h中使用，标明采用结构序列化器。是否支持文本导入导出
Status: Linked
Group: Serialization

```cpp
if (!GetUnrealSourceFile().IsNoExportTypes())
{
	LogError(TEXT("The 'MatchedSerializers' class specifier is only valid in the NoExportTypes.h file"));
}
ParsedClassFlags |= CLASS_MatchedSerializers;
```

跟在Class中标记MatchedSerializers是等价的