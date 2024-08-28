// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProperty_Inner.generated.h"


USTRUCT(BlueprintType)
struct FMyPropertyInner
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 StructInnerInt = 123;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString StructInnerString;
};

UCLASS(BlueprintType)
class INSIDER_API UMyProperty_InnerSub :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ObjectInnerInt = 123;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ObjectInnerString;
};


UCLASS(BlueprintType, EditInlineNew)
class INSIDER_API UMyProperty_InnerSub_EditInlineNew :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ObjectInnerInt = 123;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ObjectInnerString;
};


UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyProperty_Inner :public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FMyPropertyInner InnerStruct;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ShowInnerProperties))
	FMyPropertyInner InnerStruct_ShowInnerProperties;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMyProperty_InnerSub* InnerObject;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ShowInnerProperties))
	UMyProperty_InnerSub* InnerObject_ShowInnerProperties;

	//(Category = MyProperty_Inner, EditInline = , ModuleRelativePath = Property/MyProperty_Inner.h)
	//CPF_Edit | CPF_BlueprintVisible | CPF_ZeroConstructor | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditInline))
	UMyProperty_InnerSub* InnerObject_EditInline;

	//(Category = MyProperty_Inner, EditInline = true, ModuleRelativePath = Property/MyProperty_Inner.h)
	//CPF_Edit | CPF_BlueprintVisible | CPF_ExportObject | CPF_ZeroConstructor | CPF_InstancedReference | CPF_NoDestructor | CPF_PersistentInstance | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	UMyProperty_InnerSub* InnerObject_Instanced;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMyProperty_InnerSub_EditInlineNew* InnerObject_EditInlineNewClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditInline))
	UMyProperty_InnerSub_EditInlineNew* InnerObject_EditInlineNewClass_EditInline;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	UMyProperty_InnerSub_EditInlineNew* InnerObject_EditInlineNewClass_Instanced;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ShowOnlyInnerProperties))
	FMyPropertyInner InnerStruct_ShowOnlyInnerProperties;

public:
	//Useless
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (FullyExpand="true"))
	FMyPropertyInner InnerStruct_FullyExpand;

public:
	UFUNCTION(CallInEditor)
	void ClearInnerObject();
	UFUNCTION(CallInEditor)
	void InitInnerObject();

	UFUNCTION(CallInEditor)
	void RemoveActorMeta();
	UFUNCTION(CallInEditor)
	void AddActorMeta();
};

