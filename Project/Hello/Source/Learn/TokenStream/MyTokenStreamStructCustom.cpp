// Fill out your copyright notice in the Description page of Project Settings.

#include "MyTokenStreamStructCustom.h"
#include "TokenStream/MyTokenStreamClass2.h"

FMyTokenStreamStructCustom::FMyTokenStreamStructCustom()
{
	mOtherObject = NewObject<UMyTokenStreamClass2>();
}

void FMyTokenStreamStructCustom::AddStructReferencedObjects(class FReferenceCollector& Collector)const
{
	//Collector.AddReferencedObject(const_cast<FMyTokenStreamStructCustom*>(this)->mOtherObject);
}

