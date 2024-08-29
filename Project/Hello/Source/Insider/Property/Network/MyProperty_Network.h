// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProperty_Network.generated.h"

USTRUCT(BlueprintType)
struct FMyReplicatedStruct
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString MyString_Default;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,NotReplicated)
		FString MyString_NotReplicated;

		//UPROPERTY(EditAnywhere, BlueprintReadWrite,RepRetry)
		//FString MyString_RepRetry;
};

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyProperty_Network :public AActor
{
public:
	GENERATED_BODY()
protected:
	UFUNCTION()
		void OnRep_MyInt(int32 oldValue); //void OnRep_MyInt();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyInt_Default = 123;

		//PropertyFlags:	CPF_Edit | CPF_BlueprintVisible | CPF_Net | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic 
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
		int32 MyInt_Replicated = 123;

		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
		FMyReplicatedStruct MyStruct_Replicated;


	//UPROPERTY(EditAnywhere, BlueprintReadWrite, NotReplicated)
	//	int32 MyInt_NotReplicated = 123;//Only Struct members can be marked NotReplicated

	//PropertyFlags:	CPF_Edit | CPF_BlueprintVisible | CPF_Net | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_RepNotify | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic 
	//RepNotifyFunc:	OnRep_MyInt
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_MyInt)
		int32 MyInt_ReplicatedUsing = 123;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite,RepRetry)
	//	int32 MyInt_RepRetry = 123;	//'RepRetry' is deprecated.
};

