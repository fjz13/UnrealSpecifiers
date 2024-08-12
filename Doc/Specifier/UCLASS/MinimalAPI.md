# MinimalAPI

Type: bool
Feature: DllExport
Description: 最小化API，向其他模块只暴露该类的类型信息，也可以被CastTo，但是该类的函数不导出（除非使用inline），不能跨模块被调用，但蓝图依然可以正常访问。
这个选项节省了编译时间，因为不需要暴露出所有的函数。
EClassFlagsOperation: |=
EClassFlags: CLASS_MinimalAPI (../../Flags/EClassFlags/CLASS_MinimalAPI.md)
Status: Done

不导出该类的属性和函数，只导出类型信息，所以其他引用的模块可以利用指针来做转换，但是不能调用上面的函数。好处是可以缩短编译信息。注意MinimalAPI不能和MODULENAME_API一起使用，因为MinimalAPI就是用来不导出的，而MODULENAME_API就是用来导出的。但是MinimalAPI的效果并不等价于不写MODULENAME_API的效果，因为MinimalAPI还会导出GetPrivateStaticClass用来允许NewObject。所以如果一个类完全不想让另一个模块知道，则不需要写任何导出。而如果想让另一个模块知道类型，但是完全不能调用函数，则可以用MinimalAPI来防止。游戏的模块推荐不导出。插件的模块外部的推荐导出，内部的基类可以考虑MinimalAPI，私有类则可以完全不导出。引擎里使用MinimalAPI还是非常多的，生成的效果是这些类可以作为变量使用，但不能继承和调用方法。

一般是配合BlueprintType使用，这样就可以在蓝图中作为变量。

```cpp
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
```

可以正常在蓝图中调用函数和属性。蓝图函数库中的方法也可以调用，说明UHT对MinimalAPI还是依然生成反射的调用信息的，蓝图调用是只需要反射信息就可以的，因为是自己模块把函数和属性的指针注册到系统里，因此并不需要dll导出。只不过在dll导出工具里查看dll导出的函数列表并没有该函数。

![Untitled](MinimalAPI/Untitled.png)

dll导出：

![Untitled](MinimalAPI/Untitled%201.png)

在跨模块调用的时候，因为没有dll导出，因此会触发链接错误。

```cpp
UMyClass_MinimalAPI* a = NewObject<UMyClass_MinimalAPI>();

//error LNK2019: unresolved external symbol "public: void __cdecl UMyClass_MinimalAPI::MyFunc(void)" (?MyFunc@UMyClass_MinimalAPI@@QEAAXXZ) referenced in function "public: void __cdecl UMyClass_UseMinimalAPI::TestFunc(void)" (?TestFunc@UMyClass_UseMinimalAPI@@QEAAXXZ)
//a->MyFunc();

a->MyProperty++;

//第二种错误
//error LNK2019: unresolved external symbol "private: static class UClass * __cdecl UMyClass_NotMinimalAPI::GetPrivateStaticClass(void)" (?GetPrivateStaticClass@UMyClass_NotMinimalAPI@@CAPEAVUClass@@XZ)
//referenced in function "class UMyClass_NotMinimalAPI * __cdecl NewObject<class UMyClass_NotMinimalAPI>(class UObject *)" (??$NewObject@VUMyClass_NotMinimalAPI@@@@YAPEAVUMyClass_NotMinimalAPI@@PEAVUObject@@@Z)
auto* a = NewObject<UMyClass_NotMinimalAPI>();

//第三种错误
//error LNK2019: unresolved external symbol "public: static void __cdecl UMyClass_MinimalAPI_BlueprintFunctionLibary::MyFuncInMinimalAPI(void)" (?MyFuncInMinimalAPI@UMyClass_MinimalAPI_BlueprintFunctionLibary@@SAXXZ) 
//referenced in function "public: void __cdecl UMyClass_UseMinimalAPI::TestFunc(void)" (?TestFunc@UMyClass_UseMinimalAPI@@QEAAXXZ)
UMyClass_MinimalAPI_BlueprintFunctionLibary::MyFuncInMinimalAPI();

UMyClass_MinimalAPI_BlueprintFunctionLibary::MyFuncInMinimalAPIWithAPI();
```