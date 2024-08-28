// Fill out your copyright notice in the Description page of Project Settings.

#include "MyFunction_OutputType.h"
#include <Kismet/GameplayStatics.h>
#include <EngineUtils.h>


TArray<AActor*> UMyFunctionLibrary_OutputTypeTest::MyGetAnimals(TSubclassOf<AMyAnimalActor> ActorClassType)
{
	TArray<AActor*> result;
	return result;
}

void UMyFunctionLibrary_OutputTypeTest::MyGetAnimalsOut(TSubclassOf<AMyAnimalActor> ActorClassType, TArray<AActor*>& OutActors)
{


}

void UMyFunctionLibrary_OutputTypeTest::MyGetAnimalsOut2(TSubclassOf<AMyAnimalActor> ActorClassType, AActor*& FirstOutActor, TArray<AActor*>& OutActors)
{

}

TArray<AActor*> UMyFunctionLibrary_OutputTypeTest::MyGetAnimalsWithActor(AMyAnimalActor* ExampleActor)
{
	TArray<AActor*> result;
	return result;
}

TArray<AActor*> UMyFunctionLibrary_OutputTypeTest::MyGetAnimalsWithActorArray(TArray<AMyAnimalActor*> ExampleActorArray)
{
	TArray<AActor*> result;
	return result;
}

TArray<AActor*> UMyFunctionLibrary_OutputTypeTest::MyGetAnimalsWithStructProperty(const FMyOutputTypeArgs& Args)
{
	TArray<AActor*> result;
	MyGetAnimalsOut(Args.ActorClassType, result);
	return result;
}

//
//TArray<AActor*> UMyFunctionLibrary_OutputTypeTest::MyGetAnimalsWithActorSoft( TSoftObjectPtr<AMyAnimalActor> ExampleActor)
//{
//	TArray<AActor*> result;
//	if (ExampleActor != nullptr)
//	{
//		MyGetAnimalsOut(WorldContextObject, ExampleActor->GetClass(), result);
//	}
//	return result;
//}
//
//TArray<AActor*> UMyFunctionLibrary_OutputTypeTest::MyGetAnimalsWithActorSoftClass( TSoftClassPtr<AMyAnimalActor> ExampleActorClass)
//{
//	TArray<AActor*> result;
//	if (ExampleActorClass != nullptr)
//	{
//		MyGetAnimalsOut(WorldContextObject, ExampleActorClass.Get(), result);
//	}
//	return result;
//}
