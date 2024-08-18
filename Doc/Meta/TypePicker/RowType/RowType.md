# RowType

功能描述: 指定FDataTableRowHandle 属性的可选行类型的基类。
使用位置: UPROPERTY
Feature: Behavior
引擎模块: TypePicker
元数据类型: string="abc"
限制类型: FDataTableRowHandle
Status: Done
常用程度: 3

指定FDataTableRowHandle 属性的可选行类型的基类。

测试代码：

```cpp
USTRUCT(BlueprintType)
struct FMyCommonRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString MyString;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector MyVector;
};

UCLASS(BlueprintType)
class INSIDER_API UMyProperty_RowType :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RowTypeTest")
	FDataTableRowHandle MyRowHandle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RowTypeTest", meta = (RowType = "/Script/Insider.MyCommonRow"))
	FDataTableRowHandle MyRowHandle_RowType;
};

```

测试结果：

在编辑器中创建基于FMyCommonRow 的DataTable，即DT_MyCommonRow。当然项目里也有别的RowStruct的DataTable。

可以见到MyRowHandle_RowType的选项被限定到了DT_MyCommonRow，而且RowName也正确的显示了出来。

![Untitled](RowType/Untitled.png)

原理：

也是针对于FDataTableRowHandle这个类型进行UI的定制化，如果有该RowType数据，则赋值到RowFilterStruct ，从而完成筛选。

```cpp
void FDataTableCustomizationLayout::CustomizeHeader(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
		if (StructPropertyHandle->HasMetaData(TEXT("RowType")))
		{
			const FString& RowType = StructPropertyHandle->GetMetaData(TEXT("RowType"));
			RowTypeFilter = FName(*RowType);
			RowFilterStruct = UClass::TryFindTypeSlow<UScriptStruct>(RowType);
		}

}

bool FDataTableCustomizationLayout::ShouldFilterAsset(const struct FAssetData& AssetData)
{
	if (!RowTypeFilter.IsNone())
	{
		static const FName RowStructureTagName("RowStructure");
		FString RowStructure;
		if (AssetData.GetTagValue<FString>(RowStructureTagName, RowStructure))
		{
			if (RowStructure == RowTypeFilter.ToString())
			{
				return false;
			}

			// This is slow, but at the moment we don't have an alternative to the short struct name search
			UScriptStruct* RowStruct = UClass::TryFindTypeSlow<UScriptStruct>(RowStructure);
			if (RowStruct && RowFilterStruct && RowStruct->IsChildOf(RowFilterStruct))
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

RegisterCustomPropertyTypeLayout("DataTableRowHandle", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FDataTableCustomizationLayout::MakeInstance));

```