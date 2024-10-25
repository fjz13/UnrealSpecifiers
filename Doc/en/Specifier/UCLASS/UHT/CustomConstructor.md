# CustomConstructor

- **Function Description:** Prevent the automatic generation of constructor declarations.
- **Engine Module:** UHT
- **Metadata Type:** bool
- **Action Mechanism:** Add [CLASS_CustomConstructor](../../../Flags/EClassFlags/CLASS_CustomConstructor.md) to ClassFlags

UHT will not generate the default constructor for NO_API UMyClass_ModuleAPI(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());. However, this is typically used in conjunction with GENERATED_UCLASS_BODY, as GENERATED_BODY will automatically generate a default constructor. It is generally used when customizing this function is required. (But using GENERATED_BODY is also acceptable.)

Currently deprecated:

```cpp
CLASS_CustomConstructor UE_DEPRECATED(5.1, "CLASS_CustomConstructor should no longer be used. It is no longer being set by engine code.") = 0x00008000u,
```