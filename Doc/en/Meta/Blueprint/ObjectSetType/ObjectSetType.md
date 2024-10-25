# ObjectSetType

- **Function Description:** Specifies the type of object collection for the statistical page.
- **Usage Location:** UCLASS
- **Engine Module:** Blueprint
- **Metadata Type:** string="abc"
- **Commonality:** ★

Specifies the type of object collection for the statistical page.

Belonging to the StatViewer module, it is used exclusively on a few specific internal classes.

## Source Code Example:

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

## Respective Effect:

On the statistical page, the type is visible in the upper right corner.

![Untitled](Untitled.png)

## Principles:

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