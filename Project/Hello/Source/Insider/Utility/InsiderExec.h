#pragma once

#include "Utility/InsiderTypes.h"
#include "Misc/CoreMisc.h"
#include "InsiderSubsystem.h"


class INSIDER_API FInsiderExec :public FStaticSelfRegisteringExec
{
public:
	FInsiderExec(bool(*InStaticExecFunc)(UWorld* Inworld, const TCHAR* Cmd, FOutputDevice& Ar));
	virtual bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar);


private:
	template<typename TObject = UObject>
	TObject* FindObjectHelper(const FString& objName, FOutputDevice& Ar)
	{
		UObject* obj = UInsiderSubsystem::Get().FindObjectWithNameSmart(objName);
		if (obj == nullptr)
		{
			FString str = FString::Printf(TEXT("NotFound:%s"), *objName);
			Ar.Log(ELogVerbosity::Error, str);
		}

		return Cast<TObject>(obj);
	}

	template<typename TObject = UObject>
	TObject* FindObjectHelperWithCommand(const TCHAR*& Command, FOutputDevice& Ar)
	{
		FString objName;
		if (FParse::Token(Command, objName, false))
		{
			return FindObjectHelper<TObject>(objName, Ar);
		}
		return nullptr;
	}

private:
	template<typename TClass = UClass>
	TClass* FindClassHelper(const FString& className, FOutputDevice& Ar)
	{
		UObject* obj = UInsiderSubsystem::Get().FindObjectWithNameSmart(className);
		if (obj == nullptr)
		{
			FString str = FString::Printf(TEXT("NotFound:%s"), *className);
			Ar.Log(ELogVerbosity::Error, str);
			return nullptr;
		}
		if (!obj->IsA<UClass>())
		{
			FString str = FString::Printf(TEXT("Not UClass:%s"), *className);
			Ar.Log(ELogVerbosity::Error, str);
			return nullptr;
		}
		return Cast<TClass>(obj);
	}

	template<typename TClass = UClass>
	TClass* FindClassHelperWithCommand(const TCHAR*& Command, FOutputDevice& Ar)
	{
		FString className;
		if (FParse::Token(Command, className, false))
		{
			return FindClassHelper<TClass>(className, Ar);
		}
		return nullptr;
	}
private:
	void PrintObjectHelper(UObject* obj, FOutputDevice& Ar);
	void PrintObjectsHelper(const TArray<UObject*>& objs, FOutputDevice& Ar);

};

