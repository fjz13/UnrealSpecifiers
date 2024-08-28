// Fill out your copyright notice in the Description page of Project Settings.

#include "MyObjectWithSubobject.h"
#include "MyObject.h"

UMyObjectWithSubobject::UMyObjectWithSubobject()
{
	MySubObject = CreateDefaultSubobject<UMyObject>("MySub");
}

