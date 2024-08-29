// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/CommonTypes.h"

#include "UMyProperty_Container.generated.h"

UENUM(BlueprintType)
enum class EMyArrayEnumNormal :uint8
{
	First,
	Second,
	Third,
	Max,
};


UENUM(BlueprintType)
enum class EMyArrayEnumHidden :uint8
{
	First,
	Second,
	Cat = 5 UMETA(Hidden),
	Third = 2,
	Max = 3,
};


USTRUCT(BlueprintType)
struct INSIDER_API FMyArrayTitleStruct
{
	GENERATED_BODY()
public:
	FMyArrayTitleStruct() = default;
	FMyArrayTitleStruct(int32 id) :MyInt(id) {}
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 MyInt = 123;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString MyString = TEXT("Hello");
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MyFloat = 456.f;
};



UCLASS(BlueprintType)
class INSIDER_API UMyProperty_Container :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ElementDuplicateTest)
	TArray<int32> MyIntArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ElementDuplicateTest, meta = (NoElementDuplicate))
	TArray<int32> MyIntArray_NoElementDuplicate;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ElementDuplicateTest)
	TArray<FMyCommonStruct> MyStructArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ElementDuplicateTest, meta = (NoElementDuplicate))
	TArray<FMyCommonStruct> MyStructArray_NoElementDuplicate;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ElementDuplicateTest)
	TArray<UMyCommonObject*> MyObjectArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ElementDuplicateTest, meta = (NoElementDuplicate))
	TArray<UMyCommonObject*> MyObjectArray_NoElementDuplicate;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditFixedOrderTest)
	TArray<int32> MyIntArray_NoEditFixedOrder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditFixedOrderTest, meta = (EditFixedOrder))
	TArray<int32> MyIntArray_EditFixedOrder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditFixedOrderTest)
	TSet<int32> MyIntSet_NoEditFixedOrder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditFixedOrderTest, meta = (EditFixedOrder))
	TSet<int32> MyIntSet_EditFixedOrder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditFixedOrderTest)
	TMap<int32, FString> MyIntMap_NoEditFixedOrder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditFixedOrderTest, meta = (EditFixedOrder))
	TMap<int32, FString> MyIntMap_EditFixedOrder;
public:
	UPROPERTY(EditAnywhere, Category = ArraySizeEnumTest)
	int32 MyIntArray_NoArraySizeEnum[3];

	UPROPERTY(EditAnywhere, Category = ArraySizeEnumTest, meta = (ArraySizeEnum = "MyArrayEnumNormal"))
	int32 MyIntArray_Normal_HasArraySizeEnum[(int)EMyArrayEnumNormal::Max];

	UPROPERTY(EditAnywhere, Category = ArraySizeEnumTest, meta = (ArraySizeEnum = "MyArrayEnumHidden"))
	int32 MyIntArray_Hidden_HasArraySizeEnum[(int)EMyArrayEnumHidden::Max];
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TitlePropertyTest)
	TArray<FMyArrayTitleStruct> MyStructArray_NoTitleProperty;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TitlePropertyTest, meta = (TitleProperty = "{MyString}[{MyInt}]"))
	TArray<FMyArrayTitleStruct> MyStructArray_HasTitleProperty;

	UPROPERTY(EditAnywhere, Category = TitlePropertyTest, meta = (ArraySizeEnum = "MyArrayEnumNormal",TitleProperty = "{MyString}[{MyInt}]"))
	FMyArrayTitleStruct MyStructArray_IndexAndTitle[(int)EMyArrayEnumNormal::Max];


public:
	UFUNCTION(CallInEditor)
	void ClearInnerObject();
	UFUNCTION(CallInEditor)
	void InitInnerObject();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ReadOnlyKeysTest)
	TMap<int32, FString> MyIntMap_NoReadOnlyKeys;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ReadOnlyKeysTest, meta = (ReadOnlyKeys))
	TMap<int32, FString> MyIntMap_ReadOnlyKeys;
};

