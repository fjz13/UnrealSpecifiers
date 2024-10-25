# Required

- **Function Description:** The parameter node for the specified function must be connected to supply a value

- **Metadata Type:** bool
- **Engine Module:** Blueprint, Parameter
- **Action Mechanism:** Include [CPF_RequiredParm](../../../../Flags/EPropertyFlags/CPF_RequiredParm.md) in PropertyFlags
- **Common Usage:** ★★

The parameter node of the specified function must be connected to a variable to supply a value.

If a default value is provided for the parameter, this flag will still disregard the default value, treating it as if no value has been provided. A variable must still be connected.

## Test Code:

```cpp
//PropertyFlags:	CPF_Parm | CPF_ZeroConstructor | CPF_RequiredParm | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
	UFUNCTION(BlueprintCallable)
	FString MyFuncTestParam_RequiredObject(UPARAM(Required) UObject* objValue);

	//(CPP_Default_intValue = 123, ModuleRelativePath = Function/Param/MyFunction_TestParam.h)
	//PropertyFlags:	CPF_Parm | CPF_ZeroConstructor | CPF_RequiredParm | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
	UFUNCTION(BlueprintCallable)
	FString MyFuncTestParam_RequiredInt(UPARAM(Required) int intValue=123);
```

## Blueprint Node:

![Untitled](Untitled.png)

If a node is not connected, an error will be reported during compilation

Pin  Int Value  must be linked to another node (in  My Func Test Param Required Int )
Pin  Obj Value  must be linked to another node (in  My Func Test Param Required Object )

## Principle:

The judgment is based on this marker.

```cpp
const bool bIsRequiredParam = Param->HasAnyPropertyFlags(CPF_RequiredParm);
	// Don't let the user edit the default value if the parameter is required to be explicit.
	Pin->bDefaultValueIsIgnored |= bIsRequiredParam;
```