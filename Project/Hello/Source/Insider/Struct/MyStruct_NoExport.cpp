// Fill out your copyright notice in the Description page of Project Settings.

#include "MyStruct_NoExport.h"


//链入函数声明，在其他的cpp里已经有实现，所以可以正常调用到
INSIDER_API UScriptStruct* Z_Construct_UScriptStruct_FMyStruct_NoExport();
UPackage* Z_Construct_UPackage__Script_Insider();

static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_MyStruct_NoExport;

class UScriptStruct* FMyStruct_NoExport::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_MyStruct_NoExport.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_MyStruct_NoExport.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FMyStruct_NoExport, Z_Construct_UPackage__Script_Insider(), TEXT("MyStruct_NoExport"));
	}
	return Z_Registration_Info_UScriptStruct_MyStruct_NoExport.OuterSingleton;
}


template<> INSIDER_API UScriptStruct* StaticStruct<FMyStruct_NoExport>()
{
	return FMyStruct_NoExport::StaticStruct();
}

