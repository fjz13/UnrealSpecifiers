// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProperty_ComponentReference.generated.h"

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyProperty_ComponentReference :public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AllowedClassesTest|FComponentReference", meta = (UseComponentPicker))
	FComponentReference MyComponentReference_NoAllowedClasses;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AllowedClassesTest|FComponentReference", meta = (UseComponentPicker, AllowedClasses = "/Script/Insider.MyActorComponent"))
	FComponentReference MyComponentReference_AllowedClasses;
public:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "DisallowedClassesTest|FComponentReference", meta = (UseComponentPicker))
	FComponentReference MyComponentReference_NoDisallowedClasses;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "DisallowedClassesTest|FComponentReference", meta = (UseComponentPicker, DisallowedClasses = "/Script/Insider.MyActorComponent"))
	FComponentReference MyComponentReference_DisallowedClasses;
public:	//not work
	//	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "GetAllowedClassesTest|FComponentReference", meta = (UseComponentPicker))
	//	FComponentReference MyComponentReference_NoGetAllowedClasses;
	//
	//	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "GetAllowedClassesTest|FComponentReference", meta = (UseComponentPicker, GetAllowedClasses = "MyGetAllowedClassesFunc"))
	//	FComponentReference MyComponentReference_GetAllowedClasses;
	//public:
	UFUNCTION()
	TArray<UClass*> MyGetAllowedClassesFunc();
	//
	//	UFUNCTION()
	//	TArray<UClass*> MyGetDisallowedClassesFunc();

public:
	//not work
		//UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "ExactClassTest|FComponentReference", meta = (UseComponentPicker,AllowedClasses = "/Script/Insider.MyActorChildComponent",GetAllowedClasses = "MyGetAllowedClassesFunc"))
		//FComponentReference MyComponentReference_NoExactClass;

		//UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "ExactClassTest|FComponentReference", meta = (UseComponentPicker, ExactClass, AllowedClasses = "/Script/Insider.MyActorChildComponent",GetAllowedClasses = "MyGetAllowedClassesFunc"))
		//FComponentReference MyComponentReference_ExactClass;


public:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "UseComponentPickerTest")
	FComponentReference MyComponentReference_NoUseComponentPicker;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "UseComponentPickerTest", meta = (UseComponentPicker))
	FComponentReference MyComponentReference_UseComponentPicker;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "UseComponentPicker_AllowAnyActor_Test", meta = (UseComponentPicker,AllowAnyActor))
	FComponentReference MyComponentReference_UseComponentPicker_AllowAnyActor;
public:
	UFUNCTION(BlueprintCallable)
	UActorComponent* MyGetComponent(const FComponentReference& ref);

	UFUNCTION(BlueprintCallable)
	UActorComponent* MyGetComponentSoft(const FSoftComponentReference& ref);
};
