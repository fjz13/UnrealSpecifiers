# AllowedLocators

- **功能描述：** 用来给Sequencer定位可绑定的对象
- **使用位置：** UPROPERTY
- **引擎模块：** Scene
- **元数据类型：** string="abc"
- **限制类型：** FUniversalObjectLocator
- **常用程度：** ★

用来给Sequencer定位可绑定的对象。

看起来是Sequencer用来定位Actor做属性绑定的辅助定位器。只用在FUniversalObjectLocator 这个写好的属性里，一般我们用不到去扩展这部分，因此只是OnlyInternal。

## 源码中搜索得到：

```cpp

	// Helper struct for Binding Properties UI for locators.
USTRUCT()
struct FMovieSceneUniversalLocatorInfo
{
	GENERATED_BODY()

	// Locator for the entry
	UPROPERTY(EditAnywhere, Category = "Default", meta=(AllowedLocators="Actor"))
	FUniversalObjectLocator Locator;

	// Flags for how to resolve the locator
	UPROPERTY()
	ELocatorResolveFlags ResolveFlags = ELocatorResolveFlags::None;
};
```

看起来是允许定位的对象类型。

## 原理：

```cpp
TMap<FName, TSharedPtr<ILocatorEditor>> ApplicableLocators;

void FUniversalObjectLocatorCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
		TArray<FString> AllowedTypes;
		if (PropertyHandle->HasMetaData("AllowedLocators"))
		{
			PropertyHandle->GetMetaData("AllowedLocators").ParseIntoArray(AllowedTypes, TEXT(","));
		}
}

FUniversalObjectLocatorEditorModule& Module = FModuleManager::Get().LoadModuleChecked<FUniversalObjectLocatorEditorModule>("UniversalObjectLocatorEditor");
for (TPair<FName, TSharedPtr<ILocatorEditor>> Pair : Module.LocatorEditors)
{
	if (AllowedTypes.Num() == 0 || AllowedTypes.Contains(Pair.Key.ToString()))
	{
		ApplicableLocators.Add(Pair.Key, Pair.Value);
	}
}
```