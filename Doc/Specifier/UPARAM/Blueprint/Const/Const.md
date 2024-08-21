# Const

- **功能描述：** 指定该函数参数不可更改
- **元数据类型：** bool
- **引擎模块：** Blueprint, Parameter
- **作用机制：** 在PropertyFlags中加入[CPF_ConstParm](../../../../Flags/EPropertyFlags/CPF_ConstParm.md)，在Meta中加入[NativeConst](../../../../Meta/Blueprint/NativeConst.md)
- **常用程度：** ★

指定该函数参数不可更改。

如果在C++代码的参数上直接加const，则会自动的被UHT识别并添加CPF_ConstParm 标志，以及NativeConst元数据。但也可以手动加上UPARAM(const)来强制UHT添加CPF_ConstParm，效果见下面蓝图中的Out节点，把输出参数变成了输入参数。

虽然不知道什么情况下需要手动添加，因此在源码中没有找到实际的用例。能想到的用处是在蓝图层面使它变成const输入参数，但是在C++层面依然是可变的引用参数，方便在C++里调用一些非const的方法。

## 测试代码：

```cpp
//PropertyFlags:	CPF_ConstParm | CPF_Parm | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic 
	UFUNCTION(BlueprintCallable)
	FString MyFuncTestParam_ConstInt(UPARAM(const) int value);

	//PropertyFlags:	CPF_ConstParm | CPF_Parm | CPF_OutParm | CPF_ZeroConstructor | CPF_ReferenceParm | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic 
	UFUNCTION(BlueprintCallable)
	FString MyFuncTestParam_ConstIntOut(UPARAM(const) int& value);

	//(NativeConst = )
	//PropertyFlags:	CPF_ConstParm | CPF_Parm | CPF_OutParm | CPF_ZeroConstructor | CPF_ReferenceParm | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic 
	UFUNCTION(BlueprintCallable)
	FString MyFuncTestParam_ConstIntRef(UPARAM(const) const int& value);

	//PropertyFlags:	CPF_Parm | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic 
	UFUNCTION(BlueprintCallable)
	FString MyFuncTestParam_NoConstInt(int value);

	//PropertyFlags:	CPF_Parm | CPF_OutParm | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic 
	UFUNCTION(BlueprintCallable)
	FString MyFuncTestParam_NoConstIntOut(int& value);

	//(NativeConst = )
	//PropertyFlags:	CPF_ConstParm | CPF_Parm | CPF_OutParm | CPF_ZeroConstructor | CPF_ReferenceParm | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic 
	UFUNCTION(BlueprintCallable)
	FString MyFuncTestParam_NoConstIntRef(const int& value);
```

## 蓝图节点：

MyFuncTestParam_ConstIntOut的输出Value变成了输入的Value，因为不能改变。

![Untitled](Untitled.png)

## 原理代码：

在代码中实际出现const，就会增加CPF_ConstParam Flag。

```cpp
\Engine\Source\Programs\Shared\EpicGames.UHT\Parsers\UhtPropertyParser.cs 1030

if (propertySettings.PropertyCategory != UhtPropertyCategory.Member && !isTemplateArgument)
{
	// const before the variable type support (only for params)
	if (tokenReader.TryOptional("const"))
	{
		propertySettings.PropertyFlags |= EPropertyFlags.ConstParm;
		propertySettings.MetaData.Add(UhtNames.NativeConst, "");
	}
}
```