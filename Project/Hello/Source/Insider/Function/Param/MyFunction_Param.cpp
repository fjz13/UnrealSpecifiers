// Fill out your copyright notice in the Description page of Project Settings.

#include "MyFunction_Param.h"

int32 UMyFunction_Param::MyArray_Count(const TArray<int32>& TargetArray)
{
	return 0;
}

int32 UMyFunction_Param::GenericMyArray_Count(const void* TargetArray, const FArrayProperty* ArrayProp)
{
	if (TargetArray)
	{
		FScriptArrayHelper ArrayHelper(ArrayProp, TargetArray);

		return ArrayHelper.Num();
	}

	return 0;
}


DEFINE_FUNCTION(UMyFunction_Param::execMyArray_Count)
{
	Stack.MostRecentProperty = nullptr;
	Stack.StepCompiledIn<FArrayProperty>(NULL);
	void* ArrayAddr = Stack.MostRecentPropertyAddress;
	FArrayProperty* ArrayProperty = CastField<FArrayProperty>(Stack.MostRecentProperty);
	if (!ArrayProperty)
	{
		Stack.bArrayContextFailed = true;
		return;
	}
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)RESULT_PARAM = GenericMyArray_Count(ArrayAddr, ArrayProperty);
	P_NATIVE_END;
}

//////////////////////////////////////////////////////////////////////////

int32 UMyFunction_Param::MyArray_CompareSize(const TArray<int32>& ArrayA, const TArray<int32>& ArrayB)
{
	return 0;
}

int32 UMyFunction_Param::GenericMyArray_CompareSize(void* ArrayA, const FArrayProperty* ArrayAProp, void* ArrayB, const FArrayProperty* ArrayBProp)
{
	if (ArrayA && ArrayB)
	{
		FScriptArrayHelper ArrayAHelper(ArrayAProp, ArrayA);
		FScriptArrayHelper ArrayBHelper(ArrayBProp, ArrayB);
		return ArrayAHelper.Num() - ArrayBHelper.Num();
	}

	return 0;
}


DEFINE_FUNCTION(UMyFunction_Param::execMyArray_CompareSize)
{
	// Retrieve the first array
	Stack.MostRecentProperty = nullptr;
	Stack.StepCompiledIn<FArrayProperty>(NULL);
	void* ArrayAAddr = Stack.MostRecentPropertyAddress;
	FArrayProperty* ArrayAProperty = CastField<FArrayProperty>(Stack.MostRecentProperty);
	if (!ArrayAProperty)
	{
		Stack.bArrayContextFailed = true;
		return;
	}
	// Retrieve the second array
	Stack.MostRecentProperty = nullptr;
	Stack.StepCompiledIn<FArrayProperty>(NULL);
	void* ArrayBAddr = Stack.MostRecentPropertyAddress;
	FArrayProperty* ArrayBProperty = CastField<FArrayProperty>(Stack.MostRecentProperty);
	if (!ArrayBProperty)
	{
		Stack.bArrayContextFailed = true;
		return;
	}

	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)RESULT_PARAM = GenericMyArray_CompareSize(ArrayAAddr, ArrayAProperty, ArrayBAddr, ArrayBProperty);
	P_NATIVE_END;
}

//////////////////////////////////////////////////////////////////////////

int32 UMyFunction_Param::MyMap_Count(const TMap<int32, int32>& TargetMap)
{
	return 0;
}

int32 UMyFunction_Param::GenericMyMap_Count(const void* TargetMap, const FMapProperty* MapProperty)
{
	if (TargetMap)
	{
		FScriptMapHelper MapHelper(MapProperty, TargetMap);
		return MapHelper.Num();
	}
	return 0;
}

DEFINE_FUNCTION(UMyFunction_Param::execMyMap_Count)
{
	Stack.MostRecentProperty = nullptr;
	Stack.StepCompiledIn<FMapProperty>(NULL);
	void* MapAddr = Stack.MostRecentPropertyAddress;
	FMapProperty* MapProperty = CastField<FMapProperty>(Stack.MostRecentProperty);
	if (!MapProperty)
	{
		Stack.bArrayContextFailed = true;
		return;
	}

	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)RESULT_PARAM = GenericMyMap_Count(MapAddr, MapProperty);
	P_NATIVE_END
}

//////////////////////////////////////////////////////////////////////////
int32 UMyFunction_Param::MyMap_CompareSize(const TMap<int32, int32>& MapA, const TMap<int32, int32>& MapB)
{
	return 0;
}

int32 UMyFunction_Param::GenericMyMap_CompareSize(void* MapA, const FMapProperty* MapAProp, void* MapB, const FMapProperty* MapBProp)
{
	if (MapA && MapB)
	{
		FScriptMapHelper MapAHelper(MapAProp, MapA);
		FScriptMapHelper MapBHelper(MapBProp, MapB);
		return MapAHelper.Num() - MapBHelper.Num();
	}

	return 0;
}





DEFINE_FUNCTION(UMyFunction_Param::execMyMap_CompareSize)
{
	// Retrieve the first Map
	Stack.MostRecentProperty = nullptr;
	Stack.StepCompiledIn<FMapProperty>(NULL);
	void* MapAAddr = Stack.MostRecentPropertyAddress;
	FMapProperty* MapAProperty = CastField<FMapProperty>(Stack.MostRecentProperty);
	if (!MapAProperty)
	{
		Stack.bArrayContextFailed = true;
		return;
	}
	// Retrieve the second Map
	Stack.MostRecentProperty = nullptr;
	Stack.StepCompiledIn<FMapProperty>(NULL);
	void* MapBAddr = Stack.MostRecentPropertyAddress;
	FMapProperty* MapBProperty = CastField<FMapProperty>(Stack.MostRecentProperty);
	if (!MapBProperty)
	{
		Stack.bArrayContextFailed = true;
		return;
	}

	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)RESULT_PARAM = GenericMyMap_CompareSize(MapAAddr, MapAProperty, MapBAddr, MapBProperty);
	P_NATIVE_END;
}


//////////////////////////////////////////////////////////////////////////
bool UMyFunction_Param::MyMap_FindOrAdd(const TMap<int32, int32>& TargetMap, const int32& Key, const int32& Value)
{
	return false;
}

bool UMyFunction_Param::GenericMyMap_FindOrAdd(const void* TargetMap, const FMapProperty* MapProperty, const void* KeyPtr, const void* ValuePtr)
{
	if (TargetMap)
	{
		FScriptMapHelper MapHelper(MapProperty, TargetMap);
		if (MapHelper.FindValueFromHash(KeyPtr))
		{
			return false;
		}
		MapHelper.AddPair(KeyPtr, ValuePtr);
		return true;
	}
	return false;
}


DEFINE_FUNCTION(UMyFunction_Param::execMyMap_FindOrAdd)
{
	Stack.MostRecentProperty = nullptr;
	Stack.StepCompiledIn<FMapProperty>(NULL);
	void* MapAddr = Stack.MostRecentPropertyAddress;
	FMapProperty* MapProperty = CastField<FMapProperty>(Stack.MostRecentProperty);
	if (!MapProperty)
	{
		Stack.bArrayContextFailed = true;
		return;
	}

	// Since Key and Value aren't really an int, step the stack manually
	const FProperty* CurrKeyProp = MapProperty->KeyProp;
	const int32 KeyPropertySize = CurrKeyProp->ElementSize * CurrKeyProp->ArrayDim;
	void* KeyStorageSpace = FMemory_Alloca(KeyPropertySize);
	CurrKeyProp->InitializeValue(KeyStorageSpace);

	Stack.MostRecentPropertyAddress = nullptr;
	Stack.MostRecentPropertyContainer = nullptr;
	Stack.StepCompiledIn<FProperty>(KeyStorageSpace);

	const FProperty* CurrValueProp = MapProperty->ValueProp;
	const int32 ValuePropertySize = CurrValueProp->ElementSize * CurrValueProp->ArrayDim;
	void* ValueStorageSpace = FMemory_Alloca(ValuePropertySize);
	CurrValueProp->InitializeValue(ValueStorageSpace);

	Stack.MostRecentPropertyAddress = nullptr;
	Stack.MostRecentPropertyContainer = nullptr;
	Stack.StepCompiledIn<FProperty>(ValueStorageSpace);

	P_FINISH;

	P_NATIVE_BEGIN;
	*(bool*)RESULT_PARAM = GenericMyMap_FindOrAdd(MapAddr, MapProperty, KeyStorageSpace, ValueStorageSpace);
	P_NATIVE_END;

	CurrValueProp->DestroyValue(ValueStorageSpace);
	CurrKeyProp->DestroyValue(KeyStorageSpace);
}



void UMyFunction_Param::MySet_Add2(const TSet<int32>& SetA, const int32& ItemA, const TSet<int32>& SetB, const int32& ItemB)
{

}

void UMyFunction_Param::GenericMySet_Add2(const void* TargetSet, const FSetProperty* SetA, const void* ItemA, const FSetProperty* SetB, const void* ItemB)
{

}

DEFINE_FUNCTION(UMyFunction_Param::execMySet_Add2)
{

}
