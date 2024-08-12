# AllowedClasses

Description: 用在类或对象选择器上，指定选择的对象必须属于某一些类型基类。
Usage: UPROPERTY
Feature: Editor
Group: TypePicker
Type: strings="a，b，c"
LimitedType: TSubClassOf，UClass*，FSoftClassPath，UObject*，FSoftObjectPath，FPrimaryAssetId，FComponentReference,
Example: AllowedClasses="Class1, Class2, ..”
Status: Done
Sub-item: ExactClass (ExactClass.md), DisallowedClasses (DisallowedClasses.md), GetAllowedClasses (GetAllowedClasses.md), GetDisallowedClasses (GetDisallowedClasses.md)

用在类或对象选择器上，指定选择的对象必须属于某一些类型基类。

- 类选择器的应用属性是：TSubClassOf，UClass*，FSoftClassPath。不能应用的属性是：UScriptStruct*
- 对象选择器的应用属性是：UObject*， FSoftObjectPath，FPrimaryAssetId，FComponentReference
- 这些选择器往往会显示出一大串对象资源来供选择，因此就可以用AllowedClasses来限定其必须属于的类型。
- AllowedClasses里可以用逗号隔开多个类型，因此可以同时支持多个类型筛选。

测试代码：

```cpp
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AllowedClassesTest|TSubclassOf")
	TSubclassOf<UObject> MyClass_NoAllowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AllowedClassesTest|TSubclassOf", meta = (AllowedClasses = "MyCommonObject"))
	TSubclassOf<UObject> MyClass_AllowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AllowedClassesTest|UClass*")
	UClass* MyClassPtr_NoAllowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AllowedClassesTest|UClass*", meta = (AllowedClasses = "MyCommonObject"))
	UClass* MyClassPtr_AllowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AllowedClassesTest|FSoftClassPath")
	FSoftClassPath MySoftClass_NoAllowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AllowedClassesTest|FSoftClassPath", meta = (AllowedClasses = "MyCommonObject"))
	FSoftClassPath MySoftClass_AllowedClasses;

	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AllowedClassesTest|FSoftObjectPath")
	UObject* MyObject_NoAllowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AllowedClassesTest|FSoftObjectPath", meta = (AllowedClasses = "/Script/Engine.Texture2D"))
	UObject* MyObject_AllowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AllowedClassesTest|FSoftObjectPath")
	FSoftObjectPath MySoftObject_NoAllowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AllowedClassesTest|FSoftObjectPath", meta = (AllowedClasses = "/Script/Engine.Texture2D"))
	FSoftObjectPath MySoftObject_AllowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AllowedClassesTest|FPrimaryAssetId")
	FPrimaryAssetId MyPrimaryAsset_NoAllowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AllowedClassesTest|FPrimaryAssetId", meta = (AllowedClasses = "MyPrimaryDataAsset"))
	FPrimaryAssetId MyPrimaryAsset_AllowedClasses;
	
	
UCLASS(Blueprintable,BlueprintType)
class INSIDER_API AMyActor_Class :public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AllowedClassesTest|FComponentReference", meta = (UseComponentPicker))
	FComponentReference MyComponentReference_NoAllowedClasses;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AllowedClassesTest|FComponentReference", meta = (UseComponentPicker,AllowedClasses = "MyActorComponent"))
	FComponentReference MyComponentReference_AllowedClasses;
};

UCLASS(BlueprintType)
class INSIDER_API UMyPrimaryDataAsset :public UPrimaryDataAsset
{}
```

测试结果：

- 在类选择器上，可见加了AllowedClasses 之后，就限定到MyCommonObject的子类上。
- 在对象选择器上，加上了AllowedClasses = "/Script/Engine.Texture2D"之后，就把类型限定到纹理上。
- 在FPrimaryAssetId 属性的资产筛选上，加了AllowedClasses 之后，可以限定到MyPrimaryDataAsset类型，图上是BP_MyPrimaryAsset。注意一下UMyPrimaryDataAsset 需要在ProjectSettings里设置上。

![AllowClasses.jpg](AllowedClasses/AllowClasses.jpg)

测试FComponentReference的效果：

结合上述代码，可见默认情况下，FComponentReference可选择的范围是当前Actor下所有Component。而加上AllowedClasses后，可以把选择的范围限定到代码里描述的MyActorComponent。

![AllowClasses_ComponentReference.jpg](AllowedClasses/AllowClasses_ComponentReference.jpg)

## 原理：

在源码里搜索可见，往往在各种类型的Customization或SPropertyEditorXXX上，会进行AllowedClasses 和DisallowedClasses 的判断，之后再对类型进行IsChildOf的Filter筛选。

```cpp
void FPrimaryAssetIdCustomization::CustomizeHeader(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	AllowedClasses = PropertyCustomizationHelpers::GetClassesFromMetadataString(StructPropertyHandle->GetMetaData("AllowedClasses"));
	DisallowedClasses = PropertyCustomizationHelpers::GetClassesFromMetadataString(StructPropertyHandle->GetMetaData("DisallowedClasses"));
}
void FComponentReferenceCustomization::BuildClassFilters()
{
		const FString& AllowedClassesFilterString = PropertyHandle->GetMetaData(NAME_AllowedClasses);
		ParseClassFilters(AllowedClassesFilterString, AllowedActorClassFilters, AllowedComponentClassFilters);

		const FString& DisallowedClassesFilterString = PropertyHandle->GetMetaData(NAME_DisallowedClasses);
		ParseClassFilters(DisallowedClassesFilterString, DisallowedActorClassFilters, DisallowedComponentClassFilters);
}
void FSoftClassPathCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
		TArray<const UClass*> AllowedClasses = PropertyCustomizationHelpers::GetClassesFromMetadataString(PropertyHandle->GetMetaData("AllowedClasses"));
		TArray<const UClass*> DisallowedClasses = PropertyCustomizationHelpers::GetClassesFromMetadataString(PropertyHandle->GetMetaData("DisallowedClasses"));
}

void PropertyEditorUtils::GetAllowedAndDisallowedClasses(const TArray<UObject*>& ObjectList, const FProperty& MetadataProperty, TArray<const UClass*>& AllowedClasses, TArray<const UClass*>& DisallowedClasses, bool bExactClass, const UClass* ObjectClass)
{
		AllowedClasses = PropertyCustomizationHelpers::GetClassesFromMetadataString(MetadataProperty.GetOwnerProperty()->GetMetaData("AllowedClasses"));
		DisallowedClasses = PropertyCustomizationHelpers::GetClassesFromMetadataString(MetadataProperty.GetOwnerProperty()->GetMetaData("DisallowedClasses"));
		if (MetadataProperty.GetOwnerProperty()->HasMetaData("GetAllowedClasses"))
		{
			const FString GetAllowedClassesFunctionName = MetadataProperty.GetOwnerProperty()->GetMetaData("GetAllowedClasses");
		}
		
		if (MetadataProperty.GetOwnerProperty()->HasMetaData("GetDisallowedClasses"))
		{
			const FString GetDisallowedClassesFunctionName = MetadataProperty.GetOwnerProperty()->GetMetaData("GetDisallowedClasses");
		}
}

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
```