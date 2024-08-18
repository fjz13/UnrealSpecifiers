# AutoExpandCategories

功能描述: 指定此类的对象在细节面板中应该自动展开的Category。
引擎模块: Category
元数据类型: strings=(abc，"d|e"，"x|y|z")
Example: AutoExpandCategories=(Category1, Category2, ...)
MetaOperation: +=&-=
Meta: AutoCollapseCategories (../../Meta/Meta/AutoCollapseCategories.md), AutoExpandCategories (../../Meta/Meta/AutoExpandCategories.md)
Status: Done
Sub-item: AutoCollapseCategories (AutoCollapseCategories.md)
常用程度: 1

指定此类的对象在细节面板中应该自动展开的Category。

- 这里面的Category可以填多个，对应本类中属性身上定义的Category。
- 值得注意的是，编辑器会自动的保存属性目录的展开关闭状态。影响属性是否展开，还会受到DetailPropertyExpansion的配置的影响，在打开窗口后，SDetailsViewBase::UpdateFilteredDetails()会保存当前展开的属性项目，应该是为了下次打开的时候自动展开。保存的代码为GConfig->SetSingleLineArray(TEXT("DetailPropertyExpansion"), *Struct->GetName(), ExpandedPropertyItems, GEditorPerProjectIni); 从而在\Hello\Saved\Config\WindowsEditor\EditorPerProjectUserSettings.ini下保存。因此为了更好的测试该元数据的作用状态。应该手动先清除一下ini中的保存值后再测试。

```cpp
[DetailCategories]
MyClass_AutoExpandCategories.MyClass_AutoExpandCategories=False
MyClass_AutoExpandCategories.MyGroup1=False
MyClass_AutoExpandCategories.MyGroup2=False
MyClass_AutoExpandCategories.MyGroup3=True
MyClass_AutoExpandCategories.MyGroup4=True

[DetailPropertyExpansion]
GeometryCache="\"Object.GeometryCache.Materials\" \"Object.GeometryCache.Tracks\" "
Object="\"Object.MyGroup2.MyGroup2|MyGroup22\" \"Object.MyGroup4.MyGroup4|MyGroup44\" \"Object.MyGroup4.MyGroup4|MyGroup44.MyGroup4|MyGroup44|MyGroup444\" "
GeometryCacheCodecV1="\"Object.GeometryCache.TopologyRanges\" "
GeometryCacheCodecBase="\"Object.GeometryCache.TopologyRanges\" "
MassSettings="\"Object.Mass\" "
DeveloperSettings=
SmartObjectSettings="\"Object.SmartObject\" "
MyClass_ShowCategories=
MyClass_ShowCategoriesChild=
MyClass_DontCollapseCategories="\"Object.MyGroup2.MyGroup2|MyGroup22\" \"Object.MyGroup3.MyGroup3|MyGroup33\" \"Object.MyGroup3.MyGroup3|MyGroup33.MyGroup3|MyGroup33|MyGroup333\" "
MyClass_CollapseCategories="\"Object.MyGroup2.MyGroup2|MyGroup22\" \"Object.MyGroup3.MyGroup3|MyGroup33\" \"Object.MyGroup3.MyGroup3|MyGroup33.MyGroup3|MyGroup33|MyGroup333\" "
MyClass_AutoExpandCategories="\"Object.MyGroup2.MyGroup2|MyGroup22\" \"Object.MyGroup4.MyGroup4|MyGroup44\" \"Object.MyGroup4.MyGroup4|MyGroup44.MyGroup4|MyGroup44|MyGroup444\" "
MyClass_AutoExpandCategoriesCompare=
MyClass_AutoCollapseCategories="\"Object.MyGroup2.MyGroup2|MyGroup22\" \"Object.MyGroup4.MyGroup4|MyGroup44\" \"Object.MyGroup4.MyGroup4|MyGroup44.MyGroup4|MyGroup44|MyGroup444\" "
```

根据代码搜索规则，AutoExpandCategories 和AutoCollapseCategories的值要用空格隔开。顶层目录一开始默认就是打开的，所以AutoExpandCategories 一般用在子层目录。而且还有个限制是必须一级一级都打开。直接打开最子目录还不行。因此在示例代码里必须要把中间的二级目录"MyGroup4|MyGroup44"也都得写上。

示例代码：

```cpp
UCLASS(Blueprintable, AutoExpandCategories = ("MyGroup2|MyGroup22", "MyGroup4|MyGroup44","MyGroup4|MyGroup44|MyGroup444"))
class INSIDER_API UMyClass_AutoExpandCategories :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Property_NotInGroup;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyGroup1")
		int Property_Group1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyGroup2")
		int Property_Group2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyGroup2|MyGroup22")
		int Property_Group22;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyGroup3|MyGroup33")
		int Property_Group33;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyGroup4|MyGroup44|MyGroup444")
		int Property_Group444;
};

源码里最复杂的样例：
UCLASS(Config = Engine, PerObjectConfig, BlueprintType, AutoCollapseCategories = ("Data Layer|Advanced"), AutoExpandCategories = ("Data Layer|Editor", "Data Layer|Advanced|Runtime"))
class ENGINE_API UDataLayerInstance : public UObject

可以打开子目录：UCLASS(Blueprintable, AutoExpandCategories = ("MyGroup2|MyGroup22", "MyGroup4|MyGroup44","MyGroup4|MyGroup44|MyGroup444"))
不可以打开子目录：UCLASS(Blueprintable, AutoExpandCategories = ("MyGroup2|MyGroup22", "MyGroup4|MyGroup44|MyGroup444"))
```

示例效果：

在Saved\EditorPerProjectUserSettings中删除掉DetailCategories以及DetailPropertyExpansion下的MyClass_AutoCollapseCategories值之后再用testprops class=MyClass_AutoExpandCategories来打开该窗口：

通过对比可以看出Expand确实可以自动展开子目录方便立马编辑。要求是AutoExpandCategories 里填的目录要和属性上的Category匹配

![Untitled](AutoExpandCategories/Untitled.png)

原理：

UClass里提取AutoExpandCategories和AutoCollapseCategories的元数据来判断Category是否应该显示。

```cpp
if (BaseClass->IsAutoExpandCategory(*CategoryName.ToString())		&&	!BaseClass->IsAutoCollapseCategory(*CategoryName.ToString()))
	{
		NewCategoryNode->SetNodeFlags(EPropertyNodeFlags::Expanded, true);
	}

bool UClass::IsAutoExpandCategory(const TCHAR* InCategory) const
{
	static const FName NAME_AutoExpandCategories(TEXT("AutoExpandCategories"));
	if (const FString* AutoExpandCategories = FindMetaData(NAME_AutoExpandCategories))
	{
		return !!FCString::StrfindDelim(**AutoExpandCategories, InCategory, TEXT(" "));
	}
	return false;
}

bool UClass::IsAutoCollapseCategory(const TCHAR* InCategory) const
{
	static const FName NAME_AutoCollapseCategories(TEXT("AutoCollapseCategories"));
	if (const FString* AutoCollapseCategories = FindMetaData(NAME_AutoCollapseCategories))
	{
		return !!FCString::StrfindDelim(**AutoCollapseCategories, InCategory, TEXT(" "));
	}
	return false;
}

```