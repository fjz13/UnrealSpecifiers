# NoElementDuplicate

功能描述: 去除TArray属性里数据项的Duplicate菜单项按钮。
使用位置: UPROPERTY
Feature: Editor
引擎模块: Container Property
元数据类型: bool
限制类型: TArray
Status: Done
常用程度: 1

去除TArray属性里数据项的Duplicate菜单项按钮。

用于TArray属性，值可以是任何类型，可以是数值，结构，也可以是Object*。

测试代码：

```cpp
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = IntArray)
	TArray<int32> MyIntArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = IntArray, meta = (NoElementDuplicate))
	TArray<int32> MyIntArray_NoElementDuplicate;
```

效果：

可以看到带有NoElementDuplicate的数组，在值的右侧下拉箭头的菜单项里只有两项。

![Untitled](NoElementDuplicate/Untitled.png)

## 原理：

判断如有NoElementDuplicate，则只生成Insert_Delete 菜单，否则是默认的Insert_Delete_Duplicate 。当然要求当前属性是数组属性，且不是EditFixedSize固定大小的。

```cpp
void GetRequiredPropertyButtons( TSharedRef<FPropertyNode> PropertyNode, TArray<EPropertyButton::Type>& OutRequiredButtons, bool bUsingAssetPicker )
{
		const FArrayProperty* OuterArrayProp = NodeProperty->GetOwner<FArrayProperty>();
		
		if( OuterArrayProp )
		{
			if( PropertyNode->HasNodeFlags(EPropertyNodeFlags::SingleSelectOnly) && !(OuterArrayProp->PropertyFlags & CPF_EditFixedSize) )
			{
				if (OuterArrayProp->HasMetaData(TEXT("NoElementDuplicate")))
				{
					OutRequiredButtons.Add( EPropertyButton::Insert_Delete );
				}
				else
				{
					OutRequiredButtons.Add( EPropertyButton::Insert_Delete_Duplicate );
				}
			}
		}
}
```