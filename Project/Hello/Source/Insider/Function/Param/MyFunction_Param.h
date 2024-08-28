// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyFunction_Param.generated.h"

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyFunction_Param :public UBlueprintFunctionLibrary
{
public:
	GENERATED_BODY()
public:
	//Array
	UFUNCTION(BlueprintPure, CustomThunk, meta = (ArrayParm = "TargetArray"))
	static int32 MyArray_Count(const TArray<int32>& TargetArray);
	static int32 GenericMyArray_Count(const void* TargetArray, const FArrayProperty* ArrayProp);
	DECLARE_FUNCTION(execMyArray_Count);

	UFUNCTION(BlueprintPure, CustomThunk, meta = (ArrayParm = "ArrayA,ArrayB"))
	static int32 MyArray_CompareSize(const TArray<int32>& ArrayA, const TArray<int32>& ArrayB);
	static int32 GenericMyArray_CompareSize(void* ArrayA, const FArrayProperty* ArrayAProp, void* ArrayB, const FArrayProperty* ArrayBProp);
	DECLARE_FUNCTION(execMyArray_CompareSize);

public:
	//Map
	UFUNCTION(BlueprintPure, CustomThunk, meta = (MapParam = "TargetMap"))
	static int32 MyMap_Count(const TMap<int32, int32>& TargetMap);
	static int32 GenericMyMap_Count(const void* TargetMap, const FMapProperty* MapProperty);
	DECLARE_FUNCTION(execMyMap_Count);


	UFUNCTION(BlueprintPure, CustomThunk, meta = (MapParam = "MapA,MapB"))
	static int32 MyMap_CompareSize(const TMap<int32, int32>& MapA, const TMap<int32, int32>& MapB);
	static int32 GenericMyMap_CompareSize(void* MapA, const FMapProperty* MapAProp, void* MapB, const FMapProperty* MapBProp);
	DECLARE_FUNCTION(execMyMap_CompareSize);

	UFUNCTION(BlueprintCallable, CustomThunk, meta = (MapParam = "TargetMap", MapKeyParam = "Key", MapValueParam = "Value"))
	static bool MyMap_FindOrAdd(const TMap<int32, int32>& TargetMap, const int32& Key, const int32& Value);
	static bool GenericMyMap_FindOrAdd(const void* TargetMap, const FMapProperty* MapProperty, const void* KeyPtr, const void* ValuePtr);
	DECLARE_FUNCTION(execMyMap_FindOrAdd);

public:
	UFUNCTION(BlueprintCallable, CustomThunk, meta = (SetParam = "SetA|ItemA,SetB|ItemB"))
	static void MySet_Add2(const TSet<int32>& SetA, const int32& ItemA, const TSet<int32>& SetB, const int32& ItemB);
	static void GenericMySet_Add2(const void* TargetSet, const FSetProperty* SetA, const void* ItemA, const FSetProperty* SetB, const void* ItemB);
	DECLARE_FUNCTION(execMySet_Add2);

public:
	UFUNCTION(BlueprintCallable, meta = (AutoCreateRefTerm = "Location,Value"))
	static bool MyFunc_HasAutoCreateRefTerm(const FVector& Location, const int32& Value) { return false; }

	UFUNCTION(BlueprintCallable)
	static bool MyFunc_NoAutoCreateRefTerm(const FVector& Location, const int32& Value) { return false; }

	UFUNCTION(BlueprintCallable)
	static bool MyFunc_NoRef(FVector Location, int32 Value) { return false; }

public:
	//DataTable
	UFUNCTION(BlueprintCallable, meta = (DataTablePin="CurveTable"))
	static void GetMyCurveTableRow(UCurveTable* CurveTable, FName MyRowName, float InXY, float& OutXY,const FString& ContextString){}
	
	UFUNCTION(BlueprintCallable, meta = (DataTablePin="TargetTable"))
	static bool HasMyDataTableRow(UDataTable* TargetTable, FName MyRowName,FName OtherRowName){return false;}
};

