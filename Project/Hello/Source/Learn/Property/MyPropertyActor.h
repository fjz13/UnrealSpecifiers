// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enum/MyFlags.h"
#include "Enum/MyEnum.h"
#include "StructUtils/InstancedStruct.h"
#include "MyPropertyActor.generated.h"


UCLASS(Blueprintable)
class LEARN_API AMyPropertyActor :public AActor
{
	GENERATED_BODY()
public:
	AMyPropertyActor();
public:	//UPROPERTY specifiers
	UPROPERTY(BlueprintReadWrite)
		float Float_ReadWrite;

	UPROPERTY(BlueprintReadOnly)
		float Float_ReadOnly;

	UPROPERTY(EditAnywhere)
		float Float_EditAnywhere;

	UPROPERTY(EditDefaultsOnly)
		float Float_EditDefaultsOnly;

	UPROPERTY(EditInstanceOnly)
		float Float_EditInstanceOnly;

	UPROPERTY(VisibleAnywhere)
		float Float_VisibleAnywhere;

	UPROPERTY(VisibleDefaultsOnly)
		float Float_VisibleDefaultsOnly;

	UPROPERTY(VisibleInstanceOnly)
		float Float_VisibleInstanceOnly;


	UPROPERTY(EditAnywhere, SimpleDisplay)
		float Float_SimpleDisplay;

	UPROPERTY(EditAnywhere, AdvancedDisplay)
		float Float_AdvancedDisplay;

	UPROPERTY(EditAnywhere, Category = "MyParent|MyChild")
		float Float_Category;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<float> Float_Array;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, EditFixedSize)
		TArray<float> Float_Array_FixedSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UMyBlueprintableClass* Object_HasClear;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, NoClear)
		class UMyBlueprintableClass* Object_NoClear;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//FStructOnScope StructOnScope;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPROPERTY(EditAnywhere,  Category = InstancedStruct, meta = (BaseStruct = "/Script/Insider.ShopItem"))
		FInstancedStruct MyInstancedStruct;
	UPROPERTY(EditAnywhere,  Category = InstancedStruct, meta = (BaseStruct = "/Script/Insider.ShopItem"))
		TArray<FInstancedStruct> MyInstancedStructArray;
private:
	//Error: BlueprintReadOnly should not be used on private members
	/*UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float Float_Private;*/

	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (AllowPrivateAccess = true))
		float Float_Private_AllowAccess;
public:
	UFUNCTION(BlueprintGetter)	//or BlueprintPure
		float Float_Getter()const {return Float_WithGetter*2.f;}

	UFUNCTION(BlueprintSetter)	//or BlueprintCallable
		void Float_Setter(float NewValue) {Float_WithSetter = NewValue / 4.f;}

private:

	UPROPERTY(EditAnywhere, BlueprintGetter = Float_Getter)
		float Float_WithGetter;

	UPROPERTY(EditAnywhere, BlueprintSetter = Float_Setter)
		float Float_WithSetter;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Bool_Bool;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		uint32 Bool_UInt32 : 1;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 UInt32Value;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString String_FString;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName String_FName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText String_FText;

public://flags
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (Bitmask))
		int32 Flags_Mask;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (Bitmask, BitmaskEnum = "/Script/Insider.MyFlags"))
		int32 Flags_MaskEnum;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		MyEnum Enum_DirectEnum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		MyFlags Flags_DirectFlags;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (Bitmask, BitmaskEnum = "/Script/Insider.MyFlags"))
		MyFlags Flags_DirectFlags_Bitmask;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class ACharacter> CharacterClass;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move", meta = (ExposeOnSpawn))
		FVector PositionMin;
};
