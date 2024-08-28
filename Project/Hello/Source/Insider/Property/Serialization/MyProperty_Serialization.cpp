// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProperty_Serialization.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"
#include <Exporters/Exporter.h>
#include <Containers/UnrealString.h>

void UMyProperty_Serialization_Test::RunTest()
{
	RunExportTest();
	UMyProperty_Serialization* obj = NewObject<UMyProperty_Serialization>(GetTransientPackage());

	obj->MyInt_Default = 456;
	obj->MyInt_Transient = 456;
	obj->MyInt_DuplicateTransient = 456;
	obj->MyInt_NonPIEDuplicateTransient = 456;

	//save obj
	TArray<uint8> outBytes;
	FMemoryWriter MemoryWriter(outBytes, true);
	FObjectAndNameAsStringProxyArchive Ar(MemoryWriter, false);
	obj->Serialize(Ar);


	//load
	FMemoryReader MemoryReader(outBytes, true);

	FObjectAndNameAsStringProxyArchive Ar2(MemoryReader, true);

	UMyProperty_Serialization* obj2 = NewObject<UMyProperty_Serialization>(GetTransientPackage());
	obj2->Serialize(Ar2);


	UMyProperty_Serialization* obj3= DuplicateObject<UMyProperty_Serialization>(obj,GetTransientPackage());
}

void UMyProperty_Serialization_Test::RunExportTest()
{
	UMyProperty_Serialization* obj = NewObject<UMyProperty_Serialization>(GetTransientPackage());

	obj->MyInt_Default = 456;
	obj->MyInt_Transient = 456;
	obj->MyInt_DuplicateTransient = 456;
	obj->MyInt_NonPIEDuplicateTransient = 456;


	FStringOutputDevice Ar;
	UExporter::ExportToOutputDevice(nullptr, obj, nullptr,Ar,TEXT("T3D"), 3);

	FStringOutputDevice Ar2;
	UExporter::ExportToOutputDevice(nullptr, obj, nullptr,Ar2,TEXT("COPY"), 3);


	FString str=Ar;
}
