# MetaClass

Usage: UPROPERTY
Feature: Editor
Type: string="abc"
Description: 用在软引用属性上，限定要选择的对象的基类
LimitedType: FSoftClassPath，FSoftObjectPath
Status: Done
Group: TypePicker

用在软引用属性上，限定要选择的资源的基类。

软引用属性指的是FSoftClassPath和FSoftObjectPath，这类属性本身并没有像TSubClassOf一样本身的类型限制，因此可以额外的加MetaClass来限制要选择的对象的所属于的基类。

MetaClass里的值也可以是"/Script/Engine.Actor”这种ObjectPath。

## 测试代码：

```cpp
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaClassTest|TSubclassOf")
TSubclassOf<UObject> MyClass_NotMetaClass;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaClassTest|TSubclassOf", meta = (MetaClass = "MyCommonObject"))
TSubclassOf<UObject> MyClass_MetaClass;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaClassTest|FSoftClassPath")
FSoftClassPath MySoftClass_NotMetaClass;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaClassTest|FSoftClassPath", meta = (MetaClass = "MyCommonObject"))
FSoftClassPath MySoftClass_MetaClass;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaClassTest|FSoftClassPath", meta = (MetaClass = "MyCommonObject"))
TSoftClassPtr<UObject> MySoftClassPtrT_MetaClass;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaClassTest|UClass*")
UClass* MyClassPtr_NotMetaClass;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaClassTest|UClass*", meta = (MetaClass = "MyCommonObject"))
UClass* MyClassPtr_MetaClass;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaClassTest|FSoftObjectPath")
FSoftObjectPath MySoftObject_NotMetaClass;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaClassTest|FSoftObjectPath", meta = (MetaClass = "MyCustomAsset"))
FSoftObjectPath MySoftObject_MetaClass;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaClassTest|FSoftObjectPath", meta = (MetaClass = "MyCustomAsset"))
TSoftObjectPtr<UObject> MySoftObjectPtrT_MetaClass;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaClassTest|UScriptStruct*")
UScriptStruct* MyStructPtr_NotMetaClass;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaClassTest|UScriptStruct*", meta = (MetaClass="MyCommonStruct"))
UScriptStruct* MyStructPtr_MetaClass;
```

## 测试效果：

测试效果，只有MySoftClass_MetaClass和MySoftObject_MetaClass的选择列表里进行了筛选。

![MetaClass.jpg](MetaClass/MetaClass.jpg)

## 原理：

在源码里搜索，发现FSoftClassPath和FSoftObjectPath都有进行类型定制化，根据MetaClass分别设定到SClassPropertyEntryBox和SObjectPropertyEntryBox的MetaClass和AllowedClass上。

发现TSoftObjectPtr和TSoftClassPtr并没有进行定制化，因此没有支持该功能。UScriptStruct*本身也不支持该功能，虽然也是选择类型。

```cpp
void FSoftClassPathCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	const FString& MetaClassName = PropertyHandle->GetMetaData("MetaClass");
	const FString& RequiredInterfaceName = PropertyHandle->GetMetaData("RequiredInterface"); // This was the old name, switch to MustImplement to synchronize with class property
	const FString& MustImplementName = PropertyHandle->GetMetaData("MustImplement");
	TArray<const UClass*> AllowedClasses = PropertyCustomizationHelpers::GetClassesFromMetadataString(PropertyHandle->GetMetaData("AllowedClasses"));
	TArray<const UClass*> DisallowedClasses = PropertyCustomizationHelpers::GetClassesFromMetadataString(PropertyHandle->GetMetaData("DisallowedClasses"));
	const bool bAllowAbstract = PropertyHandle->HasMetaData("AllowAbstract");
	const bool bIsBlueprintBaseOnly = PropertyHandle->HasMetaData("IsBlueprintBaseOnly") || PropertyHandle->HasMetaData("BlueprintBaseOnly");
	const bool bAllowNone = !(PropertyHandle->GetMetaDataProperty()->PropertyFlags & CPF_NoClear);
	const bool bShowTreeView = PropertyHandle->HasMetaData("ShowTreeView");
	const bool bHideViewOptions = PropertyHandle->HasMetaData("HideViewOptions");
	const bool bShowDisplayNames = PropertyHandle->HasMetaData("ShowDisplayNames");

	const UClass* const MetaClass = !MetaClassName.IsEmpty()
	? FEditorClassUtils::GetClassFromString(MetaClassName)
	: UObject::StaticClass();
	
	SNew(SClassPropertyEntryBox)
	.MetaClass(MetaClass)
	
	}
	
void FSoftObjectPathCustomization::CustomizeHeader( TSharedRef<IPropertyHandle> InStructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils )
{
	const FString& MetaClassName = InStructPropertyHandle->GetMetaData("MetaClass");
	UClass* MetaClass = !MetaClassName.IsEmpty()
		? FEditorClassUtils::GetClassFromString(MetaClassName)
		: UObject::StaticClass();
	TSharedRef<SObjectPropertyEntryBox> ObjectPropertyEntryBox = SNew(SObjectPropertyEntryBox)
		.AllowedClass(MetaClass)
		.PropertyHandle(InStructPropertyHandle)
		.ThumbnailPool(StructCustomizationUtils.GetThumbnailPool());
}
```