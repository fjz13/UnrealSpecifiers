# MetaStruct

- **功能描述：** 设定到UScriptStruct*属性上，指定选择的类型的父结构。
- **使用位置：** UPROPERTY
- **引擎模块：** TypePicker
- **元数据类型：** string="abc"
- **限制类型：** UScriptStruct*
- **常用程度：** ★★★

设定到UScriptStruct*属性上，指定选择的类型的父结构。

## 测试代码：

```cpp
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaStructTest|UScriptStruct*", meta = ())
	UScriptStruct* MyStructPtr_NoMetaStruct;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaStructTest|UScriptStruct*", meta = (MetaStruct = "MyCommonStruct"))
	UScriptStruct* MyStructPtr_MetaStruct;
```

## 测试结果：

拥有MetaStruct 的可以把类型列表筛选到MyCommonStruct的子类上。

![MetaStruct](MetaStruct.jpg)

## 原理：

找到MetaStruct后设置到StructFilter上的MetaStruct ，最后进行筛选。定义了选择结构的基类。

```cpp
void SPropertyEditorStruct::Construct(const FArguments& InArgs, const TSharedPtr< class FPropertyEditor >& InPropertyEditor)
{
		const FString& MetaStructName = Property->GetOwnerProperty()->GetMetaData(TEXT("MetaStruct"));
		if (!MetaStructName.IsEmpty())
		{
						MetaStruct = UClass::TryFindTypeSlow<UScriptStruct>(MetaStructName, EFindFirstObjectOptions::EnsureIfAmbiguous);
						if (!MetaStruct)
						{
							MetaStruct = LoadObject<UScriptStruct>(nullptr, *MetaStructName);
						}
		}
}

virtual bool FPropertyEditorStructFilter::IsStructAllowed(const FStructViewerInitializationOptions& InInitOptions, const UScriptStruct* InStruct, TSharedRef<FStructViewerFilterFuncs> InFilterFuncs) override
{
	if (InStruct->IsA<UUserDefinedStruct>())
	{
		// User Defined Structs don't support inheritance, so only include them if we have don't a MetaStruct set
		return MetaStruct == nullptr;
	}

	// Query the native struct to see if it has the correct parent type (if any)
	return !MetaStruct || InStruct->IsChildOf(MetaStruct);
}
```
