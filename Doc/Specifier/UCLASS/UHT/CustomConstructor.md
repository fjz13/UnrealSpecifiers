# CustomConstructor

功能描述: 阻止构造函数声明自动生成。
引擎模块: UHT
元数据类型: bool
Example: UMyClass_CustomConstructor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
EClassFlagsOperation: |=
EClassFlags: CLASS_CustomConstructor (../../Flags/EClassFlags/CLASS_CustomConstructor.md)
Status: Deprecated

UHT不会生成 NO_API UMyClass_ModuleAPI(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());的默认构造函数。但是这个一般都是配合GENERATED_UCLASS_BODY使用的，因为GENERATED_BODY会自动生成默认构造函数。一般在自己需要自定义这个函数的时候使用。（但其实用GENERATED_BODY也行）

当前已经弃用：

```cpp
CLASS_CustomConstructor UE_DEPRECATED(5.1, "CLASS_CustomConstructor should no longer be used. It is no longer being set by engine code.") = 0x00008000u,
```