// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPythonTest.h"
#include "Utility/InsiderSubsystem.h"

void UMyPythonTestLibary::MyScriptFunc_None()
{
	UInsiderSubsystem::Get().PrintStringEx(nullptr, TEXT("MyScriptFunc_None"));
}

void UMyPythonTestLibary::MyScriptFuncDefault()
{
	UInsiderSubsystem::Get().PrintStringEx(nullptr, TEXT("MyScriptFuncDefault"));
}

void UMyPythonTestLibary::MyScriptFunc_ScriptName()
{
	UInsiderSubsystem::Get().PrintStringEx(nullptr, TEXT("MyScriptFunc_ScriptName"));
}

void UMyPythonTestLibary::MyScriptFunc_NoExport()
{
	UInsiderSubsystem::Get().PrintStringEx(nullptr, TEXT("MyScriptFunc_NoExport"));
}

//
//void UMyPythonTestLibary::MyTestScriptMethod()
//{
//	UInsiderSubsystem::Get().PrintStringEx(nullptr, TEXT("MyTestScriptMethod"));
//}
//
//void UMyPythonTestLibary::MyTestScriptMethod2(UObject* obj, FString val)
//{
//	FString str = FString::Printf(TEXT("%s:%s"), *obj->GetName(), *val);
//	UInsiderSubsystem::Get().PrintStringEx(nullptr, str);
//}
