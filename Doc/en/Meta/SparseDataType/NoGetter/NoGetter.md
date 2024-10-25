# NoGetter

- **Function description:** Prevent UHT from generating a C++ getter function for this attribute, effective only for properties within the structure data of sparse classes.

- **Use location:** UPROPERTY

- **Engine module:** SparseDataType

- **Metadata type:** bool

- **Associated items:**

  UCLASS: [SparseClassDataType](../../../Specifier/UCLASS/Blueprint/SparseClassDataType/SparseClassDataType.md)

- **Commonality:** ★

Prevents UHT from generating a C++ getter function for this attribute, effective only for properties within the structure data of sparse classes.

This should be used in conjunction with the usage of SparseClassDataTypes, and NoGetter does not impact the property's accessibility in blueprints.

## Test Code:

```cpp
USTRUCT(BlueprintType)
struct FMySparseClassData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	int32 MyInt_EditDefaultOnly = 123;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 MyInt_BlueprintReadOnly = 1024;

	// "GetByRef" means that Blueprint graphs access a const ref instead of a copy.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (GetByRef))
	FString MyString_EditDefault_ReadOnly = TEXT("MyName");

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (NoGetter))
	FString MyString_EditDefault_NoGetter = TEXT("MyName");
};
```

## Test Results:

In the generated . generated.h" , you will find that MyString_EditDefault_NoGetter does not generate the corresponding C++ get function.

```cpp
// "MyClass_SparseClassDataTypes.generated.h"

#define FID_Hello_Source_Insider_Class_Trait_MyClass_SparseClassDataTypes_h_33_SPARSE_DATA_PROPERTY_ACCESSORS \
int32 GetMyInt_EditDefaultOnly() const { return GetMySparseClassData(EGetSparseClassDataMethod::ArchetypeIfNull)->MyInt_EditDefaultOnly; } \
int32 GetMyInt_BlueprintReadOnly() const { return GetMySparseClassData(EGetSparseClassDataMethod::ArchetypeIfNull)->MyInt_BlueprintReadOnly; } \
const FString& GetMyString_EditDefault_ReadOnly() const { return GetMySparseClassData(EGetSparseClassDataMethod::ArchetypeIfNull)->MyString_EditDefault_ReadOnly; }
```

And it is still accessible in blueprints:

![Untitled](Untitled.png)

## Principle:

UHT After recognizing SparseDataStruct , it will call AppendSparseDeclarations to generate the corresponding C++ attribute Get function (that is, FID_Hello_Source_Insider_Class_Trait_MyClass_SparseClassDataTypes_h_33_SPARSE_DATA_PROPERTY_ACCESSORS those) for its internal attributes. And if the attribute is marked with NoGetter , the attribute will be filtered out SparseDataStruct .

```cpp
	private static IEnumerable<UhtProperty> EnumerateSparseDataStructProperties(IEnumerable<UhtScriptStruct> sparseScriptStructs)
	{
		foreach (UhtScriptStruct sparseScriptStruct in sparseScriptStructs)
		{
			foreach (UhtProperty property in sparseScriptStruct.Properties)
			{
				if (!property.MetaData.ContainsKey(UhtNames.NoGetter))
				{
					yield return property;
				}
			}
		}
	}
```

However, the attributes in the blueprint's property details panel still exist because the blueprint system analyzes all attributes within SparseDataStruct and adds them to the details panel. This part of the logic does not consider NoGetter, hence NoGetter does not affect the property's accessibility in blueprints, only the C++ getter function.

```cpp
if (UScriptStruct* SparseClassDataStruct = ResolvedBaseClass->GetSparseClassDataStruct())
{
	SparseClassDataInstances.Add(ResolvedBaseClass, TTuple<UScriptStruct*, void*>(SparseClassDataStruct, ResolvedBaseClass->GetOrCreateSparseClassData()));

	for (TFieldIterator<FProperty> It(SparseClassDataStruct); It; ++It)
	{
		GetCategoryProperties(ClassesToConsider, *It, bShouldShowDisableEditOnInstance, bShouldShowHiddenProperties, CategoriesFromBlueprints, CategoriesFromProperties, SortedCategories);
	}
}

```