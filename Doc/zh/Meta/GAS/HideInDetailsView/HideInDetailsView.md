# HideInDetailsView

- **功能描述：** 把该UAttributeSet子类里的属性隐藏在FGameplayAttribute的选项列表里。
- **使用位置：** UCLASS, UPROPERTY
- **引擎模块：** GAS
- **元数据类型：** bool
- **限制类型：** UAttributeSet
- **关联项：** [HideFromModifiers](../HideFromModifiers/HideFromModifiers.md), [SystemGameplayAttribute](../SystemGameplayAttribute/SystemGameplayAttribute.md)
- **常用程度：** ★★★

把该UAttributeSet子类里的属性隐藏在FGameplayAttribute的选项列表里。

可用在UCLASS上隐藏掉整个类里的所有属性，也可以用在某个特定属性上只隐藏该属性。

在源码里用到的例子是UAbilitySystemTestAttributeSet，因为其就是一个专门用来测试的AS，因此希望不影响正常的选项列表。

## 测试代码：

```cpp
UCLASS()
class UMyAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core")
	float HP = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core", meta = (HideInDetailsView))
	float HP_HideInDetailsView = 100.f;
};

UCLASS(meta = (HideInDetailsView))
class UMyAttributeSet_Hide : public UAttributeSet
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core")
	float HP = 100.f;
};

UCLASS()
class UMyAttributeSetTest : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GAS")
	FGameplayAttribute MyAttribute;
};
```

## 测试效果：

可见只能选到UMyAttributeSet.HP属性，无法选择到UMyAttributeSet_Hide里的选项。

![Untitled](Untitled.png)

## 原理：

```cpp
PropertyModule.RegisterCustomPropertyTypeLayout( "GameplayAttribute", FOnGetPropertyTypeCustomizationInstance::CreateStatic( &FAttributePropertyDetails::MakeInstance ) );

void FGameplayAttribute::GetAllAttributeProperties(TArray<FProperty*>& OutProperties, FString FilterMetaStr, bool UseEditorOnlyData)
{
	for (TObjectIterator<UClass> ClassIt; ClassIt; ++ClassIt)
	{
		if (UseEditorOnlyData)
		{
			#if WITH_EDITOR
			// Allow entire classes to be filtered globally
			if (Class->HasMetaData(TEXT("HideInDetailsView")))
			{
				continue;
			}
			#endif
		}


			for (TFieldIterator<FProperty> PropertyIt(Class, EFieldIteratorFlags::ExcludeSuper); PropertyIt; ++PropertyIt)
			{
				FProperty* Property = *PropertyIt;

				if (UseEditorOnlyData)
				{
					// Allow properties to be filtered globally (never show up)
					if (Property->HasMetaData(TEXT("HideInDetailsView")))
					{
						continue;
					}
					#endif
				}

				OutProperties.Add(Property);
			}
	}
}
```