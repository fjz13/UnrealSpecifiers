# HiddenNode

功能描述: 把指定的UBTNode隐藏不在右键菜单中显示。
使用位置: UCLASS
Feature: Blueprint
引擎模块: Blueprint
元数据类型: bool
限制类型: UBTNode
Status: Done
常用程度: 1

把指定的UBTNode隐藏不在右键菜单中显示。

测试代码：

```cpp

UCLASS(MinimalAPI,meta = ())
class UMyBT_NotHiddenNode : public UBTDecorator
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(Category = Node, EditAnywhere)
	float MyFloat;
};

UCLASS(MinimalAPI,meta = (HiddenNode))
class UMyBT_HiddenNode : public UBTDecorator
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(Category = Node, EditAnywhere)
	float MyFloat;
};

```

测试结果：

可见只有UMyBT_NotHiddenNode 显示了出来，而UMyBT_HiddenNode 被隐藏了。

![Untitled](HiddenNode/Untitled.png)

原理：

原理比较简单，就是坚持元数据标记，然后设置bIsHidden 。

```cpp
bool FGraphNodeClassHelper::IsHidingClass(UClass* Class)
{
	static FName MetaHideInEditor = TEXT("HiddenNode");

	return 
		Class && 
		((Class->HasAnyClassFlags(CLASS_Native) && Class->HasMetaData(MetaHideInEditor))
		|| ForcedHiddenClasses.Contains(Class));
}

//D:\github\UnrealEngine\Engine\Source\Editor\AIGraph\Private\AIGraphTypes.cpp
void FGraphNodeClassHelper::BuildClassGraph()
{
		for (TObjectIterator<UClass> It; It; ++It)
		{
			UClass* TestClass = *It;
			if (TestClass->HasAnyClassFlags(CLASS_Native) && TestClass->IsChildOf(RootNodeClass))
			{
				
				NewData.bIsHidden = IsHidingClass(TestClass);
		
				NewNode->Data = NewData;
		
				if (TestClass == RootNodeClass)
				{
					RootNode = NewNode;
				}
		
				NodeList.Add(NewNode);
			}
		}
}
```