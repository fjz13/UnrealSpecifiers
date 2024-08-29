// Fill out your copyright notice in the Description page of Project Settings.

#include "MyTokenStreamStructCycle.h"
#include "MyTokenStreamClass.h"

FMyTokenStreamStructCycle::FMyTokenStreamStructCycle()
{
	//CycleObject = NewObject<UMyTokenStreamClass>();//会导致CDO来循环创建
}
