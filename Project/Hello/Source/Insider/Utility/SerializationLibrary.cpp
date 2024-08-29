#include "SerializationLibrary.h"
#include <Serialization/ObjectWriter.h>
#include <Serialization/ObjectReader.h>
#include <Serialization/ObjectAndNameAsStringProxyArchive.h>

void USerializationLibrary::SaveObjectToMemory(UObject* object, TArray<uint8>& outSaveData)
{
	FMemoryWriter MemoryWriter(outSaveData, true);
	FObjectAndNameAsStringProxyArchive Ar(MemoryWriter, false);


	object->Serialize(Ar);
}

UObject* USerializationLibrary::LoadObjectFromMemory(UClass* objectClass, const TArray<uint8>& saveData)
{
	if (saveData.Num() == 0)
	{
		// Empty buffer, return instead of causing a bad serialize that could crash
		return nullptr;
	}

	FMemoryReader MemoryReader(saveData, true);
	FObjectAndNameAsStringProxyArchive Ar(MemoryReader, false);


	// If we have a class, try and load it.
	UObject* resultObject = NewObject<UObject>(GetTransientPackage(), objectClass);

	resultObject->Serialize(Ar);

	return resultObject;
}

void USerializationLibrary::SaveStructToMemory(UScriptStruct* structClass, void* structObject, const void* structDefaults, TArray<uint8>& outSaveData, EInsiderSerializationFlags flags/*=EInsiderSerializationFlags::None*/)
{
	FMemoryWriter MemoryWriter(outSaveData, false);
	MemoryWriter.SetWantBinaryPropertySerialization(EnumHasAnyFlags(flags, EInsiderSerializationFlags::UseBinary));
	if (!EnumHasAnyFlags(flags, EInsiderSerializationFlags::CheckDefaults))
	{
		structDefaults=nullptr;
	}
	structClass->SerializeItem(MemoryWriter, structObject, structDefaults);
}

void USerializationLibrary::LoadStructFromMemory(UScriptStruct* structClass, void* structObject, const void* structDefaults, const TArray<uint8>& saveData, EInsiderSerializationFlags flags/*=EInsiderSerializationFlags::None*/)
{
	FMemoryReader MemoryReader(saveData, true);
	MemoryReader.SetWantBinaryPropertySerialization(EnumHasAnyFlags(flags, EInsiderSerializationFlags::UseBinary));
	if (!EnumHasAnyFlags(flags, EInsiderSerializationFlags::CheckDefaults))
	{
		structDefaults=nullptr;
	}
	structClass->SerializeItem(MemoryReader, structObject, structDefaults);
}
