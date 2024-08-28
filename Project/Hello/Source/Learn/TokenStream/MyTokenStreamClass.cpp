// Fill out your copyright notice in the Description page of Project Settings.

#include "MyTokenStreamClass.h"

UMyTokenStreamClass::UMyTokenStreamClass()
{
}

void UMyTokenStreamClass::AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector)
{
	Super::AddReferencedObjects(InThis, Collector);

	/*UMyTokenStreamClass* This = CastChecked<UMyTokenStreamClass>(InThis);

	if (This->NonGCObjectValue)
	{
		Collector.AddReferencedObject(This->NonGCObjectValue);
	}

	This->GCStructValue.AddReferencedObjects(Collector);

	for (FMyTokenStreamStructGC& i: This->GCStructArrayValue)
	{
		i.AddReferencedObjects(Collector);
	}*/
}

