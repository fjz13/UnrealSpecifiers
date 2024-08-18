# ObjectSetType

功能描述: 指定统计页面的对象集合类型。
使用位置: UCLASS
Feature: Blueprint
引擎模块: Blueprint
元数据类型: string="abc"
Status: OnlyInternal
常用程度: 1

指定统计页面的对象集合类型。

属于StatViewer模块，只在固定的内部几个类上使用。

源码例子：

```cpp

/** Enum defining the object sets for this stats object */
UENUM()
enum EPrimitiveObjectSets : int
{
	PrimitiveObjectSets_AllObjects			UMETA( DisplayName = "All Objects" , ToolTip = "View primitive statistics for all objects in all levels" ),
	PrimitiveObjectSets_CurrentLevel		UMETA( DisplayName = "Current Level" , ToolTip = "View primitive statistics for objects in the current level" ),
	PrimitiveObjectSets_SelectedObjects		UMETA( DisplayName = "Selected Objects" , ToolTip = "View primitive statistics for selected objects" ),
};

/** Statistics page for primitives.  */
UCLASS(Transient, MinimalAPI, meta=( DisplayName = "Primitive Stats", ObjectSetType = "EPrimitiveObjectSets" ) )
class UPrimitiveStats : public UObject
{}
```

相应效果：

在统计页面，可见右上角的类型。

![Untitled](ObjectSetType/Untitled.png)

原理：

```cpp
template <typename Entry>
class FStatsPage : public IStatsPage
{
public:
	FStatsPage()
	{
		FString EnumName = Entry::StaticClass()->GetName();
		EnumName += TEXT(".");
		EnumName += Entry::StaticClass()->GetMetaData( TEXT("ObjectSetType") );
		ObjectSetEnum = FindObject<UEnum>( nullptr, *EnumName );
		bRefresh = false;
		bShow = false;
		ObjectSetIndex = 0;
	}
};
```