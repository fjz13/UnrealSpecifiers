// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MyProperty_SaveGame.generated.h"

USTRUCT(BlueprintType)
struct FMySaveGameStruct
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString MyString_Default;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,SaveGame)
		FString MyString_SaveGame;
};


UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyProperty_SaveGame :public USaveGame
{
public:
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyInt_Default = 123;
	//PropertyFlags:	CPF_Edit | CPF_BlueprintVisible | CPF_ZeroConstructor | CPF_SaveGame | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
		int32 MyInt_SaveGame = 123;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,SaveGame)
		FMySaveGameStruct MyStruct;
};

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyProperty_SaveGame_Test :public UObject
{
	GENERATED_BODY()
public:
	static void SaveGame();
	static void LoadGame();
	static void RunTest();
	static UMyProperty_SaveGame* LoadGameFromMemory(const TArray<uint8>& InSaveData);
	static bool SaveGameToMemory(UMyProperty_SaveGame* SaveGameObject, TArray<uint8>& OutSaveData);
};
