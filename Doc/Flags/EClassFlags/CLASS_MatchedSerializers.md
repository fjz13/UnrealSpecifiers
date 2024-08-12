# CLASS_MatchedSerializers

Value: 0x00000020u
Feature: LoadConstruct
Status: Done
Trait: DefaultC++, Internal
UCLASS: UCLASS() (../../Specifier/UCLASS/UCLASS().md), 不写UCLASS() (../../Specifier/UCLASS/%E4%B8%8D%E5%86%99UCLASS().md), MatchedSerializers (../../Specifier/UCLASS/MatchedSerializers.md)

在UClass::IsSafeToSerializeToStructuredArchives中被使用，只在NoExportTypes.h中使用，标明采用结构序列化器。是否支持文本导入导出，只在编辑器情况下使用。