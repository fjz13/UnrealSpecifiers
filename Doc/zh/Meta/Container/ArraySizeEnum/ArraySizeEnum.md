# ArraySizeEnum

- **功能描述：** 为固定数组提供一个枚举，使得数组元素按照枚举值来作为索引和显示。
- **使用位置：** UPROPERTY
- **引擎模块：** Container Property
- **元数据类型：** string="abc"
- **限制类型：** T Array[Size]
- **常用程度：** ★★★

为固定数组提供一个枚举，使得数组元素按照枚举值来作为索引和显示。

- 所谓固定数组，是区别于TArray这种可以动态改变大小的数组，而是平凡的用[size]直接定义的数组。这种固定数组（static array）因为不会增删，因此才有时适合用枚举里的所有值用作下标，达成更高的便利性。
- 枚举里一般会把最后一个枚举项（一般叫做Max或者Size，count之类）作为数据大小值。
- 枚举里不想显示的枚举值可以用Hidden隐藏起来，但因为数组下标对应的是枚举项的下标（就是第几个枚举值）而不是枚举项的值，因此会发现数组的实际显示项目比定义的Size要小。

## 测试代码：

```cpp
UENUM(BlueprintType)
enum class EMyArrayEnumNormal :uint8
{
	First,
	Second,
	Third,
	Max,
};

UENUM(BlueprintType)
enum class EMyArrayEnumHidden :uint8
{
	First,
	Second,
	Cat = 5 UMETA(Hidden),
	Third = 2,
	Max = 3,
};

UPROPERTY(EditAnywhere, Category = ArraySizeEnumTest)
int32 MyIntArray_NoArraySizeEnum[3];

UPROPERTY(EditAnywhere, Category = ArraySizeEnumTest, meta = (ArraySizeEnum = "MyArrayEnumNormal"))
int32 MyIntArray_Normal_HasArraySizeEnum[(int)EMyArrayEnumNormal::Max];

UPROPERTY(EditAnywhere, Category = ArraySizeEnumTest, meta = (ArraySizeEnum = "MyArrayEnumHidden"))
int32 MyIntArray_Hidden_HasArraySizeEnum[(int)EMyArrayEnumHidden::Max];
```

## 测试效果：

都是大小为3的固定数组。

- MyIntArray_NoArraySizeEnum，是最普通的数组模样。
- MyIntArray_Normal_HasArraySizeEnum，正统的使用枚举项来当数组下标的例子。可以发现下标名字不是012，而是枚举项名称了。
- MyIntArray_Hidden_HasArraySizeEnum采用的枚举项里有隐藏的一项Cat，但它的下标是2（因为定义的顺序），因此数组的第3个被隐藏了起来。

![Untitled](Untitled.png)

## 原理：

可以发现一开始判断是否是固定数组（ArrayDim>1其实就是固定数组了），然后通过名字找枚举，以及为数组的每一项去枚举里找枚举项从而生成细节面板里的子行。

```cpp
void FItemPropertyNode::InitChildNodes()
{
		if( MyProperty->ArrayDim > 1 && ArrayIndex == -1 )
		{
			// Do not add array children which are defined by an enum but the enum at the array index is hidden
			// This only applies to static arrays
			static const FName NAME_ArraySizeEnum("ArraySizeEnum");
			UEnum* ArraySizeEnum = NULL;
			if (MyProperty->HasMetaData(NAME_ArraySizeEnum))
			{
				ArraySizeEnum	= FindObject<UEnum>(NULL, *MyProperty->GetMetaData(NAME_ArraySizeEnum));
			}

			// Expand array.
			for( int32 Index = 0 ; Index < MyProperty->ArrayDim ; Index++ )
			{
				bool bShouldBeHidden = false;
				if( ArraySizeEnum )
				{
					// The enum at this array index is hidden
					bShouldBeHidden = ArraySizeEnum->HasMetaData(TEXT("Hidden"), Index );
				}

				if( !bShouldBeHidden )
				{
					TSharedPtr<FItemPropertyNode> NewItemNode( new FItemPropertyNode);
					FPropertyNodeInitParams InitParams;
					InitParams.ParentNode = SharedThis(this);
					InitParams.Property = MyProperty;
					InitParams.ArrayOffset = Index*MyProperty->ElementSize;
					InitParams.ArrayIndex = Index;
					InitParams.bAllowChildren = true;
					InitParams.bForceHiddenPropertyVisibility = bShouldShowHiddenProperties;
					InitParams.bCreateDisableEditOnInstanceNodes = bShouldShowDisableEditOnInstance;

					NewItemNode->InitNode( InitParams );
					AddChildNode(NewItemNode);
				}
			}
		}
}
```