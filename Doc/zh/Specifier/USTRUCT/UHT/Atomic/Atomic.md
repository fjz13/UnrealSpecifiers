# Atomic

- **功能描述:** 指定该结构在序列化的时候总是一整个输出全部属性，而不是只输出改变的属性。
- **元数据类型:** bool
- **引擎模块:** UHT
- **作用机制：** 在StructFlags中加入[STRUCT_Atomic](../../../../Flags/EStructFlags/STRUCT_Atomic.md)
- **常用程度:** ★

指定该结构在序列化的时候总是一整个输出全部属性，而不是只输出改变的属性。

所谓的原子化序列化指的是如果该结构的某个字段属性同默认值不同，但是其他字段相同，也要一次性的序列化整个结构，而不是拆开。注意这个只在普通的SerializeVersionedTaggedProperties下有效，因为是对比默认值。在Bin下无效。其实作用机理是当采用原子化序列化的时候，就不检查内部属性的默认值，从而无论什么情况都会序列化进整个属性。

UE的noexporttype.h中有大量的atomic的基础结构，如FVector，因为Immutable也会同时设置STRUCT_Atomic，但是没有发现单独设置Atomic的地方。

## 示例代码：

```cpp
USTRUCT(BlueprintType)
struct INSIDER_API FMyStruct_InnerItem
{
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 A = 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 B = 2;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 C = 3;

	bool operator==(const FMyStruct_InnerItem& other)const
	{
		return A == other.A;
	}
};

USTRUCT(BlueprintType)
struct INSIDER_API FMyStruct_NoAtomic
{
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FMyStruct_InnerItem Item;
};

USTRUCT(Atomic, BlueprintType)
struct INSIDER_API FMyStruct_Atomic
{
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FMyStruct_InnerItem Item;
};

template<>
struct TStructOpsTypeTraits<FMyStruct_InnerItem> : public TStructOpsTypeTraitsBase2<FMyStruct_InnerItem>
{
	enum
	{
		WithIdenticalViaEquality = true,
	};
};

void USerializationLibrary::SaveStructToMemory(UScriptStruct* structClass, void* structObject, const void* structDefaults, TArray<uint8>& outSaveData, EInsiderSerializationFlags flags/*=EInsiderSerializationFlags::None*/)
{
	FMemoryWriter MemoryWriter(outSaveData, false);
	MemoryWriter.SetWantBinaryPropertySerialization(EnumHasAnyFlags(flags, EInsiderSerializationFlags::UseBinary));
	if (!EnumHasAnyFlags(flags, EInsiderSerializationFlags::CheckDefaults))
	{
		structDefaults=nullptr;
	}
	structClass->SerializeItem(MemoryWriter, structObject, structDefaults);
}

测试代码：
FMyStruct_NoAtomic NoAtomicStruct;
NoAtomicStruct.Item.A=3;

FMyStruct_Atomic AtomicStruct;
AtomicStruct.Item.A=3;

TArray<uint8> NoAtomicMemoryChanged;
USerializationLibrary::SaveStructToMemory(NoAtomicStruct,NoAtomicMemoryChanged,EInsiderSerializationFlags::CheckDefaults);

TArray<uint8> AtomicMemoryChanged;
USerializationLibrary::SaveStructToMemory(AtomicStruct,AtomicMemoryChanged,EInsiderSerializationFlags::CheckDefaults);
```

## 示例效果：

可见AtomicMemoryChanged的占用内存大小比AtomicMemoryChanged多，因为这两个结构的属性虽然都改变了，但是AtomicStruct总是会把所有的属性都序列化出来。

![Untitled](Untitled.png)

## 原理：

作用的机理是，一个外部结构是Atomic的，其内部的属性如果发现有改变，这个时候内部属性得是另一个结构，因为如果只是Int属性，则不会对比内部属性默认值。如果是内部结构属性的话，因为其中一个ID字段不一样，就在对比的时候导致整个结构不等（但同时该内部结构又有其他属性是相同的，所以上面示例代码只改了A，且提供了==的比较函数）。默认的方式是依然会在内部结构的内部属性上继续对比默认值，但原子化后就截断了默认值为null，从而导致孙子属性没有默认值可对比，从而就把整个内部属性就都输出出来。因此Atomic是用在外部结构上的，用在FVector这种不太会继续拆开的结构其实没什么意义。

```cpp
void UStruct::SerializeVersionedTaggedProperties(FStructuredArchive::FSlot Slot, uint8* Data, UStruct* DefaultsStruct, uint8* Defaults, const UObject* BreakRecursionIfFullyLoad) const
{
//……
/** If true, it means that we want to serialize all properties of this struct if any properties differ from defaults */
		bool bUseAtomicSerialization = false;
		if (DefaultsScriptStruct)
		{
			bUseAtomicSerialization = DefaultsScriptStruct->ShouldSerializeAtomically(UnderlyingArchive);
		}

if (bUseAtomicSerialization)
	{
		DefaultValue = NULL;
	}
}
```