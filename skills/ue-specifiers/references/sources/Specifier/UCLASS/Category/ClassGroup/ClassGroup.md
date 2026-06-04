---
title: "ClassGroup"
id: "UCLASS.ClassGroup"
kind: "specifier"
symbol: "ClassGroup"
scope: "UCLASS"
category: "Category"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定组件在Actor的AddComponent面板里的分组，以及在蓝图右键菜单中的分组"
usage: "UCLASS / Category"
---

# ClassGroup

- **功能描述：**  指定组件在Actor的AddComponent面板里的分组，以及在蓝图右键菜单中的分组。
- **引擎模块：** Category, Editor
- **元数据类型：** string="a|b|c"
- **作用机制：** 在Meta中增加[ClassGroupNames](../../../../Meta/DetailsPanel/ClassGroupNames.md)
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


在蓝图中右键AddComponent，该测试只对带有BlueprintSpawnableComponent的UActorComponent起作用，因为只有BlueprintSpawnableComponent才可在蓝图中动态添加组件。


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

## 行为

UE5.8 UHT 把指定组名写入 `ClassGroupNames`，用于组件/类浏览器分组。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `UhtClassSpecifiers.cs` class specifier branch
  - UE5.8 `UhtClass.cs` class flag/metadata resolution and validation

## 常见误用

把 class specifier 的 metadata/flag 结果和 property/function specifier 混淆；或忽略继承/撤销类 specifier 的相互作用。
