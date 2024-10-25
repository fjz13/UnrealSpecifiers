# ForceShowEngineContent

- **功能描述：** 指定UObject*属性的资源可选列表里强制可选引擎的内建资源
- **使用位置：** UPROPERTY
- **引擎模块：** Asset Property
- **元数据类型：** bool
- **限制类型：** UObject*
- **关联项：** [ForceShowPluginContent](ForceShowPluginContent.md)
- **常用程度：** ★★

指定UObject*属性的资源可选列表里强制可选引擎的内建资源。

## 测试代码：

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyProperty_ShowContent :public UDataAsset
{
public:
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Object)
	TObjectPtr<UObject> MyAsset_Default;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Object, meta = (ForceShowEngineContent))
	TObjectPtr<UObject> MyAsset_ForceShowEngineContent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Object, meta = (ForceShowPluginContent))
	TObjectPtr<UObject> MyAsset_ForceShowPluginContent;
};
```

## 测试结果：

可见MyAsset_Default默认是只包含本项目的资源。

MyAsset_ForceShowEngineContent的作用其实就是在选项卡里勾选ShowEngineContent，因此结果上会发现多了非常多的可选资源。

MyAsset_ForceShowPluginContent的作用同样是在选项卡里勾选ShowPluginContent，可以选择别的插件里的资源。

![Untitled](Untitled.png)

## 原理：

在属性的资源选择器里会尝试寻找ForceShowEngineContent和ForceShowPluginContent，然后设置到AssetPickerConfig里，从而改变资源的可选类型。

```cpp
void SPropertyMenuAssetPicker::Construct( const FArguments& InArgs )
{
		const bool bForceShowEngineContent = PropertyHandle ? PropertyHandle->HasMetaData(TEXT("ForceShowEngineContent")) : false;
		const bool bForceShowPluginContent = PropertyHandle ? PropertyHandle->HasMetaData(TEXT("ForceShowPluginContent")) : false;

		FAssetPickerConfig AssetPickerConfig;
		// Force show engine content if meta data says so
		AssetPickerConfig.bForceShowEngineContent = bForceShowEngineContent;
		// Force show plugin content if meta data says so
		AssetPickerConfig.bForceShowPluginContent = bForceShowPluginContent;
}
```