# Intrinsic

- **Function Description:** Specify that UHT should not generate any code for this class, requiring manual implementation.

- **Engine Module:** UHT
- **Metadata Type:** bool
- **Action Mechanism:** Add [CLASS_Intrinsic](../../../Flags/EClassFlags/CLASS_Intrinsic.md) to ClassFlags
- **Usage Frequency:** 0

Specify that UHT should not generate any code for this class, necessitating manual coding.

Only set directly in C++; typically, new classes do not use this setting. Classes marked with this are native to UE4, indicating that their metadata code is already handwritten in the source code.

noexport will still parse and generate metadata, but it lacks registration. As a result, all metadata flags for the intrinsic class need to be manually set. However, intrinsic does not generate any code at all; both generated.h and .gen.cpp remain empty. Currently, the only class in noexporttyps.h using intrinsics is UCLASS(noexport, Intrinsic) class UModel{}, but it is still not compiled by the C++ compiler.

```cpp
//UCLASS(Intrinsic)
//class INSIDER_API UMyClass_Intrinsic :public UObject	//syntax error: missing ';' before '<class-head>'
//{
//	GENERATED_BODY()
//
//};

//.h
class INSIDER_API UMyClass_Intrinsic :public UObject
{
	DECLARE_CLASS_INTRINSIC(UMyClass_Intrinsic, UObject, CLASS_MatchedSerializers, TEXT("/Script/Insider"))
};
//.cpp
IMPLEMENT_INTRINSIC_CLASS(UMyClass_Intrinsic, INSIDER_API, UObject, INSIDER_API, "/Script/Insider", {})

class COREUOBJECT_API UInterface : public UObject
{
	DECLARE_CLASS_INTRINSIC(UInterface, UObject, CLASS_Interface | CLASS_Abstract, TEXT("/Script/CoreUObject"))
};
```