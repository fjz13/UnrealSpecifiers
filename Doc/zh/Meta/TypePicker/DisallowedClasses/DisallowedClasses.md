# DisallowedClasses

- **功能描述：** 用在类或对象选择器上，指定选择的对象排除掉某一些类型基类。
- **使用位置：** UPROPERTY
- **引擎模块：** TypePicker
- **元数据类型：** strings="a，b，c"
- **限制类型：** TSubClassOf，UClass*，FSoftClassPath，FComponentReference
- **关联项：** [AllowedClasses](../AllowedClasses/AllowedClasses.md)
- **常用程度：** ★★★

用在类或对象选择器上，指定选择的对象排除掉某一些类型基类。

- 类选择器的应用属性是：TSubClassOf，UClass*，FSoftClassPath。不能应用的属性是：UScriptStruct*
- 对象选择器的应用属性是：FComponentReference。会发现相比AllowedClasses少了“UObject*， FSoftObjectPath，FPrimaryAssetId”，这是因为这3个对应的UI是SAssetPicker，而这个里面并没有应用FARFilter.RecursiveClassPathsExclusionSet来进行排除。

## 测试代码：

```cpp
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DisallowedClassesTest|TSubclassOf")
	TSubclassOf<UObject> MyClass_NoDisallowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DisallowedClassesTest|TSubclassOf", meta = (DisallowedClasses = "/Script/GameplayAbilities.AbilityAsync"))
	TSubclassOf<UObject> MyClass_DisallowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DisallowedClassesTest|UClass*")
	UClass* MyClassPtr_NoDisallowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DisallowedClassesTest|UClass*", meta = (DisallowedClasses = "/Script/GameplayAbilities.AbilityAsync"))
	UClass* MyClassPtr_DisallowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DisallowedClassesTest|FSoftClassPath")
	FSoftClassPath MySoftClass_NoDisallowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DisallowedClassesTest|FSoftClassPath", meta = (DisallowedClasses = "/Script/GameplayAbilities.AbilityAsync"))
	FSoftClassPath MySoftClass_DisallowedClasses;
public://Not work
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DisallowedClassesTest|FSoftObjectPath")
	UObject* MyObject_NoDisallowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DisallowedClassesTest|FSoftObjectPath", meta = (DisallowedClasses = "/Script/Engine.Texture2D"))
	UObject* MyObject_DisallowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DisallowedClassesTest|FSoftObjectPath")
	FSoftObjectPath MySoftObject_NoDisallowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DisallowedClassesTest|FSoftObjectPath", meta = (DisallowedClasses = "/Script/Engine.Texture2D"))
	FSoftObjectPath MySoftObject_DisallowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DisallowedClassesTest|FPrimaryAssetId")
	FPrimaryAssetId MyPrimaryAsset_NoDisallowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DisallowedClassesTest|FPrimaryAssetId", meta = (DisallowedClasses = "MyPrimaryDataAsset"))
	FPrimaryAssetId MyPrimaryAsset_DisallowedClasses;

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyActor_Class :public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "DisallowedClassesTest|FComponentReference", meta = (UseComponentPicker))
	FComponentReference MyComponentReference_NoDisallowedClasses;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "DisallowedClassesTest|FComponentReference", meta = (UseComponentPicker, DisallowedClasses = "MyActorComponent"))
	FComponentReference MyComponentReference_DisallowedClasses;
};

```

## 测试效果：

- 在类选择器上，可见加了DisallowedClasses 之后，就排除掉了AbilityAsync类。
- 而在对象选择器上，却没必要发生作用。二者的可选对象列表是一样的。原因是因为SAssetPicker并没有实际上应用DisallowedClasses 。

![DisallowedClasses](DisallowedClasses.jpg)

而在FComponentReference上的测试效果是：

DisallowedClasses可以排除掉MyActorComponent。

![DisallowedClasses_ComponentReference](DisallowedClasses_ComponentReference.jpg)

## 原理：

主要的原理已经在AllowedClasses上展示出来。DisallowedClasses的数据主要是设置到DisallowedClassFilters里面去。之后在创建ClassViewer的时候设定到ClassFilter上，最后其实还是IsChildOf的判断。但也要注意并不是所有的类和对象选择器都有使用DisallowedClasses，AssetPicker上就并没有实现。

```cpp
	TSharedRef<FPropertyEditorClassFilter> PropEdClassFilter = MakeShared<FPropertyEditorClassFilter>();
	PropEdClassFilter->ClassPropertyMetaClass = MetaClass;
	PropEdClassFilter->InterfaceThatMustBeImplemented = RequiredInterface;
	PropEdClassFilter->bAllowAbstract = bAllowAbstract;
	PropEdClassFilter->AllowedClassFilters = AllowedClassFilters;
	PropEdClassFilter->DisallowedClassFilters = DisallowedClassFilters;

	ClassViewerOptions.ClassFilters.Add(PropEdClassFilter);

	ClassFilter = FModuleManager::LoadModuleChecked<FClassViewerModule>("ClassViewer").CreateClassFilter(ClassViewerOptions);


template <typename TClass>
bool FPropertyEditorClassFilter::IsClassAllowedHelper(TClass InClass)
{
	bool bMatchesFlags = !InClass->HasAnyClassFlags(CLASS_Hidden | CLASS_HideDropDown | CLASS_Deprecated) &&
		(bAllowAbstract || !InClass->HasAnyClassFlags(CLASS_Abstract));

	if (bMatchesFlags && InClass->IsChildOf(ClassPropertyMetaClass)
		&& (!InterfaceThatMustBeImplemented || InClass->ImplementsInterface(InterfaceThatMustBeImplemented)))
	{
		auto PredicateFn = [InClass](const UClass* Class)
		{
			return InClass->IsChildOf(Class);
		};

		if (DisallowedClassFilters.FindByPredicate(PredicateFn) == nullptr &&
			(AllowedClassFilters.Num() == 0 || AllowedClassFilters.FindByPredicate(PredicateFn) != nullptr))
		{
			return true;
		}
	}

	return false;
}

void SAssetPicker::Construct( const FArguments& InArgs )
{
	if (InArgs._AssetPickerConfig.bAddFilterUI)
	{
		// We create available classes here. These are used to hide away the type filters in the filter list that don't match this list of classes
		TArray<UClass*> FilterClassList;
		for(auto Iter = CurrentBackendFilter.ClassPaths.CreateIterator(); Iter; ++Iter)
		{
			FTopLevelAssetPath ClassName = (*Iter);
			UClass* FilterClass = FindObject<UClass>(ClassName);
			if(FilterClass)
			{
				FilterClassList.AddUnique(FilterClass);
			}
		}
}
```