// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProperty_ComponentReference.h"
#include "Common/CommonTypes.h"

TArray<UClass*> AMyProperty_ComponentReference::MyGetAllowedClassesFunc()
{
	TArray<UClass*> classes;
	classes.Add(UMyActorComponent::StaticClass());
	//classes.Add(UMyActorChildComponent::StaticClass());

	return classes;
}

UActorComponent* AMyProperty_ComponentReference::MyGetComponent(const FComponentReference& ref) 
{
	return ref.GetComponent(this);
}

UActorComponent* AMyProperty_ComponentReference::MyGetComponentSoft(const FSoftComponentReference& ref) 
{
	return ref.GetComponent(this);
}

//
//TArray<UClass*> AMyProperty_ComponentReference::MyGetDisallowedClassesFunc()
//{
//	TArray<UClass*> classes;
//	classes.Add(UMyActorComponent::StaticClass());
//	return classes;
//}
