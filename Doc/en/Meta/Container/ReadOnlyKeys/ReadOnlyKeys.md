# ReadOnlyKeys

- **Function Description:** Prevents the Key of a TMap attribute from being edited.
- **Usage Location:** UPROPERTY
- **Engine Module:** Container Property
- **Metadata Type:** bool
- **Restriction Type:** TMap attribute
- **Commonality:** ★★

Prevents the Key of the TMap attribute from being edited.

Means that the elements within this TMap are set prior to this (e.g., initialized in the constructor), but we only want users to modify the content of the values, not the names of the Keys. This is particularly useful in scenarios such as using Platform as the Key, where the list of Platforms is fixed and should not be altered by users.

## Test Code:

```cpp
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ReadOnlyKeysTest)
	TMap<int32, FString> MyIntMap_NoReadOnlyKeys;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ReadOnlyKeysTest, meta = (ReadOnlyKeys))
	TMap<int32, FString> MyIntMap_ReadOnlyKeys;
```

## Test Results:

It is evident that the Key of MyIntMap_ReadOnlyKeys is grayed out and cannot be edited.

![Untitled](Untitled.png)

## Found in the Source Code:

```cpp
void FDetailPropertyRow::MakeNameOrKeyWidget( FDetailWidgetRow& Row, const TSharedPtr<FDetailWidgetRow> InCustomRow ) const
{
	if (PropertyHandle->HasMetaData(TEXT("ReadOnlyKeys")))
	{
		PropertyKeyEditor->GetPropertyNode()->SetNodeFlags(EPropertyNodeFlags::IsReadOnly, true);
	}
}
```