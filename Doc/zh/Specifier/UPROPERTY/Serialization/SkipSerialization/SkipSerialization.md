# SkipSerialization

- **功能描述：** 二进制序列化时跳过该属性，但在ExportText的时候依然可以导出。

- **元数据类型：** bool
- **引擎模块：** Serialization
- **作用机制：** 在PropertyFlags中加入[CPF_SkipSerialization](../../../../Flags/EPropertyFlags/CPF_SkipSerialization.md)
- **常用程度：** ★★★

在进行普通的二进制序列化的时候，这个标记会阻止序列化。作用和Transient一样。但如果是ExportText，则依然可以把该属性导出。其内部用的ExportProperties。

## 测试代码：

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyProperty_SerializationText :public UObject
{
public:
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyInt_Default= 123;
		//PropertyFlags:	CPF_Edit | CPF_BlueprintVisible | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic | CPF_SkipSerialization
	UPROPERTY(EditAnywhere, BlueprintReadWrite,SkipSerialization)
		int32 MyInt_SkipSerialization = 123;
};

void UMyProperty_SerializationText_Test::RunTest()
{
	UMyProperty_SerializationText* obj = NewObject<UMyProperty_SerializationText>(GetTransientPackage());

	obj->MyInt_Default = 456;
	obj->MyInt_SkipSerialization = 456;

	//save obj
	TArray<uint8> outBytes;
	FMemoryWriter MemoryWriter(outBytes, true);
	FObjectAndNameAsStringProxyArchive Ar(MemoryWriter, false);
	obj->Serialize(Ar);

	//load
	FMemoryReader MemoryReader(outBytes, true);

	FObjectAndNameAsStringProxyArchive Ar2(MemoryReader, true);

	UMyProperty_SerializationText* obj2 = NewObject<UMyProperty_SerializationText>(GetTransientPackage());
	obj2->Serialize(Ar2);
}
```

此时可见测试结果，该属性并没有被序列化进去。

![Untitled](Untitled.png)

如果采用ExportText导出：T3D或COPY格式都行

```cpp
UMyProperty_SerializationText* obj = NewObject<UMyProperty_SerializationText>(GetTransientPackage());

obj->MyInt_Default = 456;
obj->MyInt_SkipSerialization = 456;

FStringOutputDevice Ar;
UExporter::ExportToOutputDevice(nullptr, obj, nullptr,Ar,TEXT("T3D"), 3);
```

则输出结果为：

```cpp
Begin Object Class=/Script/Insider.MyProperty_SerializationText Name="MyProperty_SerializationText_0" ExportPath=/Script/Insider.MyProperty_SerializationText'"/Engine/Transient.MyProperty_SerializationText_0"'
    MyInt_Default=456
    MyInt_SkipSerialization=456
 End Object
```

另外如果在编辑器里右击复制

![Untitled](Untitled%201.png)

也可以产生文本的导出：

```cpp
{
	"Tagged": [
		[
			"MyInt_Default",
			"456"
		],
		[
			"MyInt_SkipSerialization",
			"456"
		]
	]
}
```

## 原理：

注意在判断一个Property是否应该序列化的时候，ShouldSerializeValue函数是用在普通的序列化的时候用来判断的。而在ExportText的时候，是用ShouldPort判断的。