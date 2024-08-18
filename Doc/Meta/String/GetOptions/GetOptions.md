# GetOptions

功能描述: 指定一个外部类的函数提供选项给FName或FString属性在细节面板中下拉选项框提供值列表。
使用位置: UPARAM, UPROPERTY
Feature: Editor
引擎模块: String/Text Property
元数据类型: string="abc"
限制类型: FString,FName
Status: Done
Sub-item: GetKeyOptions (GetKeyOptions.md), GetValueOptions (GetValueOptions.md)
常用程度: 5

指定一个外部类的函数提供选项给FName或FString属性在细节面板中下拉选项框提供值列表。

- 只作用于FName或FString属性，FText不支持。
- 也可以用在容器上，比如TArray，TMap，TSet。
- 也可用在内部结构的变量上。这里的关键点是在寻找函数的时候，是通过找到OuterObject::Function来的，因此即使是内部结构的变量，也可以找到外部class里的函数。但如果是另外一个不相关的类，就必须用“Module.Class.Function”这种方式才能找到，否则只能返回空。
- 函数的原型是TArray<FString> FuncName() ，返回一个字符串类型，即使类型是FName，因为引擎内部会自己做转换。
- 函数可以是成员函数，有可以是静态函数。

测试代码：

```cpp
USTRUCT(BlueprintType)
struct INSIDER_API FMyOptionsTest
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta = (GetOptions = "MyGetOptions_Static"))
	FString MyString_GetOptions;

	UPROPERTY(EditAnywhere, meta = (GetOptions = "MyGetOptions_Static"))
	TArray<FString> MyArray_GetOptions;

	UPROPERTY(EditAnywhere, meta = (GetOptions = "MyGetOptions_Static"))
	TSet<FString> MySet_GetOptions;

	UPROPERTY(EditAnywhere, meta = (GetOptions = "MyGetOptions_Static"))
	TMap<FString, int32> MyMap_GetOptions;
};

UCLASS(BlueprintType)
class INSIDER_API UMyProperty_Text :public UObject
{
public:
	UPROPERTY(EditAnywhere, Category = GetOptions)
	FString MyString_NoOptions;

	UPROPERTY(EditAnywhere, Category = GetOptions, meta = (GetOptions = "MyGetOptions"))
	FString MyString_GetOptions;

	UPROPERTY(EditAnywhere, Category = GetOptions, meta = (GetOptions = "MyGetOptions"))
	FName MyName_GetOptions;

	UPROPERTY(EditAnywhere, Category = GetOptions, meta = (GetOptions = "MyGetOptions"))
	FText MyText_GetOptions;

	UPROPERTY(EditAnywhere, Category = GetOptions, meta = (GetOptions = "MyGetOptions"))
	TArray<FString> MyArray_GetOptions;

	UPROPERTY(EditAnywhere, Category = GetOptions, meta = (GetOptions = "MyGetOptions"))
	TSet<FString> MySet_GetOptions;

	UPROPERTY(EditAnywhere, Category = GetOptions, meta = (GetOptions = "MyGetOptions"))
	TMap<FString, int32> MyMap_GetOptions;

	UFUNCTION()
	static TArray<FString> MyGetOptions_Static() { return TArray<FString>{"Cat", "Dog"}; }

	UFUNCTION()
	TArray<FString> MyGetOptions() { return TArray<FString>{"First", "Second", "Third"}; }
public:
	UPROPERTY(EditAnywhere, Category = GetOptionsStruct)
	FMyOptionsTest MyStruct_GetOptions;
public:
	UPROPERTY(EditAnywhere, Category = GetKeyValueOptions, meta = (GetKeyOptions = "MyGetOptions",GetValueOptions="MyGetOptions_Static"))
	TMap<FString, FName> MyMap_GetKeyValueOptions;
}
```

测试效果：

根据下图，可见FText并没有起作用。其他带有GetOptions标记的在细节面板上都有一个下拉选项框。

而另外当使用TMap的时候，还可以用GetKeyOptions 和GetValueOptions来分别单独为Key和Value提供不一样的选项列表，见MyMap_GetKeyValueOptions。

![Untitled](GetOptions/Untitled.png)

原理：

大致流程是用GetPropertyOptionsMetaDataKey来判断一个属性是否支持选项框编辑，然后通过

GetPropertyOptions调用指定的函数来获得选项列表，最后根据这个列表的值BuildComboBoxWidget。

```cpp
	void PropertyEditorUtils::GetPropertyOptions(TArray<UObject*>& InOutContainers, FString& InOutPropertyPath,
		TArray<TSharedPtr<FString>>& InOutOptions)
	{
		// Check for external function references
		if (InOutPropertyPath.Contains(TEXT(".")))
		{
			InOutContainers.Empty();
			UFunction* GetOptionsFunction = FindObject<UFunction>(nullptr, *InOutPropertyPath, true);

			if (ensureMsgf(GetOptionsFunction && GetOptionsFunction->HasAnyFunctionFlags(EFunctionFlags::FUNC_Static), TEXT("Invalid GetOptions: %s"), *InOutPropertyPath))
			{
				UObject* GetOptionsCDO = GetOptionsFunction->GetOuterUClass()->GetDefaultObject();
				GetOptionsFunction->GetName(InOutPropertyPath);
				InOutContainers.Add(GetOptionsCDO);
			}
		}

		if (InOutContainers.Num() > 0)
		{
			TArray<FString> OptionIntersection;
			TSet<FString> OptionIntersectionSet;

			for (UObject* Target : InOutContainers)
			{
				TArray<FString> StringOptions;
				{
					FEditorScriptExecutionGuard ScriptExecutionGuard;

					FCachedPropertyPath Path(InOutPropertyPath);
					if (!PropertyPathHelpers::GetPropertyValue(Target, Path, StringOptions))
					{
						TArray<FName> NameOptions;
						if (PropertyPathHelpers::GetPropertyValue(Target, Path, NameOptions))
						{
							Algo::Transform(NameOptions, StringOptions, [](const FName& InName) { return InName.ToString(); });
						}
					}
				}

				// If this is the first time there won't be any options.
				if (OptionIntersection.Num() == 0)
				{
					OptionIntersection = StringOptions;
					OptionIntersectionSet = TSet<FString>(StringOptions);
				}
				else
				{
					TSet<FString> StringOptionsSet(StringOptions);
					OptionIntersectionSet = StringOptionsSet.Intersect(OptionIntersectionSet);
					OptionIntersection.RemoveAll([&OptionIntersectionSet](const FString& Option){ return !OptionIntersectionSet.Contains(Option); });
				}

				// If we're out of possible intersected options, we can stop.
				if (OptionIntersection.Num() == 0)
				{
					break;
				}
			}

			Algo::Transform(OptionIntersection, InOutOptions, [](const FString& InString) { return MakeShared<FString>(InString); });
		}
	}
	
FName GetPropertyOptionsMetaDataKey(const FProperty* Property)
{
	// Only string and name properties can have options
	if (Property->IsA(FStrProperty::StaticClass()) || Property->IsA(FNameProperty::StaticClass()))
	{
		const FProperty* OwnerProperty = Property->GetOwnerProperty();
		static const FName GetOptionsName("GetOptions");
		if (OwnerProperty->HasMetaData(GetOptionsName))
		{
			return GetOptionsName;
		}

		// Map properties can have separate options for keys and values
		const FMapProperty* MapProperty = CastField<FMapProperty>(OwnerProperty);
		if (MapProperty)
		{
			static const FName GetKeyOptionsName("GetKeyOptions");
			if (MapProperty->HasMetaData(GetKeyOptionsName) && MapProperty->GetKeyProperty() == Property)
			{
				return GetKeyOptionsName;
			}

			static const FName GetValueOptionsName("GetValueOptions");
			if (MapProperty->HasMetaData(GetValueOptionsName) && MapProperty->GetValueProperty() == Property)
			{
				return GetValueOptionsName;
			}
		}
	}

	return NAME_None;
}

TSharedPtr<SWidget> SGraphPinString::TryBuildComboBoxWidget()
{
		PropertyEditorUtils::GetPropertyOptions(PropertyContainers, GetOptionsFunctionName, ComboBoxOptions);
}
```