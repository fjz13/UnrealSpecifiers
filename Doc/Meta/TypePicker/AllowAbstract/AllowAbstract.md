# AllowAbstract

- **功能描述：** 用于类属性，指定是否接受抽象类。
- **使用位置：** UPARAM, UPROPERTY
- **引擎模块：** TypePicker
- **元数据类型：** bool
- **限制类型：** TSubClassOf, FSoftClassPath，UClass*
- **常用程度：** ★★

## 测试代码：

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyCommonObject :public UObject
{
	GENERATED_BODY()
};

UCLASS(BlueprintType)
class INSIDER_API UMyCommonObjectChild :public UMyCommonObject
{
	GENERATED_BODY()
};

UCLASS(BlueprintType,Abstract)
class INSIDER_API UMyCommonObjectChildAbstract :public UMyCommonObject
{
	GENERATED_BODY()
public:
};

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AllowAbstractTest")
	TSubclassOf<UMyCommonObject> MyClass_NotAllowAbstract;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AllowAbstractTest", meta = (AllowAbstract))
	TSubclassOf<UMyCommonObject> MyClass_AllowAbstract;
```

## 测试效果：

可见增加了AllowAbstract的属性的类选择器里增加了UMyCommonObjectChildAbstract 这个抽象类。

![AllowAbstract.png](AllowAbstract.png)

## 原理：

其中的一个判断是IsEditInlineClassAllowed的判断，其中有bAllowAbstract。

```cpp
bool FPropertyHandleBase::GeneratePossibleValues(TArray<FString>& OutOptionStrings, TArray< FText >& OutToolTips, TArray<bool>& OutRestrictedItems, TArray<FText>* OutDisplayNames)
{
	 if( Property->IsA(FClassProperty::StaticClass()) || Property->IsA(FSoftClassProperty::StaticClass()) )		
	{
		UClass* MetaClass = Property->IsA(FClassProperty::StaticClass()) 
			? CastFieldChecked<FClassProperty>(Property)->MetaClass
			: CastFieldChecked<FSoftClassProperty>(Property)->MetaClass;

		FString NoneStr( TEXT("None") );
		OutOptionStrings.Add( NoneStr );
		if (OutDisplayNames)
		{
			OutDisplayNames->Add(FText::FromString(NoneStr));
		}

		const bool bAllowAbstract = Property->GetOwnerProperty()->HasMetaData(TEXT("AllowAbstract"));
		const bool bBlueprintBaseOnly = Property->GetOwnerProperty()->HasMetaData(TEXT("BlueprintBaseOnly"));
		const bool bAllowOnlyPlaceable = Property->GetOwnerProperty()->HasMetaData(TEXT("OnlyPlaceable"));
		UClass* InterfaceThatMustBeImplemented = Property->GetOwnerProperty()->GetClassMetaData(TEXT("MustImplement"));

		if (!bAllowOnlyPlaceable || MetaClass->IsChildOf<AActor>())
		{
			for (TObjectIterator<UClass> It; It; ++It)
			{
				if (It->IsChildOf(MetaClass)
					&& PropertyEditorHelpers::IsEditInlineClassAllowed(*It, bAllowAbstract)
					&& (!bBlueprintBaseOnly || FKismetEditorUtilities::CanCreateBlueprintOfClass(*It))
					&& (!InterfaceThatMustBeImplemented || It->ImplementsInterface(InterfaceThatMustBeImplemented))
					&& (!bAllowOnlyPlaceable || !It->HasAnyClassFlags(CLASS_Abstract | CLASS_NotPlaceable)))
				{
					OutOptionStrings.Add(It->GetName());
					if (OutDisplayNames)
					{
						OutDisplayNames->Add(FText::FromString(It->GetName()));
					}
				}
			}
		}
	}
}

bool IsEditInlineClassAllowed( UClass* CheckClass, bool bAllowAbstract ) 
{
	return !CheckClass->HasAnyClassFlags(CLASS_Hidden|CLASS_HideDropDown|CLASS_Deprecated)
		&&	(bAllowAbstract || !CheckClass->HasAnyClassFlags(CLASS_Abstract));
}
```
