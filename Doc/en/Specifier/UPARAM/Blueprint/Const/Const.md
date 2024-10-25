# Const

- **Function Description:** Specifies that the function parameters are immutable
- **Metadata Type:** bool
- **Engine Module:** Blueprint, Parameter
- **Action Mechanism:** Add [CPF_ConstParm](../../../../Flags/EPropertyFlags/CPF_ConstParm.md) to PropertyFlags and [NativeConst](../../../../Meta/Blueprint/NativeConst.md) to Meta
- **Commonality:** ★

Specifies that the function parameters are not modifiable.

If "const" is directly added to the parameters in the C++ code, it will be automatically recognized by UHT and the CPF_ConstParm flag, as well as NativeConst metadata, will be added. However, you can also manually add UPARAM(const) to force UHT to add CPF_ConstParm, as seen in the Out node in the blueprint below, which converts the output parameter into an input parameter.

Although it is unclear when manual addition is necessary, no practical examples were found in the source code. The imagined use case is to make it a const input parameter at the blueprint level, while still being a mutable reference parameter in C++, facilitating the invocation of some non-const methods in C++.

## Test Code:

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

## Blueprint Node:

The output Value of MyFuncTestParam_ConstIntOut has become an input Value because it cannot be altered.

![Untitled](Untitled.png)

## Principle Code:

When "const" is actually present in the code, the CPF_ConstParam flag is added.

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