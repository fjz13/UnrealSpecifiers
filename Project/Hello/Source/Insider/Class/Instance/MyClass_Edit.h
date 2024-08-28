// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyClass_Edit.generated.h"


//	ClassFlags:	CLASS_MatchedSerializers | CLASS_Native | CLASS_EditInlineNew | CLASS_RequiredAPI | CLASS_TokenStreamAssembled | CLASS_Intrinsic | CLASS_Constructed 
UCLASS(Blueprintable, EditInlineNew)
class INSIDER_API UMyClass_EditInlineNew :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyProperty;
};

//	ClassFlags:	CLASS_MatchedSerializers | CLASS_Native | CLASS_RequiredAPI | CLASS_TokenStreamAssembled | CLASS_Intrinsic | CLASS_Constructed 
UCLASS(Blueprintable, NotEditInlineNew)
class INSIDER_API UMyClass_NotEditInlineNew :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyProperty;
};



UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyClass_Edit_Test :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = InstancedProperty)
		UMyClass_EditInlineNew* MyEditInlineNew;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = InstancedProperty)
		UMyClass_NotEditInlineNew* MyNotEditInlineNew;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NormalProperty)
		UMyClass_EditInlineNew* MyEditInlineNew_NotInstanced;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NormalProperty)
		UMyClass_NotEditInlineNew* MyNotEditInlineNew_NotInstanced;
};
