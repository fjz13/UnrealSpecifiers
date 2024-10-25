# ClassGroup

- **Function description:** Specifies the grouping of components within the AddComponent panel in an Actor, as well as the grouping in the right-click menu of the Blueprint.
- **Engine module:** Category, Editor
- **Metadata type:** string = "a"|b|c"
- **Mechanism of action:** Adds [ClassGroupNames](../../../../Meta/DetailsPanel/ClassGroupNames.md) in the Meta data
- **Commonly used:** ★★★

Specifies the grouping of components within the AddComponent panel of an Actor, and in the right-click menu of the Blueprint.

## 1	Sample Code:

```cpp

//2	ClassGroup must be a valid BlueprintSpawnableComponent
/*
(BlueprintSpawnableComponent = , BlueprintType = true, ClassGroupNames = MyGroup|MySubGroup, IncludePath = Class/MyComponent_ClassGroup.h, IsBlueprintBase = true, ModuleRelativePath = Class/MyComponent_ClassGroup.h)
*/
UCLASS(Blueprintable,ClassGroup="MyGroup|MySubGroup", meta = (BlueprintSpawnableComponent))
class INSIDER_API UMyComponent_ClassGroup:public UActorComponent
{
	GENERATED_BODY()
public:
};
```

## 3	Example Effect:

When adding components:

![Untitled](Untitled.png)

4	Right-click "Add Component" within the blueprint. This test is applicable only to UActorComponents that include BlueprintSpawnableComponent, as it is the only component type that can be dynamically added to a blueprint.

![Untitled](Untitled%201.png)

## 5	Principle:

6	In the Metadata, ClassGroupNames are accessed via UClass::GetClassGroupNames, a method that is also employed within the BlueprintComponentNodeSpawner. Additionally, it is referenced in ComponentTypeRegistry.cpp, where it aids in component classification. Thus, the ClassGroup is exclusively utilized within the Component context.

```cpp
static FText GetDefaultMenuCategory(const TSubclassOf<UActorComponent> ComponentClass)
	{
		TArray<FString> ClassGroupNames;
		ComponentClass->GetClassGroupNames(ClassGroupNames);

if (FKismetEditorUtilities::IsClassABlueprintSpawnableComponent(Class))
				{
					TArray<FString> ClassGroupNames;
					Class->GetClassGroupNames(ClassGroupNames);
```