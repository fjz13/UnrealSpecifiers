---
title: "SkipSerialization"
id: "UPROPERTY.SkipSerialization"
kind: "specifier"
symbol: "SkipSerialization"
scope: "UPROPERTY"
category: "Serialization"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "二进制序列化时跳过该属性，但在ExportText的时候依然可以导出"
usage: "UPROPERTY / Serialization"
---

# SkipSerialization

## Decision Summary

- **Use when:** `SkipSerialization` specifier 的 `UPROPERTY / Serialization` 场景需要：二进制序列化时跳过该属性，但在ExportText的时候依然可以导出。
- **Do not use when:** 声明宏、目标类型或代码契约不属于 `UPROPERTY / Serialization`。
- **Requires:** 用于跳过普通序列化路径的属性；确认复制、文本导出、SaveGame、editor duplication 等相关流程是否仍需单独处理。
- **Conflicts:** 不要和同类互斥 specifier 或语义相反的暴露/持久化/网络规则混用。
- **Prefer instead:** 能用更窄暴露范围或更明确 metadata 表达时，优先选择更窄方案。

- **功能描述：** 二进制序列化时跳过该属性，但在ExportText的时候依然可以导出。

- **元数据类型：** bool
- **引擎模块：** Serialization
- **作用机制：** 在PropertyFlags中加入CPF_SkipSerialization
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

## 行为

在 UE5.8 UHT 中写入 `CPF_SkipSerialization`，用于跳过常规序列化路径；它不是文本导出 transient，也不是 duplicate transient。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `UhtPropertyMemberSpecifiers.cs` 对应 specifier 分支
  - 本地样例辅助对照：`D:/github/GitWorkspace/Hello/Source/Insider/Property/Serialization/MyProperty_SerializationText.h`。

## 常见误用

把它当成 `Transient` 的完整替代；或忽略文本导出/复制/SaveGame 等其他路径差异。
