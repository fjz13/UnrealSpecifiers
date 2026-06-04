---
title: "Hidden"
id: "meta.Enum.UMETA.Hidden"
kind: "meta"
symbol: "Hidden"
scope: "UMETA"
category: "Enum"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "隐藏UENUM的某个值"
usage: "UENUM::UMETA"
---

# Hidden

- **功能描述：** 隐藏UENUM的某个值
- **使用位置：** UENUM::UMETA
- **引擎模块：** Enum Property
- **元数据类型：** bool
- **限制类型：** UENUM的值
- **常用程度：** ★★★★★

隐藏UENUM的某个值。
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。

## 测试代码：

```cpp

UENUM(Blueprintable,BlueprintType)
enum class EMyEnum_Spacer_Hidden :uint8
{
	MyNormal,
	MySpacer UMETA(Spacer),
	MyHidden UMETA(Hidden),
};

UCLASS(BlueprintType)
class INSIDER_API UMyEnum_Test :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	EMyEnum_Spacer_Hidden MyEnum_Spacer_Hidden;
};
```

## 测试效果：

![Untitled](5b4de771-be09-4342-8955-dc0f824ef97d.png)

但是蓝图里访问：

![Untitled](Untitled.png)

## 原理：

在属性细节面板里生成枚举可能的值的时候，会判断Hidden和Spacer选项来隐藏。

但是在SEnumComboBox和SGraphPinEnum这种在蓝图里显示的时候，只会判断Hidden，而没有（忘了？）判断Spacer，因此MySpacer是依然会被显示出来。

```cpp
bool FPropertyHandleBase::GeneratePossibleValues(TArray<FString>& OutOptionStrings, TArray< FText >& OutToolTips, TArray<bool>& OutRestrictedItems, TArray<FText>* OutDisplayNames)
{
		// Ignore hidden enums
	bool bShouldBeHidden = Enum->HasMetaData(TEXT("Hidden"), EnumIndex ) || Enum->HasMetaData(TEXT("Spacer"), EnumIndex );
	if (!bShouldBeHidden)
	{
		if(ValidEnumValues.Num() > 0)
		{
			bShouldBeHidden = !ValidEnumValues.Contains(Enum->GetNameByIndex(EnumIndex));
		}
		// If both are specified, InvalidEnumValues takes precedence
		else if(InvalidEnumValues.Num() > 0)
		{
			bShouldBeHidden = InvalidEnumValues.Contains(Enum->GetNameByIndex(EnumIndex));
		}
	}
}

void SEnumComboBox::Construct(const FArguments& InArgs, const UEnum* InEnum)
{
		if (Enum->HasMetaData(TEXT("Hidden"), Index) == false)
		{
			VisibleEnums.Emplace(Index, Enum->GetValueByIndex(Index), Enum->GetDisplayNameTextByIndex(Index), Enum->GetToolTipTextByIndex(Index));
		}
}

void SGraphPinEnum::GenerateComboBoxIndexes( TArray< TSharedPtr<int32> >& OutComboBoxIndexes )
{
	// Ignore hidden enum values
	if( !EnumPtr->HasMetaData(TEXT("Hidden"), EnumIndex ) )
	{
		TSharedPtr<int32> EnumIdxPtr(new int32(EnumIndex));
		OutComboBoxIndexes.Add(EnumIdxPtr);
	}
}
```