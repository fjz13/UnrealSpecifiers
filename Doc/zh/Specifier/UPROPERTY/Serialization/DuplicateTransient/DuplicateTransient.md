# DuplicateTransient

- **功能描述：** 在对象复制或COPY格式导出的时候，忽略该属性。

- **元数据类型：** bool
- **引擎模块：** Serialization
- **作用机制：** 在PropertyFlags中加入[CPF_DuplicateTransient](../../../../Flags/EPropertyFlags/CPF_DuplicateTransient.md)
- **常用程度：** ★★

在对象复制或COPY格式导出的时候，忽略该属性。

## 示例代码：

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyProperty_Serialization :public UDataAsset
{
public:
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyInt_Default = 123;
		//PropertyFlags:	CPF_Edit | CPF_BlueprintVisible | CPF_ZeroConstructor | CPF_Transient | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient)
		int32 MyInt_Transient = 123;
		//PropertyFlags:	CPF_Edit | CPF_BlueprintVisible | CPF_ZeroConstructor | CPF_DuplicateTransient | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DuplicateTransient)
		int32 MyInt_DuplicateTransient = 123;
		//PropertyFlags:	CPF_Edit | CPF_BlueprintVisible | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_NonPIEDuplicateTransient | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
	UPROPERTY(EditAnywhere, BlueprintReadWrite, NonPIEDuplicateTransient)
		int32 MyInt_NonPIEDuplicateTransient = 123;
};

void UMyProperty_Serialization_Test::RunTest()
{

	UMyProperty_Serialization* obj = NewObject<UMyProperty_Serialization>(GetTransientPackage());

	obj->MyInt_Default = 456;
	obj->MyInt_Transient = 456;
	obj->MyInt_DuplicateTransient = 456;
	obj->MyInt_NonPIEDuplicateTransient = 456;

	UMyProperty_Serialization* obj3= DuplicateObject<UMyProperty_Serialization>(obj,GetTransientPackage());
}

```

## 示例效果：

复制蓝图，可以看到DuplicateTransient并不会被复制

![Untitled](Untitled.png)

在采用C++复制的时候：也看到MyInt_DuplicateTransient 并不会产生复制，还是123而不是456。

![Untitled](Untitled.png)

## 原理：

在文本导出的时候，如果是T3D格式，则依然会导出。如果是COPY格式，则不导出。

```cpp
bool FProperty::ShouldPort( uint32 PortFlags/*=0*/ ) const
{
// if we're copying, treat DuplicateTransient as transient
	if ((PortFlags & PPF_Copy) && HasAnyPropertyFlags(CPF_DuplicateTransient | CPF_TextExportTransient) && !(PortFlags & (PPF_ParsingDefaultProperties | PPF_IncludeTransient)))
	{
		return false;
	}
}
```

在二进制序列化的时候：

只有在PPF_Duplicate生效的时候，（DuplicateObject或者资产复制），才会跳过该属性

```cpp
bool FProperty::ShouldSerializeValue(FArchive& Ar) const
{
// Skip properties marked DuplicateTransient when duplicating
	if ((PropertyFlags & CPF_DuplicateTransient) && (Ar.GetPortFlags() & PPF_Duplicate))
	{
		return false;
	}
}
```

在对资产进行Duplidate的时候，发生DuplicateAsset然后DuplicateObject，这个时候PortFlags=PPF_Duplicate，然后会触发ShouldSerializeValue进行判断。这个时候会跳过该属性