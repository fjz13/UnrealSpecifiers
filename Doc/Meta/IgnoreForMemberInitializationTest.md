# IgnoreForMemberInitializationTest

Description: 使得该属性忽略结构的未初始验证。
Usage: UPROPERTY
Feature: Behavior
Group: Struct
Type: bool
LimitedType: C++结构下的属性
Status: Done

使得该属性忽略结构的未初始验证。

- 所谓未初始化，指的是C++结构里的变量没有在构造函数里初始化，也没有直接写上初始值
- 结构未初始验证指的是引擎提供的验证工具，可采用控制台命令“CoreUObject.AttemptToFindUninitializedScriptStructMembers”调用。然后会输出引擎内所有未初始化的变量信息。
- UE里的USTRUCT只是一个纯C++结构，不像用UCLASS定义的类都是一个UObject，后者的UPROPERTY属性会自动的都初始化为0，而结构里的UPROPERTY并不会自动的初始化，因此就需要我们手动的初始化。
- 从实践来说，如果开发者清楚知道某变量未初始化不会影响逻辑，那即使未初始化也并没有关系。但现实是往往大家绝大多数情况下只是单纯的犯懒或者遗忘给属性初始化。因此还是建议大家尽量给结构里的所有属性都初始化值。但一些特殊情况下，某些属性确实不适合初始化，比如源码例子里一些FGuid变量，只在真正用到的时候才手动赋值，在这之前初始化什么值其实都意义不大。在这种情况下，就可以用IgnoreForMemberInitializationTest来使该属性忽略这个验证，避免输出报错信息。

测试代码：

```cpp
USTRUCT(BlueprintType)
struct INSIDER_API FMyStruct_InitTest
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MyProperty;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta=(IgnoreForMemberInitializationTest))
	int32 MyProperty_IgnoreTest;
};
```

测试结果：

可见MyProperty因为没有IgnoreForMemberInitializationTest就报错了。

```cpp
在控制台调用CoreUObject.AttemptToFindUninitializedScriptStructMembers后：

LogClass: Error: IntProperty FMyStruct_InitTest::MyProperty is not initialized properly. Module:Insider File:Property/Struct/MyProperty_Struct.h
```

原理：

这个命令行调用AttemptToFindUninitializedScriptStructMembers，继而继续调用FindUninitializedScriptStructMembers来查找出UScriptStruct中的未初始化变量。具体的找出方式可以在该函数中细看。

```cpp

static void FindUninitializedScriptStructMembers(UScriptStruct* ScriptStruct, EScriptStructTestCtorSyntax ConstructorSyntax, TSet<const FProperty*>& OutUninitializedProperties)
{

		for (const FProperty* Property : TFieldRange<FProperty>(ScriptStruct, EFieldIteratorFlags::ExcludeSuper))
	{
#if	WITH_EDITORONLY_DATA
		static const FName NAME_IgnoreForMemberInitializationTest(TEXT("IgnoreForMemberInitializationTest"));
		if (Property->HasMetaData(NAME_IgnoreForMemberInitializationTest))
		{
			continue;
		}
#endif // WITH_EDITORONLY_DATA

}

//由这个调用
FStructUtils::AttemptToFindUninitializedScriptStructMembers();

// 命令行调用
CoreUObject.AttemptToFindUninitializedScriptStructMembers
```