# GetAllowedClasses

功能描述: 用在类或对象选择器上，通过一个函数来指定选择的对象必须属于某一些类型基类。
使用位置: UPROPERTY
Feature: Editor
引擎模块: TypePicker
元数据类型: string="abc"
限制类型: TSubClassOf，UClass*，UObject*，FSoftObjectPath
Example: meta=(GetAllowedClasses="FuncName").
Status: Done
Code: TArray<UClass*> FuncName() const;
Parent item: AllowedClasses (AllowedClasses.md)
常用程度: 2

AllowedClass是用直接指定类名字字符串的方式来限定基类。而GetAllowedClasses就更近一步，允许通过一个函数来返回筛选的基类。动态和自定义的灵活性就更高了。

当然GetAllowedClasses不如AllowedClass支持那么多属性类型，只支持：TSubClassOf，UClass*，UObject*，FSoftObjectPath

测试代码：

```cpp
public:
	UFUNCTION()
	TArray<UClass*> MyGetAllowedClassesFunc()
	{
			TArray<UClass*> classes;
			classes.Add(UMyCommonObject::StaticClass());
			classes.Add(UTexture2D::StaticClass());
			classes.Add(UMyPrimaryDataAsset::StaticClass());
			
			return classes;
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GetAllowedClassesTest|TSubclassOf")
	TSubclassOf<UObject> MyClass_NoGetAllowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GetAllowedClassesTest|TSubclassOf", meta = (GetAllowedClasses = "MyGetAllowedClassesFunc"))
	TSubclassOf<UObject> MyClass_GetAllowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GetAllowedClassesTest|UClass*")
	UClass* MyClassPtr_NoGetAllowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GetAllowedClassesTest|UClass*", meta = (GetAllowedClasses = "MyGetAllowedClassesFunc"))
	UClass* MyClassPtr_GetAllowedClasses;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GetAllowedClassesTest|FSoftObjectPath")
	UObject* MyObject_NoGetAllowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GetAllowedClassesTest|FSoftObjectPath", meta = (GetAllowedClasses = "MyGetAllowedClassesFunc"))
	UObject* MyObject_GetAllowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GetAllowedClassesTest|FSoftObjectPath")
	FSoftObjectPath MySoftObject_NoGetAllowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GetAllowedClassesTest|FSoftObjectPath", meta = (GetAllowedClasses = "MyGetAllowedClassesFunc"))
	FSoftObjectPath MySoftObject_GetAllowedClasses;
```

测试效果：

可见Class选择器把可选范围限定到了设定的3个基类上。而对象选择器也把对象限定到了这3个基类。

![GetAllowClasses.jpg](GetAllowedClasses/GetAllowClasses.jpg)

## 原理：

通过源码发现，可以应用的属性只有SPropertyEditorClass和SPropertyEditorAsset，而这其实对应着Class类型（没有FSoftClassPath）和对应UObject的Asset类型（FSoftObjectPath对应SPropertyEditorAsset）

```cpp
void SPropertyEditorAsset::InitializeClassFilters(const FProperty* Property)
{
		PropertyEditorUtils::GetAllowedAndDisallowedClasses(ObjectList, *MetadataProperty, AllowedClassFilters, DisallowedClassFilters, bExactClass, ObjectClass);
}

void SPropertyEditorClass::Construct(const FArguments& InArgs, const TSharedPtr< FPropertyEditor >& InPropertyEditor)
{
		PropertyEditorUtils::GetAllowedAndDisallowedClasses(ObjectList, *Property, AllowedClassFilters, DisallowedClassFilters, false);
}

TSharedRef<SWidget> SPropertyEditorEditInline::GenerateClassPicker()
{
		PropertyEditorUtils::GetAllowedAndDisallowedClasses(ObjectList, *Property, AllowedClassFilters, DisallowedClassFilters, false);
}

void PropertyEditorUtils::GetAllowedAndDisallowedClasses(const TArray<UObject*>& ObjectList, const FProperty& MetadataProperty, TArray<const UClass*>& AllowedClasses, TArray<const UClass*>& DisallowedClasses, bool bExactClass, const UClass* ObjectClass)
{
	AllowedClasses = PropertyCustomizationHelpers::GetClassesFromMetadataString(MetadataProperty.GetOwnerProperty()->GetMetaData("AllowedClasses"));
	DisallowedClasses = PropertyCustomizationHelpers::GetClassesFromMetadataString(MetadataProperty.GetOwnerProperty()->GetMetaData("DisallowedClasses"));
	
	bool bMergeAllowedClasses = !AllowedClasses.IsEmpty();

	if (MetadataProperty.GetOwnerProperty()->HasMetaData("GetAllowedClasses"))
	{
		const FString GetAllowedClassesFunctionName = MetadataProperty.GetOwnerProperty()->GetMetaData("GetAllowedClasses");
	}

	if (MetadataProperty.GetOwnerProperty()->HasMetaData("GetDisallowedClasses"))
	{
		const FString GetDisallowedClassesFunctionName = MetadataProperty.GetOwnerProperty()->GetMetaData("GetDisallowedClasses");
		if (!GetDisallowedClassesFunctionName.IsEmpty())
		{
			for (UObject* Object : ObjectList)
			{
				const UFunction* GetDisallowedClassesFunction = Object ? Object->FindFunction(*GetDisallowedClassesFunctionName) : nullptr;
				if (GetDisallowedClassesFunction)
				{
					DECLARE_DELEGATE_RetVal(TArray<UClass*>, FGetDisallowedClasses);
					DisallowedClasses.Append(FGetDisallowedClasses::CreateUFunction(Object, GetDisallowedClassesFunction->GetFName()).Execute());
				}
			}
		}
	}
}
```