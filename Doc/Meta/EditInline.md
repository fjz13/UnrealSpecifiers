# EditInline

Description: 为对象属性创建一个实例，并作为子对象。
和类DefaultToInstanced配合。用在对象引用属性上。
在本对象创建的时候，会创建一个对象copy赋值给该对象引用属性，用做子对象。
隐含了EditInline and Export.
Usage: UPROPERTY
Feature: Behavior
Group: DetailsPanel
Type: bool
Status: Done
Related to UPROPERTY: Instanced (../../Specifier/UPROPERTY/Instanced.md)
Sub-item: NoEditInline (NoEditInline.md), AllowEditInlineCustomization (AllowEditInlineCustomization.md), ForceInlineRow (ForceInlineRow.md)

也可以手动设置。

如果UClass上有EditInlineNew，但是属性上没有Instanced，这个时候可以手动的设置EditInline然后通过自己手动赋值对象引用属性来使得这个对象可以直接编辑

和ShowInnerProperties是否等价？

EditInline在对象容器（Array,Map,Set）的情况下，也可以使用。但ShowInnerProperties只能在单个对象属性上生效。

可以设置在Struct上？看源码里也有该设置。但其实并没有效果

要特别的检测容器

蓝图效果：

![Untitled](EditInline/Untitled.png)

原理：

会相应的设置EPropertyNodeFlags::EditInlineNew。

```cpp
void FPropertyNode::InitNode(const FPropertyNodeInitParams& InitParams)
{
		// we are EditInlineNew if this property has the flag, or if inside a container that has the flag.
		bIsEditInlineNew = GotReadAddresses && bIsObjectOrInterface && !MyProperty->HasMetaData(Name_NoEditInline) && 
			(MyProperty->HasMetaData(Name_EditInline) || (bIsInsideContainer && OwnerProperty->HasMetaData(Name_EditInline)));
		bShowInnerObjectProperties = bIsObjectOrInterface && MyProperty->HasMetaData(Name_ShowInnerProperties);
		
		if (bIsEditInlineNew)
		{
			SetNodeFlags(EPropertyNodeFlags::EditInlineNew, true);
		}
		else if (bShowInnerObjectProperties)
		{
			SetNodeFlags(EPropertyNodeFlags::ShowInnerObjectProperties, true);
		}
}

bool SPropertyEditorEditInline::Supports( const FPropertyNode* InTreeNode, int32 InArrayIdx )
{
	return InTreeNode
		&& InTreeNode->HasNodeFlags(EPropertyNodeFlags::EditInlineNew)
		&& InTreeNode->FindObjectItemParent()
		&& !InTreeNode->IsPropertyConst();
}

void FItemPropertyNode::InitExpansionFlags(void)
{
	FProperty* MyProperty = GetProperty();

	if (TSharedPtr<FPropertyNode>& ValueNode = GetOrCreateOptionalValueNode())
	{
		// This is a set optional, so check its SetValue instead.
		MyProperty = ValueNode->GetProperty();
	}

	bool bExpandableType = CastField<FStructProperty>(MyProperty)
		|| (CastField<FArrayProperty>(MyProperty) || CastField<FSetProperty>(MyProperty) || CastField<FMapProperty>(MyProperty));

	if (bExpandableType
		|| HasNodeFlags(EPropertyNodeFlags::EditInlineNew)
		|| HasNodeFlags(EPropertyNodeFlags::ShowInnerObjectProperties)
		|| (MyProperty->ArrayDim > 1 && ArrayIndex == -1))
	{
		SetNodeFlags(EPropertyNodeFlags::CanBeExpanded, true);
	}
}
```