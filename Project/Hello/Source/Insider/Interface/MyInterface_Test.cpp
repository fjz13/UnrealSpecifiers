// Fill out your copyright notice in the Description page of Project Settings.

#include "MyInterface_Test.h"

UMyInterface_Blueprintable::UMyInterface_Blueprintable(const FObjectInitializer&)
{

}

UMyInterface_NotBlueprintable::UMyInterface_NotBlueprintable(const FObjectInitializer&)
{

}


//void IMyInterface::BPFunc() const
//{
//
//}

//void IMyInterface::Func_NativeEvent_Implementation() const
//{
//	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "Cpp_FuncNativeEvent");
//}


UMyInterface_OnlyCpp::UMyInterface_OnlyCpp(const FObjectInitializer&)
{

}
