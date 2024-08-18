# EditInlineNew

功能描述: 指定该类的对象可以在属性细节面板里直接内联创建，要和属性的Instanced配合。
引擎模块: Instance
元数据类型: bool
EClassFlagsOperation: |=
EClassFlags: CLASS_EditInlineNew (../../Flags/EClassFlags/CLASS_EditInlineNew.md)
Status: Done
Sub-item: NotEditInlineNew (NotEditInlineNew.md)
常用程度: 5

指定该类的对象可以在属性细节面板里直接内联创建。

如果想在细节面板里直接创建对象，属性上也必须先标记Instanced或ShowInnerProperties。

EditInlineNew主要是用在UObject的子类上，一般不标EditInlineNew的是用在Actor或资产的引用上。注意EditInlineNew是表明增加从属性细节面板里直接创建对象实例的能力，而非限制只能在属性细节面板里创建，当然也可以自己手动NewObject再赋值给对象引用属性。

这个跟UPROPERTY上的Instanced能力是独立的。如果UCLASS上不加EditInlineNew，但是属性上加上Instanced，则在手动NewObject赋值该属性后，该属性也会展开内部属性来提供编辑功能。因为Instanced的属性会自动的在property上加上EditInline的meta。

此说明符会传播到所有子类；子类可通过 NotEditInlineNew 说明符覆盖它。

```cpp
UCLASS(Blueprintable, EditInlineNew)
class INSIDER_API UMyClass_EditInlineNew :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyProperty;
};

UCLASS(Blueprintable, NotEditInlineNew)
class INSIDER_API UMyClass_NotEditInlineNew :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyProperty;
};

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyClass_Edit_Test :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = InstancedProperty)
		UMyClass_EditInlineNew* MyEditInlineNew;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = InstancedProperty)
		UMyClass_NotEditInlineNew* MyNotEditInlineNew;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NormalProperty)
		UMyClass_EditInlineNew* MyEditInlineNew_NotInstanced;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NormalProperty)
		UMyClass_NotEditInlineNew* MyNotEditInlineNew_NotInstanced;
};
```

示例效果：

EditInlineNew支持直接C++或BP子类创建对象实例，然后在上面编辑实例。

而NotEditInlineNew的属性则无法找到支持的类来创建对象。

如果属性上没有Instanced则只能尝试去引用（找不到对象）。

![image.png](EditInlineNew/image.png)

原理：

判断该类是否有CLASS_EditInlineNew来决定是否可内联创建编辑。

```cpp
template <typename TClass, typename TIsChildOfFunction>
bool FPropertyEditorInlineClassFilter::IsClassAllowedHelper(TClass InClass, TIsChildOfFunction IsClassChildOf, TSharedRef< FClassViewerFilterFuncs > InFilterFuncs)
{
	const bool bMatchesFlags = InClass->HasAnyClassFlags(CLASS_EditInlineNew) &&
		!InClass->HasAnyClassFlags(CLASS_Hidden | CLASS_HideDropDown | CLASS_Deprecated) &&
		(bAllowAbstract || !InClass->HasAnyClassFlags(CLASS_Abstract));
}
```