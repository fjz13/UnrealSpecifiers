# BaseStruct

- **Function Description:** Specifies that the structure selected in the FInstancedStruct attribute option list must inherit from the structure referred to by BaseStruct.
- **Usage Location:** UPROPERTY
- **Engine Module:** TypePicker
- **Metadata Type:** bool
- **Restriction Type:** FInstancedStruct
- **Associated Items:** [ExcludeBaseStruct](../ExcludeBaseStruct.md), [StructTypeConst](../StructTypeConst.md)
- **Commonality:** ★★★

The structure chosen in the FInstancedStruct attribute option list must inherit from the structure indicated by BaseStruct.

## Test Code:

```cpp

USTRUCT(BlueprintType)
struct INSIDER_API FMyCommonStruct
{
}；

USTRUCT(BlueprintType)
struct INSIDER_API FMyCommonStructChild:public FMyCommonStruct
{
	GENERATED_BODY()
};

USTRUCT(BlueprintType, DisplayName = "This is MyCommonStructChild")
struct INSIDER_API FMyCommonStructChild_HasDisplayName :public FMyCommonStruct
{
	GENERATED_BODY()
};

UCLASS(BlueprintType)
class INSIDER_API UMyProperty_Struct :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InstancedStruct")
	FInstancedStruct MyStruct;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InstancedStruct", meta = (BaseStruct = "/Script/Insider.MyCommonStruct"))
	FInstancedStruct MyStruct_BaseStruct;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InstancedStruct", meta = (ExcludeBaseStruct, BaseStruct = "/Script/Insider.MyCommonStruct"))
	FInstancedStruct MyStruct_ExcludeBaseStruct;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InstancedStruct", meta = (StructTypeConst))
		FInstancedStruct MyStruct_Const;
};
```

## Test Results:

The selection of MyStruct_BaseStruct is restricted to FMyCommonStruct itself and its subclasses.

If the base class itself is not desired, MyStruct_ExcludeBaseStruct with ExcludeBaseStruct will not include FMyCommonStruct.

MyStruct_Const with StructTypeConst cannot be edited.

![Untitled](Untitled.png)

## Principle:

Extract the metadata of BaseStruct to populate the StructFilter.

```cpp

void FInstancedStructDetails::CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
		static const FName NAME_BaseStruct = "BaseStruct";
	const FString& BaseStructName = StructProperty->GetMetaData(NAME_BaseStruct);
	if (!BaseStructName.IsEmpty())
	{
		BaseScriptStruct = UClass::TryFindTypeSlow<UScriptStruct>(BaseStructName);
		if (!BaseScriptStruct)
		{
			BaseScriptStruct = LoadObject<UScriptStruct>(nullptr, *BaseStructName);
		}
	}

}

TSharedRef<SWidget> FInstancedStructDetails::GenerateStructPicker()
{
	static const FName NAME_ExcludeBaseStruct = "ExcludeBaseStruct";
	static const FName NAME_HideViewOptions = "HideViewOptions";
	static const FName NAME_ShowTreeView = "ShowTreeView";

	const bool bExcludeBaseStruct = StructProperty->HasMetaData(NAME_ExcludeBaseStruct);
	const bool bAllowNone = !(StructProperty->GetMetaDataProperty()->PropertyFlags & CPF_NoClear);
	const bool bHideViewOptions = StructProperty->HasMetaData(NAME_HideViewOptions);
	const bool bShowTreeView = StructProperty->HasMetaData(NAME_ShowTreeView);

	StructFilter->BaseStruct = BaseScriptStruct;
	StructFilter->bAllowBaseStruct = !bExcludeBaseStruct;

}

```