# MatchedSerializers

- **功能描述：** 只在NoExportTypes.h中使用，标明采用结构序列化器。是否支持文本导入导出

- **使用位置：** UCLASS

- **引擎模块：** Serialization

- **元数据类型：** bool

- **关联项：**

  UCLASS：[MatchedSerializers](../../Specifier/UCLASS/Serialization/MatchedSerializers/MatchedSerializers.md)

- **常用程度：** 0

```cpp
if (!GetUnrealSourceFile().IsNoExportTypes())
{
	LogError(TEXT("The 'MatchedSerializers' class specifier is only valid in the NoExportTypes.h file"));
}
ParsedClassFlags |= CLASS_MatchedSerializers;
```

跟在Class中标记MatchedSerializers是等价的