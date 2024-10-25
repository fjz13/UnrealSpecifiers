# NoExport

- **Function description:** Instruct UHT not to automatically generate registration code, but to perform lexical analysis and extract metadata exclusively.

- **Engine module:** UHT
- **Metadata type:** bool
- **Mechanism of action:** Add EClassFlags: [CLASS_NoExport](../../../Flags/EClassFlags/CLASS_NoExport.md) to ClassFlags
- **Frequency of use:** 0

Specify that UHT should not be used to automatically generate registration code, but only for lexical analysis to extract metadata.

There are a lot of this type in the engine NoExportTypes.h which are specially provided for UHT to extract information. Usually it is wrapped with #if ! CPP //noexport class to avoid compilation. At the same time, this class will be defined in another place. Because StaticRegisterNatives##TClass is not generated, GetPrivateStaticClass cannot be called successfully, so NewObject cannot be used. Generally noexport and Intrinsic are used together. Because DECLARE_CLASS_INTRINSIC internally declares static void StaticRegisterNatives##TClass () {} to allow successful calls.

Structures in the engine often use noexport to prevent UHT registration from being generated. Because the structure doesn't actually need to call GetPrivateStaticClass to create metadata. As long as there is an object Z_Construct_UScriptStruct_XXX to generate and construct the corresponding UScriptStruct object.

## Test Code:

```cpp
UCLASS(noexport)
class INSIDER_API UMyClass_NoExport :public UObject
{
	GENERATED_BODY()
public:
};
```

## Test Results:

```cpp
编译的时候生成错误：
error LNK2019: unresolved external symbol "private: static void __cdecl UMyClass_NoExport::StaticRegisterNativesUMyClass_NoExport(void)" (?StaticRegisterNativesUMyClass_NoExport@UMyClass_NoExport@@CAXXZ) referenced in function "private: static class UClass * __cdecl UMyClass_NoExport::GetPrivateStaticClass(void)" (?GetPrivateStaticClass@UMyClass_NoExport@@CAPEAVUClass@@XZ)
```