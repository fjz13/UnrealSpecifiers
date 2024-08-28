// Fill out your copyright notice in the Description page of Project Settings.

#include "MyTokenStreamStructObject.h"
#include "MyTokenStreamClass2.h"

FMyTokenStreamStructObject::FMyTokenStreamStructObject()
{
	InnerObject = NewObject<UMyTokenStreamClass2>();
}
