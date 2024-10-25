# EditInline

- **功能描述：** 为对象属性创建一个实例，并作为子对象。

- **使用位置：** UPROPERTY

- **引擎模块：** DetailsPanel

- **元数据类型：** bool

- **关联项：** [NoEditInline](../NoEditInline.md), [AllowEditInlineCustomization](../AllowEditInlineCustomization/AllowEditInlineCustomization.md), [ForceInlineRow](../ForceInlineRow/ForceInlineRow.md)

  UPROPERTY：[Instanced](../../../Specifier/UPROPERTY/Instance/Instanced/Instanced.md)

- **常用程度：** ★★★

为对象属性创建一个实例，并作为子对象。

也可以手动设置。如果UClass上有EditInlineNew，但是属性上没有Instanced，这个时候可以手动的设置EditInline然后通过自己手动赋值对象引用属性来使得这个对象可以直接编辑。

和ShowInnerProperties是否等价？EditInline在对象容器（Array,Map,Set）的情况下，也可以使用。但ShowInnerProperties只能在单个对象属性上生效。

可以设置在Struct上？看源码里也有该设置。但其实并没有效果。

## 示例代码：

```cpp
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMyProperty_EditInline_Sub* MyObject;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditInline))
	UMyProperty_EditInline_Sub* MyObject_EditInline;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (NoEditInline))
	UMyProperty_EditInline_Sub* MyObject_NoEditInline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UMyProperty_EditInline_Sub*> MyObjectArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditInline))
	TArray<UMyProperty_EditInline_Sub*> MyObjectArray_EditInline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (NoEditInline))
	TArray<UMyProperty_EditInline_Sub*> MyObjectArray_NoEditInline;
```

## 蓝图效果：

![Untitled](Untitled.png)

## 原理：

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