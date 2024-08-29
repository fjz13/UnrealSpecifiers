// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProperty_SerializationText.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"
#include <Exporters/Exporter.h>
#include <Containers/UnrealString.h>

void UMyProperty_SerializationText_Test::RunTest()
{
	//RunExportTest();
	UMyProperty_SerializationText* obj = NewObject<UMyProperty_SerializationText>(GetTransientPackage());

	obj->MyInt_Default = 456;
	obj->MyInt_SkipSerialization = 456;
	obj->MyInt_TextExportTransient = 456;


	//save obj
	TArray<uint8> outBytes;
	FMemoryWriter MemoryWriter(outBytes, true);
	FObjectAndNameAsStringProxyArchive Ar(MemoryWriter, false);
	obj->Serialize(Ar);


	//load
	FMemoryReader MemoryReader(outBytes, true);

	FObjectAndNameAsStringProxyArchive Ar2(MemoryReader, true);

	UMyProperty_SerializationText* obj2 = NewObject<UMyProperty_SerializationText>(GetTransientPackage());
	obj2->Serialize(Ar2);
}

void UMyProperty_SerializationText_Test::RunExportTest()
{
	UMyProperty_SerializationText* obj = NewObject<UMyProperty_SerializationText>(GetTransientPackage());

	obj->MyInt_Default = 456;
	obj->MyInt_SkipSerialization = 456;
	obj->MyInt_TextExportTransient = 456;


	FStringOutputDevice Ar;
	UExporter::ExportToOutputDevice(nullptr, obj, nullptr,Ar,TEXT("T3D"), 3);

	FStringOutputDevice Ar2;
	UExporter::ExportToOutputDevice(nullptr, obj, nullptr,Ar2,TEXT("COPY"), 3);


	FString str=Ar;
}
