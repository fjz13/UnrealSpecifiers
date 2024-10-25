# SkipSerialization

- **Function Description:** Skips serialization of this attribute during binary serialization, but it remains exportable when using ExportText.

- **Metadata Type:** bool
- **Engine Module:** Serialization
- **Action Mechanism:** Include [CPF_SkipSerialization](../../../../Flags/EPropertyFlags/CPF_SkipSerialization.md) in PropertyFlags
- **Commonly Used:** ★★★

During standard binary serialization, this marker prevents the attribute from being serialized, functioning similarly to Transient. However, it can still be exported if ExportText is used. Internally, ExportProperties is utilized.

## Test Code:

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

As seen in the test results, the attribute has not been serialized.

![Untitled](Untitled.png)

If ExportText is used for export: either T3D or COPY format is acceptable

```cpp
UMyProperty_SerializationText* obj = NewObject<UMyProperty_SerializationText>(GetTransientPackage());

obj->MyInt_Default = 456;
obj->MyInt_SkipSerialization = 456;

FStringOutputDevice Ar;
UExporter::ExportToOutputDevice(nullptr, obj, nullptr,Ar,TEXT("T3D"), 3);
```

The output result will be:

```cpp
Begin Object Class=/Script/Insider.MyProperty_SerializationText Name="MyProperty_SerializationText_0" ExportPath=/Script/Insider.MyProperty_SerializationText'"/Engine/Transient.MyProperty_SerializationText_0"'
    MyInt_Default=456
    MyInt_SkipSerialization=456
 End Object
```

Moreover, if you right-click and copy in the editor,

![Untitled](Untitled%201.png)

It is also possible to generate a text export:

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

## Principle:

Note that when determining whether a Property should be serialized, the ShouldSerializeValue function is used for standard serialization, while ShouldPort is used during ExportText.