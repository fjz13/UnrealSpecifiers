// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyClass_Optional.generated.h"

//ClassFlags:	CLASS_Optional | CLASS_MatchedSerializers | CLASS_Native | CLASS_RequiredAPI | CLASS_TokenStreamAssembled | CLASS_Intrinsic | CLASS_Constructed 
UCLASS(Optional)
class INSIDER_API UMyClass_Optional :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyProperty = 123;
};

UCLASS()
class INSIDER_API UMyClass_NotOptional :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyProperty = 123;
};


UCLASS()
class INSIDER_API UMyClass_Optional_Test :public UObject
{
	GENERATED_BODY()
public:

#if WITH_EDITORONLY_DATA
	UPROPERTY()
		UMyClass_Optional* MyOptionalObject;

#endif // WITH_EDITORONLY_DATA

public:
	UPROPERTY()
		UMyClass_NotOptional* MyNotOptionalObject;
public:
	static void CreatePackageAndSave();
	static void LoadPackageAndTest();
	static void RunTest();
};