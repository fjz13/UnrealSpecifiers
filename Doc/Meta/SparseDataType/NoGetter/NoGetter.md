# NoGetter

功能描述: 阻止UHT为该属性生成一个C++的get函数，只对稀疏类的结构数据里的属性生效。
使用位置: UPROPERTY
Feature: Blueprint
引擎模块: SparseDataType
元数据类型: bool
Status: Done
UCLASS: SparseClassDataType (../../Specifier/UCLASS/SparseClassDataType.md)
常用程度: 1

阻止UHT为该属性生成一个C++的get函数，只对稀疏类的结构数据里的属性生效。

这个要和SparseClassDataTypes的用法一起配合看，且NoGetter不影响蓝图里对该属性的访问。

测试代码：

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

测试结果：

在生成的.generated.h"中，会发现MyString_EditDefault_NoGetter 没有生成相应的C++ get函数。

```cpp
// "MyClass_SparseClassDataTypes.generated.h"

#define FID_Hello_Source_Insider_Class_Trait_MyClass_SparseClassDataTypes_h_33_SPARSE_DATA_PROPERTY_ACCESSORS \
int32 GetMyInt_EditDefaultOnly() const { return GetMySparseClassData(EGetSparseClassDataMethod::ArchetypeIfNull)->MyInt_EditDefaultOnly; } \
int32 GetMyInt_BlueprintReadOnly() const { return GetMySparseClassData(EGetSparseClassDataMethod::ArchetypeIfNull)->MyInt_BlueprintReadOnly; } \
const FString& GetMyString_EditDefault_ReadOnly() const { return GetMySparseClassData(EGetSparseClassDataMethod::ArchetypeIfNull)->MyString_EditDefault_ReadOnly; }
```

而蓝图里是依然可以访问到的：

![Untitled](NoGetter/Untitled.png)

## 原理：

UHT在识别到SparseDataStruct后，会为其内部的属性调用AppendSparseDeclarations生成相应的C++属性Get函数（就是FID_Hello_Source_Insider_Class_Trait_MyClass_SparseClassDataTypes_h_33_SPARSE_DATA_PROPERTY_ACCESSORS 那些）。而如果属性上标上NoGetter，就把该属性从SparseDataStruct里过滤掉。

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

但蓝图里的属性细节面板的属性还是存在的，因为蓝图系统会分析SparseDataStruct里的所有属性并加到细节面板里去。这部分逻辑并没有判断NoGetter，因此NoGetter不影响属性在蓝图里的访问，只影响C++里的get函数。

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