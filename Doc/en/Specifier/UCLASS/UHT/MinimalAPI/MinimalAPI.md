# MinimalAPI

- **Function Description:** The class's functions are not exported to the DLL; only type information is exported as variables.

- **Engine Module:** DllExport
- **Metadata Type:** bool
- **Action Mechanism:** Add [CLASS_MinimalAPI](../../../../Flags/EClassFlags/CLASS_MinimalAPI.md) to ClassFlags
- **Common Usage:** ★★★

Do not export the class's functions to the DLL; only export type information as variables.

- Other modules that reference this one can use pointers for conversion but cannot call the aforementioned functions. However, they are still accessible in Blueprints.
- The benefit is that it can reduce compilation information and speed up linking, as there are fewer dllexport functions.
- Note that MinimalAPI cannot be used in conjunction with MODULENAME_API, as MinimalAPI is for non-exporting, while MODULENAME_API is for exporting. The effect of MinimalAPI is not equivalent to not writing MODULENAME_API, because MinimalAPI also exports GetPrivateStaticClass to allow NewObject. Therefore, if a class does not want to be known by another module at all, no export is needed. If you want another module to be aware of the type but not call any functions, MinimalAPI can be used to prevent this.
- It is recommended not to export game modules. External modules of plugins should be exported, while internal base classes can consider using MinimalAPI, and private classes can be completely unexported. MinimalAPI is frequently used in the engine, resulting in classes that can be used as variables but not inherited or methods called.
- It is typically used in conjunction with BlueprintType, allowing it to be used as a variable in Blueprints.
- Functions and properties can be called normally in Blueprints. This is because blueprint calls only require reflection information, which is registered into the system by the module itself.

## Sample Code:

```cpp
UCLASS()
class UMyClass_NotMinimalAPI :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MyProperty;
	UFUNCTION(BlueprintCallable)
	void MyFunc();
};

UCLASS(MinimalAPI)
class UMyClass_MinimalAPI :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MyProperty;
	UFUNCTION(BlueprintCallable)
	void MyFunc();
};

UCLASS(MinimalAPI, BlueprintType)
class UMyClass_MinimalAPI_BlueprintType :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MyProperty;
	UFUNCTION(BlueprintCallable)
	void MyFunc() {}
};

UCLASS(MinimalAPI)
class UMyClass_MinimalAPI_BlueprintFunctionLibary :public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	static void MyFuncInMinimalAPI();

	UFUNCTION(BlueprintCallable)
	static INSIDER_API void MyFuncInMinimalAPIWithAPI();
};
```

## Example Effect:

Functions and properties can be called normally in Blueprints. Methods in the blueprint function library can also be called, indicating that UHT still generates reflection call information for MinimalAPI. Blueprint calls only require reflection information, as the module itself registers function and attribute pointers into the system, thus no DLL export is necessary. However, this function is not found when viewing the list of functions exported by the DLL in the export tool.

![Untitled](Untitled.png)

View the list of DLL exported functions:

```cpp
class UClass * __ptr64 __cdecl StaticClass<class UMyClass_MinimalAPI>(void)
class UClass * __ptr64 __cdecl StaticClass<class UMyClass_MinimalAPI_BlueprintFunctionLibary>(void)
class UClass * __ptr64 __cdecl StaticClass<class UMyClass_MinimalAPI_BlueprintType>(void)
class UClass * __ptr64 __cdecl StaticClass<class UMyClass_NotMinimalAPI>(void)
class UClass * __ptr64 __cdecl Z_Construct_UClass_UMyClass_MinimalAPI(void)
class UClass * __ptr64 __cdecl Z_Construct_UClass_UMyClass_MinimalAPI_BlueprintFunctionLibary(void)
class UClass * __ptr64 __cdecl Z_Construct_UClass_UMyClass_MinimalAPI_BlueprintFunctionLibary_NoRegister(void)
class UClass * __ptr64 __cdecl Z_Construct_UClass_UMyClass_MinimalAPI_BlueprintType(void)
class UClass * __ptr64 __cdecl Z_Construct_UClass_UMyClass_MinimalAPI_BlueprintType_NoRegister(void)
class UClass * __ptr64 __cdecl Z_Construct_UClass_UMyClass_MinimalAPI_NoRegister(void)
class UClass * __ptr64 __cdecl Z_Construct_UClass_UMyClass_NotMinimalAPI(void)
class UClass * __ptr64 __cdecl Z_Construct_UClass_UMyClass_NotMinimalAPI_NoRegister(void)
private: static class UClass * __ptr64 __cdecl UMyClass_MinimalAPI::GetPrivateStaticClass(void)
private: static class UClass * __ptr64 __cdecl UMyClass_MinimalAPI_BlueprintFunctionLibary::GetPrivateStaticClass(void)
private: static class UClass * __ptr64 __cdecl UMyClass_MinimalAPI_BlueprintType::GetPrivateStaticClass(void)
public: __cdecl UMyClass_MinimalAPI::UMyClass_MinimalAPI(class FObjectInitializer const & __ptr64) __ptr64
public: __cdecl UMyClass_MinimalAPI::UMyClass_MinimalAPI(class FVTableHelper & __ptr64) __ptr64
public: __cdecl UMyClass_MinimalAPI_BlueprintFunctionLibary::UMyClass_MinimalAPI_BlueprintFunctionLibary(class FObjectInitializer const & __ptr64) __ptr64
public: __cdecl UMyClass_MinimalAPI_BlueprintFunctionLibary::UMyClass_MinimalAPI_BlueprintFunctionLibary(class FVTableHelper & __ptr64) __ptr64
public: __cdecl UMyClass_MinimalAPI_BlueprintType::UMyClass_MinimalAPI_BlueprintType(class FObjectInitializer const & __ptr64) __ptr64
public: __cdecl UMyClass_MinimalAPI_BlueprintType::UMyClass_MinimalAPI_BlueprintType(class FVTableHelper & __ptr64) __ptr64
public: static void __cdecl UMyClass_MinimalAPI_BlueprintFunctionLibary::MyFuncInMinimalAPIWithAPI(void)
public: virtual __cdecl UMyClass_MinimalAPI::~UMyClass_MinimalAPI(void) __ptr64
public: virtual __cdecl UMyClass_MinimalAPI_BlueprintFunctionLibary::~UMyClass_MinimalAPI_BlueprintFunctionLibary(void) __ptr64
public: virtual __cdecl UMyClass_MinimalAPI_BlueprintType::~UMyClass_MinimalAPI_BlueprintType(void) __ptr64
public: void __cdecl UMyClass_MinimalAPI::`default constructor closure'(void) __ptr64
public: void __cdecl UMyClass_MinimalAPI_BlueprintFunctionLibary::`default constructor closure'(void) __ptr64
public: void __cdecl UMyClass_MinimalAPI_BlueprintType::`default constructor closure'(void) __ptr64
```

![Untitled](Untitled%201.png)

When calling across modules, a link error will be triggered because there is no DLL export.

```cpp
UMyClass_MinimalAPI* a = NewObject<UMyClass_MinimalAPI>();

//First error
//error LNK2019: unresolved external symbol "public: void __cdecl UMyClass_MinimalAPI::MyFunc(void)" (?MyFunc@UMyClass_MinimalAPI@@QEAAXXZ) referenced in function "public: void __cdecl UMyClass_UseMinimalAPI::TestFunc(void)" (?TestFunc@UMyClass_UseMinimalAPI@@QEAAXXZ)
//a->MyFunc();

a->MyProperty++;

//Second error
//error LNK2019: unresolved external symbol "private: static class UClass * __cdecl UMyClass_NotMinimalAPI::GetPrivateStaticClass(void)" (?GetPrivateStaticClass@UMyClass_NotMinimalAPI@@CAPEAVUClass@@XZ)
//referenced in function "class UMyClass_NotMinimalAPI * __cdecl NewObject<class UMyClass_NotMinimalAPI>(class UObject *)" (??$NewObject@VUMyClass_NotMinimalAPI@@@@YAPEAVUMyClass_NotMinimalAPI@@PEAVUObject@@@Z)
auto* a = NewObject<UMyClass_NotMinimalAPI>();

//Third error
//error LNK2019: unresolved external symbol "public: static void __cdecl UMyClass_MinimalAPI_BlueprintFunctionLibary::MyFuncInMinimalAPI(void)" (?MyFuncInMinimalAPI@UMyClass_MinimalAPI_BlueprintFunctionLibary@@SAXXZ)
//referenced in function "public: void __cdecl UMyClass_UseMinimalAPI::TestFunc(void)" (?TestFunc@UMyClass_UseMinimalAPI@@QEAAXXZ)
UMyClass_MinimalAPI_BlueprintFunctionLibary::MyFuncInMinimalAPI();

UMyClass_MinimalAPI_BlueprintFunctionLibary::MyFuncInMinimalAPIWithAPI();
```