// Fill out your copyright notice in the Description page of Project Settings.

#include "MyClass_MatchedSerializers.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"
#include <Exporters/Exporter.h>
#include <Containers/UnrealString.h>
#include "UObject/SavePackage.h"
#include "Utility/InsiderSubsystem.h"

#include "Serialization/Formatters/JsonArchiveOutputFormatter.h"

class FSerializationTestArchiveProxy : public FArchiveProxy
{
public:
	FSerializationTestArchiveProxy(FArchive& InnerArchive,
		TMap<TObjectPtr<UObject>, FPackageIndex> const* InObjectToIndexMap,
		TMap<FPackageIndex, TObjectPtr<UObject>> const* InIndexToObjectMap)
		: FArchiveProxy(InnerArchive)
		, ObjectToIndexMap(InObjectToIndexMap)
		, IndexToObjectMap(InIndexToObjectMap)
	{
		SetIsTextFormat(true);
		SetUseUnversionedPropertySerialization(false);

		SetUEVer(FPackageFileVersion(VER_UE4_AUTOMATIC_VERSION, EUnrealEngineObjectUE5Version::AUTOMATIC_VERSION));

		// This tells the archive to use whatever custom versions we're explicitly specifying instead of latest.
		SetShouldSkipUpdateCustomVersion(true);
	}

	virtual FArchive& operator<<(FName& Value) override
	{
		check(!IsTextFormat());

		// Serialize names as strings.
		if (IsLoading())
		{
			FString String;
			InnerArchive << String;
			Value = FName(String);
		}
		else
		{
			FString String = Value.ToString();
			InnerArchive << String;
		}
		return *this;
	}

	virtual FArchive& operator<<(UObject*& Value) override
	{
		check(!IsTextFormat());

		// Serialize object pointers by simply saving their path as a string and assuming the same object can be found
		// at that path on load.
		if (IsLoading())
		{
			FPackageIndex Index;
			InnerArchive << Index;

			check(IndexToObjectMap);
			const TObjectPtr<UObject>* Object = IndexToObjectMap->Find(Index);
			checkf(Object, TEXT("Trying to load reference to unknown object with index: %i"), Index.ForDebugging());
			Value = Object->Get();
		}
		else
		{
			check(ObjectToIndexMap);
			const FPackageIndex* Index = ObjectToIndexMap->Find(TObjectPtr<UObject>(Value));
			checkf(Index,
				TEXT("Trying to save reference to unknown object: %s"),
				Value ? *Value->GetFullName() : TEXT("nullptr"));
			InnerArchive << *const_cast<FPackageIndex*>(Index);
		}
		return *this;
	}

	virtual FArchive& operator<<(FObjectPtr& Value) override
	{
		return FArchiveUObject::SerializeObjectPtr(*this, Value);
	}
	virtual FArchive& operator<<(FLazyObjectPtr& Value) override
	{
		return FArchiveUObject::SerializeLazyObjectPtr(*this, Value);
	}
	virtual FArchive& operator<<(FSoftObjectPtr& Value) override
	{
		return FArchiveUObject::SerializeSoftObjectPtr(*this, Value);
	}
	virtual FArchive& operator<<(FSoftObjectPath& Value) override
	{
		return FArchiveUObject::SerializeSoftObjectPath(*this, Value);
	}
	virtual FArchive& operator<<(FWeakObjectPtr& Value) override
	{
		return FArchiveUObject::SerializeWeakObjectPtr(*this, Value);
	}

private:
	TMap<TObjectPtr<UObject>, FPackageIndex> const* ObjectToIndexMap;
	TMap<FPackageIndex, TObjectPtr<UObject>> const* IndexToObjectMap;
};



void UMyClass_MatchedSerializers_Test::RunTest()
{
	FString packageName = TEXT("/Game/MyTestPackage");
	FString assetPath = FPackageName::LongPackageNameToFilename(packageName, FPackageName::GetAssetPackageExtension());

	IFileManager::Get().Delete(*assetPath, false, true);


	UPackage* package = CreatePackage(*packageName);
	FSavePackageArgs saveArgs{};
	//saveArgs.TopLevelFlags = EObjectFlags::RF_Public | EObjectFlags::RF_Standalone;
	saveArgs.Error = GError;
	//saveArgs.SaveFlags=SAVE_NoError;

	UMyClass_MatchedSerializersMain::StaticClass()->ClassFlags &= ~CLASS_MatchedSerializers;

	UMyClass_MatchedSerializersMain* testObject = NewObject<UMyClass_MatchedSerializersMain>(package, TEXT("testbject"));	//ObjectFlags:	RF_NoFlags
	testObject->MyInt_Default = 456;
	testObject->SubObject = NewObject<UMyClass_MatchedSerializersSub>(GetTransientPackage());

	bool result = UPackage::SavePackage(package, testObject, *assetPath, saveArgs);

}

void UMyClass_MatchedSerializers_Test::RunExportTest()
{
	/*UMyClass_SerializationText::StaticClass()->ClassFlags &= ~CLASS_MatchedSerializers;
	UMyClass_SerializationSub::StaticClass()->ClassFlags &= ~CLASS_MatchedSerializers;*/


	UMyClass_MatchedSerializersMain* Object = NewObject<UMyClass_MatchedSerializersMain>(GetTransientPackage());

	Object->MyInt_Default = 456;
	Object->SubObject = NewObject<UMyClass_MatchedSerializersSub>(GetTransientPackage());
	Object->SubObject->MyInt_Default = 789;

	//obj->SubObject = NewObject<UMyClass_SerializationSub>(GetTransientPackage());


	TMap<TObjectPtr<UObject>, FPackageIndex> ObjectToIndexMap;
	ObjectToIndexMap.Add(TObjectPtr<UObject>(), FPackageIndex());
	ObjectToIndexMap.Add(TObjectPtr<UObject>(Object), FPackageIndex::FromExport(0));
	ObjectToIndexMap.Add(TObjectPtr<UObject>(Object->SubObject), FPackageIndex::FromExport(1));


	TArray<uint8>                  Buffer;
	FMemoryWriter                  WriterAr(Buffer, true);
	//FSerializationTestArchiveProxy TestSerializationArchiveProxy(WriterAr, &ObjectToIndexMap, nullptr);

	FJsonArchiveOutputFormatter JsonArchiveFormatter(WriterAr);
	FStructuredArchive          StructuredArchive(JsonArchiveFormatter);
	JsonArchiveFormatter.SetObjectIndicesMap(&ObjectToIndexMap);

	// Serialize the instance.
	FStructuredArchive::FSlot RootSlot = StructuredArchive.Open();
	Object->Serialize(RootSlot.EnterRecord());

	FAnsiStringView Text((char*)Buffer.GetData(), Buffer.Num());

	//return Buffer;

}

void UMyClass_MatchedSerializers_Test::PrintFlagClasses()
{
	FString str= UInsiderSubsystem::Get().FindAllClassesWithFlag(CLASS_MatchedSerializers);
	FString filePath= FPaths::Combine(FPaths::ProjectDir(),TEXT("Doc\\MatchedSerializersClasses.txt"));
	FFileHelper::SaveStringToFile(str,*filePath);

	FString str2= UInsiderSubsystem::Get().FindAllClassesWithoutFlag(CLASS_MatchedSerializers);
	FString filePath2= FPaths::Combine(FPaths::ProjectDir(),TEXT("Doc\\NoMatchedSerializersClasses.txt"));
	FFileHelper::SaveStringToFile(str2,*filePath2);
}


void UMyClass_MatchedSerializers_Test::ApplyClassFlag()
{
	UMyClass_MatchedSerializersTestAsset::StaticClass()->ClassFlags |= CLASS_MatchedSerializers;
	UMyClass_MatchedSerializersSub::StaticClass()->ClassFlags |= CLASS_MatchedSerializers;
}

void UMyClass_MatchedSerializers_Test::RemoveClassFlag()
{
	UMyClass_MatchedSerializersTestAsset::StaticClass()->ClassFlags &= ~CLASS_MatchedSerializers;
	UMyClass_MatchedSerializersSub::StaticClass()->ClassFlags &= ~CLASS_MatchedSerializers;
}
