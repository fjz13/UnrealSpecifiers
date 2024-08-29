// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPython_ScriptMethod.h"
#include "Utility/InsiderSubsystem.h"

void UMyPython_ScriptMethod_Test::MyFuncOnObject(UMyPython_ScriptMethod* obj, FString val)
{
	UInsiderSubsystem::Get().PrintStringEx(nullptr, __FUNCTION__);
}


void UMyPython_ScriptMethod_Test::MyFuncOnObject2(UMyPython_ScriptMethod* obj, FString val)
{
	UInsiderSubsystem::Get().PrintStringEx(nullptr, __FUNCTION__);
}

void UMyPython_ScriptMethod_Test::SetStringOnStruct(const FMyPythonStruct_ScriptMethod& myStruct, FString val)
{
	UInsiderSubsystem::Get().PrintStringEx(nullptr, __FUNCTION__);
}

void UMyPython_ScriptMethod_Test::SetStringOnStructMutable(const FMyPythonStruct_ScriptMethod& myStruct, FString val)
{
	myStruct.MyString = val;
	UInsiderSubsystem::Get().PrintStringEx(nullptr, __FUNCTION__);
}

void UMyPython_ScriptMethod_Test::SetStringOnStructViaRef(FMyPythonStruct_ScriptMethod& myStruct, FString val)
{
	myStruct.MyString = val;
	UInsiderSubsystem::Get().PrintStringEx(nullptr, __FUNCTION__);
}

FMyPythonStruct_ScriptMethod UMyPython_ScriptMethod_Test::AppendStringOnStruct(const FMyPythonStruct_ScriptMethod& myStruct, FString val)
{
	FMyPythonStruct_ScriptMethod Result = myStruct;
	Result.MyString += val;
	return Result;
}

FMyPythonStruct_ScriptMethod UMyPython_ScriptMethod_Test::AppendStringOnStructReturn(const FMyPythonStruct_ScriptMethod& myStruct, FString val)
{
	FMyPythonStruct_ScriptMethod Result = myStruct;
	Result.MyString += val;
	return Result;
}

FMyPythonStruct_ScriptMethod UMyPython_ScriptMethod_Test::AppendStringOnStructViaRef(FMyPythonStruct_ScriptMethod& myStruct, FString val)
{
	myStruct.MyString += val;
	return myStruct;
}

//FMyPythonStruct_ScriptMethod UMyPython_ScriptMethod_Test::AppendStringOnStructViaRefReturn(FMyPythonStruct_ScriptMethod& myStruct, FString val)
//{
//	myStruct.MyString += val;
//	return myStruct;
//}
//
