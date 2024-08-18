# ref

功能描述: 使得函数的参数变成引用类型
元数据类型: bool
引擎模块: Blueprint, Parameter
EPropertyFlags: CPF_ReferenceParm (../../Flags/EPropertyFlags/CPF_ReferenceParm.md)
Status: Done
常用程度: 5

普通参数和引用参数的区别是，在获取参数的时候，Ref类型会直接获得实参的引用，而不是拷贝。这样就可以避免拷贝，保存修改。

单纯的&参数是会被解析成输出返回参数，因此要用ref再继续标明。

测试代码：

```cpp
//PropertyFlags:	CPF_Parm | CPF_OutParm | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic 
	UFUNCTION(BlueprintCallable)
	FString MyFuncTestParam_Default(int& refValue);

	//PropertyFlags:	CPF_Parm | CPF_OutParm | CPF_ZeroConstructor | CPF_ReferenceParm | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic 
	UFUNCTION(BlueprintCallable)
	FString MyFuncTestParam_Ref(UPARAM(ref) int& refValue);

	UFUNCTION(BlueprintCallable)
	FString MyFuncTestParam_Copy(int value);
```

蓝图的代码：

![Untitled](ref/Untitled.png)

原理：

ref参数在UHT生成时会用P_GET_PROPERTY_REF来获得

```cpp
#define P_GET_PROPERTY(PropertyType, ParamName)													\
	PropertyType::TCppType ParamName = PropertyType::GetDefaultPropertyValue();					\
	Stack.StepCompiledIn<PropertyType>(&ParamName);

#define P_GET_PROPERTY_REF(PropertyType, ParamName)												\
	PropertyType::TCppType ParamName##Temp = PropertyType::GetDefaultPropertyValue();			\
	PropertyType::TCppType& ParamName = Stack.StepCompiledInRef<PropertyType, PropertyType::TCppType>(&ParamName##Temp);
```