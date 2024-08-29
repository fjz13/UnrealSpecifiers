// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "MyClass_NoExport.generated.h"
//UCLASS(noexport)
//class INSIDER_API UMyClass_NoExport :public UObject
//{
//	GENERATED_BODY()
//public:
//};

/*


noexport 在编译和NewObject<UMyClass_NoExport>的时候会报错：
1 > MyClass_NoExport.gen.cpp.obj :
error LNK2019 : unresolved external symbol "private: static void __cdecl UMyClass_NoExport::StaticRegisterNativesUMyClass_NoExport(void)"
(? StaticRegisterNativesUMyClass_NoExport@UMyClass_NoExport@@CAXXZ)
referenced in function "private: static class UClass * __cdecl UMyClass_NoExport::GetPrivateStaticClass(void)"
(? GetPrivateStaticClass@UMyClass_NoExport@@CAPEAVUClass@@XZ)

*/
