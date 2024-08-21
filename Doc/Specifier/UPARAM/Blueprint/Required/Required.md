# Required

- **功能描述：** 指定函数的参数节点必须连接提供一个值

- **元数据类型：** bool
- **引擎模块：** Blueprint, Parameter
- **作用机制：** 在PropertyFlags中加入[CPF_RequiredParm](../../../../Flags/EPropertyFlags/CPF_RequiredParm.md)
- **常用程度：** ★★

指定函数的参数节点必须连接个变量来提供一个值。

如果参数上有提供默认值，该标志依然会忽略默认值，认为还是没提供值。还是必须要连接变量。

## 测试代码：

```cpp
//PropertyFlags:	CPF_Parm | CPF_ZeroConstructor | CPF_RequiredParm | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic 
	UFUNCTION(BlueprintCallable)
	FString MyFuncTestParam_RequiredObject(UPARAM(Required) UObject* objValue);

	//(CPP_Default_intValue = 123, ModuleRelativePath = Function/Param/MyFunction_TestParam.h)
	//PropertyFlags:	CPF_Parm | CPF_ZeroConstructor | CPF_RequiredParm | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic 
	UFUNCTION(BlueprintCallable)
	FString MyFuncTestParam_RequiredInt(UPARAM(Required) int intValue=123);
```

## 蓝图节点：

![Untitled](Untitled.png)

如果不连一个节点，编译时会报错：

Pin  Int Value  must be linked to another node (in  My Func Test Param Required Int )
Pin  Obj Value  must be linked to another node (in  My Func Test Param Required Object )

## 原理：

根据这个标记来判断。

```cpp
const bool bIsRequiredParam = Param->HasAnyPropertyFlags(CPF_RequiredParm);
	// Don't let the user edit the default value if the parameter is required to be explicit.
	Pin->bDefaultValueIsIgnored |= bIsRequiredParam;
```