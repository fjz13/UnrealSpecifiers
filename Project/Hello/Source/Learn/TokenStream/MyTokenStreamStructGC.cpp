// Fill out your copyright notice in the Description page of Project Settings.

#include "MyTokenStreamStructGC.h"
#include "MyTokenStreamClass2.h"

FMyTokenStreamStructGC::FMyTokenStreamStructGC()
{
	mOtherObject = NewObject<UMyTokenStreamClass2>();
}

void FMyTokenStreamStructGC::AddReferencedObjects(FReferenceCollector& Collector)
{
	//Collector.AddReferencedObject(mOtherObject);

}
