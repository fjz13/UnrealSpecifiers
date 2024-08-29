// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonTypes.generated.h"

//These types are all used for testing

UENUM(BlueprintType)
enum class EMyCommonEnum :uint8
{
	First,
	Second,
	Third,
};

UENUM(BlueprintType)
namespace EMyCommonEnumNamespace
{
	enum Type : int
	{
		First,
		Second,
		Third,
	};
}


UENUM(BlueprintType)
enum class EMyCommonEnum2 :uint8
{
	Cat,
	Dog,
};


USTRUCT(BlueprintType)
struct INSIDER_API FMyCommonStruct
{
	GENERATED_BODY()
public:
	FMyCommonStruct() = default;
	FMyCommonStruct(int32 id) :MyInt(id) {}

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 MyInt = 123;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString MyString;

	friend uint32 GetTypeHash(const FMyCommonStruct& item) { return HashCombineFast(item.MyInt, GetTypeHashHelper(item.MyString)); }
	bool operator==(const FMyCommonStruct& other)const { return MyInt == other.MyInt && MyString == other.MyString; }
};


USTRUCT(BlueprintType)
struct INSIDER_API FMyCommonStructChild:public FMyCommonStruct
{
	GENERATED_BODY()
};


USTRUCT(BlueprintType)
struct FMyCommonRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString MyString;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector MyVector={1.f,2.f,3.f};
};


UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyCommonObject :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 MyInt = 123;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString MyString;
};


UCLASS(BlueprintType)
class INSIDER_API UMyCommonObjectChild :public UMyCommonObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ChildFloat = 123.456f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector ChildLocation;
};



UINTERFACE(Blueprintable, MinimalAPI)
class UMyCommonInterface :public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class INSIDER_API IMyCommonInterface
{
	GENERATED_IINTERFACE_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void MyImplementableEvent() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void MyNativeEvent() const;
};


UCLASS(Blueprintable,BlueprintType)
class INSIDER_API AMyActor :public AActor
{
	GENERATED_BODY()
};

UCLASS(Blueprintable,BlueprintType, meta = (BlueprintSpawnableComponent))
class INSIDER_API UMyActorComponent :public UActorComponent
{
	GENERATED_BODY()
};

UCLASS(Blueprintable,BlueprintType, meta = (BlueprintSpawnableComponent))
class INSIDER_API UMyActorChildComponent :public UMyActorComponent
{
	GENERATED_BODY()
};