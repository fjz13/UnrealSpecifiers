# EditFixedOrder

- **Function Description:** Prevents array elements from being reordered via dragging.
- **Usage Location:** UPROPERTY
- **Engine Module:** Container Property
- **Metadata Type:** bool
- **Restriction Type:** TArray
- **Commonliness:** ★★

## Test Code:

```cpp
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditFixedOrderTest)
	TArray<int32> MyIntArray_NoEditFixedOrder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditFixedOrderTest, meta = (EditFixedOrder))
	TArray<int32> MyIntArray_EditFixedOrder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditFixedOrderTest)
	TSet<int32> MyIntSet_NoEditFixedOrder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditFixedOrderTest, meta = (EditFixedOrder))
	TSet<int32> MyIntSet_EditFixedOrder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditFixedOrderTest)
	TMap<int32,FString> MyIntMap_NoEditFixedOrder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditFixedOrderTest, meta = (EditFixedOrder))
	TMap<int32,FString> MyIntMap_EditFixedOrder;
```

## Test Effects:

- It can be seen that only the first MyIntArray_NoEditFixedOrder appears on the array element as a draggable mark, and then the order can be changed.
- With the addition of EditFixedOrder's TArray, the order cannot be changed.
- Other types like TSet and TMap do not support this meta, as their internal order is inherently irrelevant.

![EditFixedOrder](EditFixedOrder.gif)

## Principle:

As you can see, the judgment of whether an attribute row in the details panel is reorderable is that the outer part is an array, and there is no EditFixedOrder and ArraySizeEnum (fixed array). Of course, this attribute itself must also be in an editable state (for example, if it is disabled and grayed out, it will obviously not be editable)

```cpp
bool FPropertyNode::IsReorderable()
{
	FProperty* NodeProperty = GetProperty();
	if (NodeProperty == nullptr)
	{
		return false;
	}
	// It is reorderable if the parent is an array and metadata doesn't prohibit it
	const FArrayProperty* OuterArrayProp = NodeProperty->GetOwner<FArrayProperty>();

	static const FName Name_DisableReordering("EditFixedOrder");
	static const FName NAME_ArraySizeEnum("ArraySizeEnum");
	return OuterArrayProp != nullptr
		&& !OuterArrayProp->HasMetaData(Name_DisableReordering)
		&& !IsEditConst()
		&& !OuterArrayProp->HasMetaData(NAME_ArraySizeEnum)
		&& !FApp::IsGame();
}
```