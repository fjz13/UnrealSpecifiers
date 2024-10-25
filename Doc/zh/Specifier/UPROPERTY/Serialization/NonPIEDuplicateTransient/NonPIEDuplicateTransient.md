# NonPIEDuplicateTransient

- **功能描述：** 在对象复制的时候，且在不是PIE的场合，忽略该属性。

- **元数据类型：** bool
- **引擎模块：** Serialization
- **作用机制：** 在PropertyFlags中加入[CPF_NonPIEDuplicateTransient](../../../../Flags/EPropertyFlags/CPF_NonPIEDuplicateTransient.md)
- **常用程度：** ★

在对象复制的时候，且在不是PIE的场合，忽略该属性。

- DuplicateTransient和NonPIEDuplicateTransient的区别是，前者在任何情况的对象复制时都忽略该属性，而后者在PIE的时候（也是在发生对象复制过程）依然会复制该属性，其他情况下的复制和前者行为一致。
- PIE的时候本质就是把当前的编辑World里Actor复制一份到PIE的世界里，会触发Actor的复制。

## 示例代码：

准备了一份DataAsset和Actor来分别验证复制行为的不同。

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

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyProperty_Serialization_TestActor :public AActor
{
public:
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyInt_Default = 123;
		//PropertyFlags:	CPF_Edit | CPF_BlueprintVisible | CPF_ZeroConstructor | CPF_Transient | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient)
		int32 MyInt_Transient = 123;
		//PropertyFlags:	CPF_Edit | CPF_BlueprintVisible | CPF_ZeroConstructor | CPF_DuplicateTransient | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DuplicateTransient)
		int32 MyInt_DuplicateTransient = 123;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, NonPIEDuplicateTransient)
		int32 MyInt_NonPIEDuplicateTransient = 123;
};
```

## 示例效果：

在对资产进行Duplidate的时候，发生DuplicateAsset然后DuplicateObject，这个时候PortFlags=PPF_Duplicate，然后会触发ShouldSerializeValue进行判断。这个时候会跳过该属性。

可以看到NonPIEDuplicateTransient并不会被复制。

![Untitled](Untitled.png)

在点击PIE的时候，可以看到NonPIEDuplicateTransient这个时候却是会复制值过去了。这是因为这个时候PortFlags=PPF_DuplicateForPIE&PPF_Duplicate

![Untitled](Untitled%201.png)

结论是用于一些Cache数据，在复制的时候并不需要序列化复制，这样可以阻止两个不同的Actor采用同一份计算后的临时数据。但是又可以在PIE的时候，让Actor各自采用自己的一份数据，因为PIE的时候，本质就是把当前的编辑World里Actor复制一份到PIE的世界里，会触发Actor的复制。

## 原理：

在文本导出的的时候，在不是PIE里的复制的时候，不序列化该属性。

```cpp
bool FProperty::ShouldPort( uint32 PortFlags/*=0*/ ) const
{
// if we're not copying for PIE and NonPIETransient is set, don't export
	if (!(PortFlags & PPF_DuplicateForPIE) && HasAnyPropertyFlags(CPF_NonPIEDuplicateTransient))
	{
		return false;
	}
}
```

在二进制序列化的时候：

只有在PPF_Duplicate生效的时候，（DuplicateObject?或者资产复制），才会跳过该属性。但是在PIE的时候，又要继续序列化。

```cpp
bool FProperty::ShouldSerializeValue(FArchive& Ar) const
{
// Skip properties marked NonPIEDuplicateTransient when duplicating, but not when we're duplicating for PIE
	if ((PropertyFlags & CPF_NonPIEDuplicateTransient) && !(Ar.GetPortFlags() & PPF_DuplicateForPIE) && (Ar.GetPortFlags() & PPF_Duplicate))
	{
		return false;
	}
}
```