# HideViewOptions

- **功能描述：** 用于选择Class或Struct的属性上，隐藏在类选取器中修改显示选项的功能。
- **使用位置：** UPROPERTY
- **引擎模块：** TypePicker
- **元数据类型：** bool
- **限制类型：** TSubClassOf，FSoftClassPath，UClass*，UScriptStruct*，FInstancedStruct 
- **常用程度：** ★

用于选择Class或Struct的属性上，隐藏在类选取器中修改显示选项的功能。

应用的属性类型有TSubClassOf，FSoftClassPath，UClass*，UScriptStruct*，FInstancedStruct 这种用于选择类型的属性。如果是TSoftObjectPtr或者FSoftObjectPath这种用于选择对象的则不起作用。

## 测试代码：

```cpp
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HideViewOptionsTest|TSubclassOf")
	TSubclassOf<UObject> MyClass_NotHideViewOptions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HideViewOptionsTest|TSubclassOf", meta = (HideViewOptions))
	TSubclassOf<UObject> MyClass_HideViewOptions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HideViewOptionsTest|UClass*")
	UClass* MyClassPtr_NotHideViewOptions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HideViewOptionsTest|UClass*", meta = (HideViewOptions))
	UClass* MyClassPtr_HideViewOptions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HideViewOptionsTest|FSoftClassPath")
	FSoftClassPath MySoftClass_NotHideViewOptions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HideViewOptionsTest|FSoftClassPath", meta = (HideViewOptions))
	FSoftClassPath MySoftClass_HideViewOptions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HideViewOptionsTest|UScriptStruct*")
	UScriptStruct* MyStructPtr_NotHideViewOptions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HideViewOptionsTest|UScriptStruct*", meta = (HideViewOptions))
	UScriptStruct* MyStructPtr_HideViewOptions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HideViewOptionsTest|FInstancedStruct")
	FInstancedStruct MyInstancedStruct_NotHideViewOptions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HideViewOptionsTest|FInstancedStruct", meta = (HideViewOptions))
	FInstancedStruct MyInstancedStruct_HideViewOptions;
```

## 测试效果：

可见如果没有HideViewOptions，则在弹出框的角落有个齿轮或者眼睛用于修改显示选项。

![HideViewOptions.jpg](HideViewOptions.jpg)

## 原理：

在源码中对于TSubClassOf和UClass*有SPropertyEditorClass，对于FSoftClassPath有FSoftClassPathCustomization，对于UScriptStruct*有SPropertyEditorStruct，对于FInstancedStruct 有FInstancedStructDetails来进行UI定制化。

```cpp
void FSoftClassPathCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
		const bool bShowTreeView = PropertyHandle->HasMetaData("ShowTreeView");
		const bool bHideViewOptions = PropertyHandle->HasMetaData("HideViewOptions");
		
	SNew(SClassPropertyEntryBox)
		.ShowTreeView(bShowTreeView)
		.HideViewOptions(bHideViewOptions)
		.ShowDisplayNames(bShowDisplayNames)
}

void SPropertyEditorClass::Construct(const FArguments& InArgs, const TSharedPtr< FPropertyEditor >& InPropertyEditor)
{
		bShowViewOptions = Property->GetOwnerProperty()->HasMetaData(TEXT("HideViewOptions")) ? false : true;
		bShowTree = Property->GetOwnerProperty()->HasMetaData(TEXT("ShowTreeView"));
		bShowDisplayNames = Property->GetOwnerProperty()->HasMetaData(TEXT("ShowDisplayNames"));
}
void SPropertyEditorStruct::Construct(const FArguments& InArgs, const TSharedPtr< class FPropertyEditor >& InPropertyEditor)
{
		bShowViewOptions = Property->GetOwnerProperty()->HasMetaData(TEXT("HideViewOptions")) ? false : true;
		bShowTree = Property->GetOwnerProperty()->HasMetaData(TEXT("ShowTreeView"));
		bShowDisplayNames = Property->GetOwnerProperty()->HasMetaData(TEXT("ShowDisplayNames"));
}
TSharedRef<SWidget> FInstancedStructDetails::GenerateStructPicker()
{
		const bool bExcludeBaseStruct = StructProperty->HasMetaData(NAME_ExcludeBaseStruct);
		const bool bAllowNone = !(StructProperty->GetMetaDataProperty()->PropertyFlags & CPF_NoClear);
		const bool bHideViewOptions = StructProperty->HasMetaData(NAME_HideViewOptions);
		const bool bShowTreeView = StructProperty->HasMetaData(NAME_ShowTreeView);
}
```
