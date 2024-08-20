# ClassGroup

- **功能描述：** 指定组件在Actor的AddComponent面板里的分组，以及在蓝图右键菜单中的分组。
- **引擎模块：**Category, Editor
- **元数据类型：**string="a|b|c"
- **作用机制：**在Meta中增加[ClassGroupNames](../../../../Meta/DetailsPanel/ClassGroupNames.md)
- **常用程度：★★★**

指定组件在Actor的AddComponent面板里的分组，以及在蓝图右键菜单中的分组。

## 示例代码：

```cpp

//ClassGroup 必须是BlueprintSpawnableComponent才有效
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

## 示例效果：

在添加组件的时候：

![Untitled](Untitled.png)

在蓝图中右键AddComponent，该测试只对带有BlueprintSpawnableComponent的UActorComponent起作用，因为只有BlueprintSpawnableComponent才可在蓝图中动态添加组件。

![Untitled](Untitled%201.png)

## 原理：

Metadata中的ClassGroupNames，被使用方法是UClass::GetClassGroupNames，这个又是在BlueprintComponentNodeSpawner中被使用。还有一个使用地方是ComponentTypeRegistry.cpp中，也是在判断Component。因此这个ClassGroup确实是只被Component使用的。

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