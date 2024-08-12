# AllowedTypes

Description: 为FPrimaryAssetId可以指定允许的资产类型。
Usage: UPROPERTY
Feature: Editor
Group: TypePicker
Type: strings="a，b，c"
LimitedType: FPrimaryAssetId
Status: Done

为FPrimaryAssetId可以指定允许的资产类型。

测试代码：

```cpp
UCLASS(BlueprintType)
class INSIDER_API UMyProperty_PrimaryAsset :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PrimaryAsset")
	FPrimaryAssetId MyPrimaryAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PrimaryAsset",meta=(AllowedTypes="MyAsset"))
	FPrimaryAssetId MyPrimaryAsset_Allowed;
};

```

测试结果：

在项目中已经事先定义了多个UPrimaryDataAsset，也在ProjectSettings里设置了。（如何定义请查看别的文章详解）。

可见MyPrimaryAsset_Allowed的选项只有一个了，说明受到了限制。

![Untitled](AllowedTypes/Untitled.png)

原理：

在FPrimaryAssetId 的定制化FPrimaryAssetIdCustomization中，会查看该标记，解析AllowedTypes的值并把它设置到成员变量AllowedTypes中去，最终达成筛选。

```cpp
TArray<FPrimaryAssetType> FPrimaryAssetIdCustomization::AllowedTypes;

void FPrimaryAssetIdCustomization::CustomizeHeader(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	check(UAssetManager::IsInitialized());

	StructPropertyHandle = InStructPropertyHandle;

	const FString& TypeFilterString = StructPropertyHandle->GetMetaData("AllowedTypes");
	if( !TypeFilterString.IsEmpty() )
	{
		TArray<FString> CustomTypeFilterNames;
		TypeFilterString.ParseIntoArray(CustomTypeFilterNames, TEXT(","), true);

		for(auto It = CustomTypeFilterNames.CreateConstIterator(); It; ++It)
		{
			const FString& TypeName = *It;

			AllowedTypes.Add(*TypeName);
		}
	}
	
	IAssetManagerEditorModule::MakePrimaryAssetIdSelector(
	FOnGetPrimaryAssetDisplayText::CreateSP(this, &FPrimaryAssetIdCustomization::GetDisplayText),
	FOnSetPrimaryAssetId::CreateSP(this, &FPrimaryAssetIdCustomization::OnIdSelected),
	bAllowClear, AllowedTypes, AllowedClasses, DisallowedClasses)
	
	}
```