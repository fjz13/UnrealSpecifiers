# ref

Description: 使得函数的参数变成引用类型
Type: bool
Feature: Blueprint, Parameter
EPropertyFlags: CPF_ReferenceParm (../../Flags/EPropertyFlags/CPF_ReferenceParm.md)
Status: Done

普通参数和引用参数的区别是，在获取参数的时候，Ref类型会直接获得实参的引用，而不是拷贝。这样就可以避免拷贝，保存修改。

```jsx
#define P_GET_PROPERTY(PropertyType, ParamName)													\
	PropertyType::TCppType ParamName = PropertyType::GetDefaultPropertyValue();					\
	Stack.StepCompiledIn<PropertyType>(&ParamName);

#define P_GET_PROPERTY_REF(PropertyType, ParamName)												\
	PropertyType::TCppType ParamName##Temp = PropertyType::GetDefaultPropertyValue();			\
	PropertyType::TCppType& ParamName = Stack.StepCompiledInRef<PropertyType, PropertyType::TCppType>(&ParamName##Temp);
```

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