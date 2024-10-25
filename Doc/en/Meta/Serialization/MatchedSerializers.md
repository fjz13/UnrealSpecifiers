# MatchedSerializers

- **Function Description:** Used exclusively in NoExportTypes.h to denote the employment of a structured serializer. Indicates support for text-based import and export functionality

- **Usage Location:** UCLASS

- **Engine Module:** Serialization

- **Metadata Type:** Boolean

- **Associated Items:**

  UCLASS: [MatchedSerializers](../../Specifier/UCLASS/Serialization/MatchedSerializers/MatchedSerializers.md)

- **Commonality:** 0

```cpp
if (!GetUnrealSourceFile().IsNoExportTypes())
{
	LogError(TEXT("The 'MatchedSerializers' class specifier is only valid in the NoExportTypes.h file"));
}
ParsedClassFlags |= CLASS_MatchedSerializers;
```

Marking MatchedSerializers in a class is equivalent in effect