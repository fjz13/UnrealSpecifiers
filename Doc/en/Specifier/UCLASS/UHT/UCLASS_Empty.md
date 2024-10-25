# UCLASS()

- **Function Description:** The default behavior for leaving it blank is that it cannot be inherited within blueprints, variables cannot be defined within blueprints, yet it retains reflective capabilities.

- **Engine Module:** UHT
- **Metadata Type:** bool
- **Functionality Mechanism:** [CLASS_MatchedSerializers](../../../Flags/EClassFlags/CLASS_MatchedSerializers.md), [CLASS_Native](../../../Flags/EClassFlags/CLASS_Native.md), [CLASS_RequiredAPI](../../../Flags/EClassFlags/CLASS_RequiredAPI.md), [CLASS_TokenStreamAssembled](../../../Flags/EClassFlags/CLASS_TokenStreamAssembled.md), [CLASS_Intrinsic](../../../Flags/EClassFlags/CLASS_Intrinsic.md), [CLASS_Constructed](../../../Flags/EClassFlags/CLASS_Constructed.md) are added to ClassFlags
- **Related items:** [Do not write UCLASS ()](%E4%B8%8D%E5%86%99UCLASS_Empty.md)
- **Commonly Used:** ★★★★★

It cannot be inherited in blueprints, nor can variables be defined within blueprints.

However, they can still be instantiated using the blueprint ConstructObject. This is particularly suitable for those who desire reflective capabilities without the intention of using them within blueprints.

## Sample Code:

```cpp
/*
[MyClass_Default	Class->Struct->Field->Object	/Script/Insider.MyClass_Default] [IncludePath = Class/MyClass_Default.h, ModuleRelativePath = Class/MyClass_Default.h]
ObjectFlags:	RF_Public | RF_Standalone | RF_Transient
Outer:	Package /Script/Insider
ClassFlags:	CLASS_MatchedSerializers | CLASS_Native | CLASS_RequiredAPI | CLASS_TokenStreamAssembled | CLASS_Intrinsic | CLASS_Constructed
Size:	48
{
public: void ExecuteUbergraph(int32 EntryPoint);
};
*/

UCLASS()
class INSIDER_API UMyClass_Default :public UObject
{
	GENERATED_BODY()
public:
};
```

By default, it possesses the following flags: CLASS_MatchedSerializers | CLASS_Native | CLASS_RequiredAPI | CLASS_TokenStreamAssembled | CLASS_Intrinsic | CLASS_Constructed