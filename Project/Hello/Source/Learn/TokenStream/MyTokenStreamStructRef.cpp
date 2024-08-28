// Fill out your copyright notice in the Description page of Project Settings.

#include "MyTokenStreamStructRef.h"
#include "TokenStream/MyTokenStreamClass2.h"

FMyTokenStreamStructRef::FMyTokenStreamStructRef()
{
	mOtherObject = NewObject<UMyTokenStreamClass2>();
}

void FMyTokenStreamStructRef::AddReferencedObjects(FReferenceCollector& Collector)
{
	//Collector.AddReferencedObject(mOtherObject);
}
