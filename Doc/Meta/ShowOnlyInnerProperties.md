# ShowOnlyInnerProperties

Description: 把结构属性的内部属性直接上提一个层级直接展示
Usage: UPROPERTY
Feature: Editor
Type: bool
LimitedType: FStruct属性
Status: Done
Parent item: ShowInnerProperties (ShowInnerProperties.md)

把结构属性的内部属性直接上提一个层级直接展示，而不是像默认一样归属于一个可展开的父级结构。

测试代码：

```cpp
UPROPERTY(EditAnywhere, BlueprintReadWrite)
FMyPropertyInner InnerStruct;

UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ShowOnlyInnerProperties))
FMyPropertyInner InnerStruct_ShowOnlyInnerProperties;
```

效果对比：

![Untitled](ShowOnlyInnerProperties/Untitled.png)

可以发现InnerStruct_ShowOnlyInnerProperties的内部属性直接就显示在对象的当前层级上，而InnerStruct的属性有一个结构名称作为Category来展开。

## 原理：

在遇见FStructProperty的时候，会开始判断ShowOnlyInnerProperties来决定是否要创建一个可展开的Category，或者还是直接把内部属性展示出来。有了ShowOnlyInnerProperties，就会直接递归迭代到其内部属性。

```cpp
void DetailLayoutHelpers::UpdateSinglePropertyMapRecursive(FPropertyNode& InNode, FName CurCategory, FComplexPropertyNode* CurObjectNode, FUpdatePropertyMapArgs& InUpdateArgs)
{
		static FName ShowOnlyInners("ShowOnlyInnerProperties");
		// Whether or not to push out struct properties to their own categories or show them inside an expandable struct
		// This recursively applies for any nested structs that have the ShowOnlyInners metadata 
		const bool bPushOutStructProps = bIsStruct && !bIsCustomizedStruct && Property->HasMetaData(ShowOnlyInners);
		
		if (bRecurseIntoChildren || LocalUpdateFavoriteSystemOnly)
		{
						// Built in struct properties or children of arras 
						UpdateSinglePropertyMapRecursive(ChildNode, CurCategory, CurObjectNode, ChildArgs);
		}

}

void FObjectPropertyNode::GetCategoryProperties(const TSet<UClass*>& ClassesToConsider, const FProperty* CurrentProperty, bool bShouldShowDisableEditOnInstance, bool bShouldShowHiddenProperties,
	const TSet<FName>& CategoriesFromBlueprints, TSet<FName>& CategoriesFromProperties, TArray<FName>& SortedCategories)
	{
			if (CurrentProperty->HasMetaData(Name_ShowOnlyInnerProperties))
			{
				const FStructProperty* StructProperty = CastField<const FStructProperty>(CurrentProperty);
				if (StructProperty)
				{
					for (TFieldIterator<FProperty> It(StructProperty->Struct); It; ++It)
					{
						GetCategoryProperties(ClassesToConsider, *It, bShouldShowDisableEditOnInstance, bShouldShowHiddenProperties, CategoriesFromBlueprints, CategoriesFromProperties, SortedCategories);
					}
				}
			}
			
}
```