// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyTokenStreamStructGC.h"
#include "MyTokenStreamStructPure.h"
#include "MyTokenStreamStructRef.h"
#include "MyTokenStreamInterface.h"
#include "MyTokenStreamStructCycle.h"
#include "MyTokenStreamStructObject.h"
#include "MyTokenStreamStructCustom.h"



#include "MyTokenStreamClass.generated.h"

class UMyTokenStreamClass2;


UCLASS(Blueprintable, Blueprintable)
class LEARN_API UMyTokenStreamClass :public UObject
{
	GENERATED_BODY()
public:
	UMyTokenStreamClass();

	static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);

public:
	/*UPROPERTY()
		float FloatValue;
	UPROPERTY()
		int IntValue;
	UPROPERTY()
		FString StringValue;*/
//	UPROPERTY()
//		UMyTokenStreamClass2* ObjectValue;
//
//	UPROPERTY()
//		FMyTokenStreamStructPure PureStructValue;
//
//	UPROPERTY()
//		FMyTokenStreamStructRef RefStructValue;
//
//	UPROPERTY()
//		FMyTokenStreamStructObject ObjectStructValue;
//
//	UPROPERTY()
//		FMyTokenStreamStructCustom CustomStructValue;
//
//	UPROPERTY()
//		TScriptInterface<IMyTokenStreamInterface> InterfaceValue;
//
//
//public:	//array
//	/*UPROPERTY()
//		TArray<int> IntArrayValue;
//
//	UPROPERTY()
//		TArray<FString> StringArrayValue;*/
//
//	UPROPERTY()
//		TArray<UMyTokenStreamClass2*> ObjectArrayValue;
//
//	UPROPERTY()
//		TArray<FMyTokenStreamStructPure> PureStructArrayValue;
//
//	UPROPERTY()
//		TArray<FMyTokenStreamStructRef> RefStructArrayValue;
//
//	UPROPERTY()
//		TArray<FMyTokenStreamStructObject> ObjectStructArrayValue;
//
//	UPROPERTY()
//		TArray<FMyTokenStreamStructCustom> CustomStructArrayValue;	//���ᱻ����
//
//	UPROPERTY()
//		TArray<TScriptInterface<IMyTokenStreamInterface>> InterfaceArrayValue;
//
//	/*UPROPERTY()
//		int IntArrayValueFixed[10];
//
//	UPROPERTY()
//		FString StringArrayValueFixed[10];*/
//
//	UPROPERTY()
//		UMyTokenStreamClass2* ObjectArrayValueFixed[10];
//
//	UPROPERTY()
//		FMyTokenStreamStructPure PureStructArrayValueFixed[10];
//
//	UPROPERTY()
//		FMyTokenStreamStructRef RefStructArrayValueFixed[10];
//
//	UPROPERTY()
//		TScriptInterface<IMyTokenStreamInterface> InterfaceArrayValueFixed[10];
//
//public:	//map
//	UPROPERTY()
//		TMap<int, UMyTokenStreamClass2*> IntObjectMap;
//
//public://set
//	UPROPERTY()
//		TSet<UMyTokenStreamClass2*> ObjectSet;

public://cycle
	UPROPERTY()
		FMyTokenStreamStructCycle CycleStructValue;

	UPROPERTY()
		TSubclassOf<AActor> MyActorClass;
private:
	UMyTokenStreamClass2* NonGCObjectValue;
	FMyTokenStreamStructGC GCStructValue;
	TArray<FMyTokenStreamStructGC> GCStructArrayValue;
};
