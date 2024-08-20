# NoExport

- **功能描述：**指定UHT不要用来自动生成注册的代码，而只是进行词法分析提取元数据。

- **引擎模块：**UHT
- **元数据类型：**bool
- **作用机制：**在ClassFlags中增加EClassFlags: [CLASS_NoExport](../../../Flags/EClassFlags/CLASS_NoExport.md)
- **常用程度：**0

指定UHT不要用来自动生成注册的代码，而只是进行词法分析提取元数据。

引擎的NoExportTypes.h里大量都是这种类型，专门提供给UHT来提取信息的。一般会用#if !CPP //noexport class来包裹，来避免编译。同时在另一个地方会定义这个类。因为StaticRegisterNatives##TClass没有生成，所以GetPrivateStaticClass不能调用成功，所以不能NewObject。一般noexport和Intrinsic都是配合使用的。因为DECLARE_CLASS_INTRINSIC内部会声明static void StaticRegisterNatives##TClass() {} 来允许成功调用。

引擎里的结构倒是经常用noexport来阻止生成UHT注册。因为结构其实不需要调用GetPrivateStaticClass来创建元数据。只要有Z_Construct_UScriptStruct_XXX来生成构造相应的UScriptStruct对象就行。

## 测试代码:

```cpp
UCLASS(noexport)
class INSIDER_API UMyClass_NoExport :public UObject
{
	GENERATED_BODY()
public:
};
```

## 测试结果：

```cpp
编译的时候生成错误：
error LNK2019: unresolved external symbol "private: static void __cdecl UMyClass_NoExport::StaticRegisterNativesUMyClass_NoExport(void)" (?StaticRegisterNativesUMyClass_NoExport@UMyClass_NoExport@@CAXXZ) referenced in function "private: static class UClass * __cdecl UMyClass_NoExport::GetPrivateStaticClass(void)" (?GetPrivateStaticClass@UMyClass_NoExport@@CAPEAVUClass@@XZ)
```