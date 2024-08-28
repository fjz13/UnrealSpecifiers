// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/GCObject.h"

class UMyTokenStreamClass2;


class LEARN_API FMyTokenStreamStructGC:public FGCObject
{
public:
	FMyTokenStreamStructGC();
public:
	virtual FString GetReferencerName() const override{return TEXT("MyTokenStreamStructGC"); }

	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
public:
	UMyTokenStreamClass2* mOtherObject = nullptr;

};
