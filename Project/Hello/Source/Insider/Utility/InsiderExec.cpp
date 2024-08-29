#include "InsiderExec.h"
#include "Utility/Log.h"
#include "HAL/IConsoleManager.h"
#include "Utility/InsiderSubsystem.h"
#include "Utility/ReflectionLibrary.h"

#include "CoreGlobals.h"

#include "Windows\WindowsPlatformApplicationMisc.h"

FInsiderExec::FInsiderExec(bool(*InStaticExecFunc)(UWorld* Inworld, const TCHAR* Cmd, FOutputDevice& Ar))
	:FStaticSelfRegisteringExec(InStaticExecFunc)
{
	IConsoleManager::Get().RegisterConsoleCommand(TEXT("po"), TEXT("po objectPath"), ECVF_Cheat);
	IConsoleManager::Get().RegisterConsoleCommand(TEXT("pp"), TEXT("pp packagePath"), ECVF_Cheat);


	IConsoleManager::Get().RegisterConsoleCommand(TEXT("i.PrintObject"), TEXT("i.PrintObject objPath"), ECVF_Cheat);

	IConsoleManager::Get().RegisterConsoleCommand(TEXT("i.PrintAllPackages"), TEXT("i.PrintAllPackages"), ECVF_Cheat);
	IConsoleManager::Get().RegisterConsoleCommand(TEXT("i.PrintAllUClasses"), TEXT("i.PrintAllUClasses"), ECVF_Cheat);
	IConsoleManager::Get().RegisterConsoleCommand(TEXT("i.PrintAllEnums"), TEXT("i.PrintAllEnums"), ECVF_Cheat);
	IConsoleManager::Get().RegisterConsoleCommand(TEXT("i.PrintAllStructs"), TEXT("i.PrintAllStructs"), ECVF_Cheat);
	IConsoleManager::Get().RegisterConsoleCommand(TEXT("i.PrintAllMetaDataKeys"), TEXT("i.PrintAllMetaDataKeys"), ECVF_Cheat);

	IConsoleManager::Get().RegisterConsoleCommand(TEXT("i.PrintObjectsWithOuter"), TEXT("i.PrintObjectsWithOuter objPath"), ECVF_Cheat);

	IConsoleManager::Get().RegisterConsoleCommand(TEXT("i.PrintDerivedClasses"), TEXT("i.PrintDerivedClasses classPath [0/1]"), ECVF_Cheat);
	IConsoleManager::Get().RegisterConsoleCommand(TEXT("i.PrintSuperClasses"), TEXT("i.PrintSuperClasses classPath"), ECVF_Cheat);
	IConsoleManager::Get().RegisterConsoleCommand(TEXT("i.PrintInterfacesWithClass"), TEXT("i.PrintInterfaces classPath"), ECVF_Cheat);
	IConsoleManager::Get().RegisterConsoleCommand(TEXT("i.PrintClassesWithInterface"), TEXT("i.PrintClassesWithInterface interfacePath"), ECVF_Cheat);
	IConsoleManager::Get().RegisterConsoleCommand(TEXT("i.PrintObjectOfClass"), TEXT("i.PrintObjectOfClass classPath [0/1]"), ECVF_Cheat);


	IConsoleManager::Get().RegisterConsoleCommand(TEXT("i.NewObject"), TEXT("i.NewObject classPath objName"), ECVF_Cheat);
	IConsoleManager::Get().RegisterConsoleCommand(TEXT("i.RemoveFromRoot"), TEXT("i.RemoveFromRoot objPath"), ECVF_Cheat);

	IConsoleManager::Get().RegisterConsoleCommand(TEXT("i.PrintProperty"), TEXT("i.PrintProperty objPath propertyName"), ECVF_Cheat);
	IConsoleManager::Get().RegisterConsoleCommand(TEXT("i.SetPropertyValue"), TEXT("i.SetPropertyValue objPath propertyName propertyValue"), ECVF_Cheat);

	IConsoleManager::Get().RegisterConsoleCommand(TEXT("i.SetMetaData"), TEXT("i.SetMetaData objPath Key Value"), ECVF_Cheat);
	IConsoleManager::Get().RegisterConsoleCommand(TEXT("i.RemoveMetaData"), TEXT("i.RemoveMetaData objPath Key"), ECVF_Cheat);

	IConsoleManager::Get().RegisterConsoleCommand(TEXT("i.Call"), TEXT("i.Call objPath FunctionName"), ECVF_Cheat);



}

bool FInsiderExec::Exec(UWorld* InWorld, const TCHAR* Command, FOutputDevice& Ar)
{
	if (FParse::Command(&Command, TEXT("po")) || FParse::Command(&Command, TEXT("i.PrintObject")))
	{
		FString objName;
		if (!FParse::Token(Command, objName, false))
		{
			return false;
		}

		FString IgnoreComment;
		if (FParse::Token(Command, IgnoreComment, false)&&IgnoreComment==TEXT("clean"))
		{
			UInsiderSubsystem::Get().IgnoreCommentAndToolTip=true;
		}
		else
		{
			UInsiderSubsystem::Get().IgnoreCommentAndToolTip=false;
		}


		UObject* obj = FindObjectHelper(objName, Ar);
		if (obj == nullptr)
		{
			//try to load objName as asset
			UPackage* packObj = LoadPackage(nullptr, *objName, LOAD_None);
			if (packObj == nullptr)
			{
				//still cannot found
				FString str = FString::Printf(TEXT("NotFound:%s"), *objName);
				Ar.Log(ELogVerbosity::Error, str);
				return false;
			}
			else
			{
				//search again
				obj = FindObjectHelper(objName, Ar);

			}
		}

		if (obj == nullptr)
		{
			//still cannot found
			FString str = FString::Printf(TEXT("NotFound:%s"), *objName);
			Ar.Log(ELogVerbosity::Error, str);
			return false;
		}
		else
		{
			PrintObjectHelper(obj, Ar);
			if (UBlueprint* bp = Cast<UBlueprint>(obj))
			{
				PrintObjectHelper(bp->GeneratedClass, Ar);
			}
		}

		return true;
	}

	if (FParse::Command(&Command, TEXT("pp")))
	{
		FString objName;
		if (!FParse::Token(Command, objName, false))
		{
			return false;
		}

		if (UPackage* packObj = LoadPackage(nullptr, *objName, LOAD_None))
		{
			PrintObjectHelper(packObj, Ar);
		}
		else
		{
			FString str = FString::Printf(TEXT("NotFound:%s"), *objName);
			Ar.Log(ELogVerbosity::Error, str);
			return false;
		}

		return true;
	}


	if (FParse::Command(&Command, TEXT("i.PrintAllPackages")))
	{
		FString str = UInsiderSubsystem::Get().PrintAllPackages();

		Ar.Log(TEXT("Insider"), ELogVerbosity::Display, str);
		FPlatformApplicationMisc::ClipboardCopy(*str);
		return true;
	}

	if (FParse::Command(&Command, TEXT("i.PrintAllUClasses")))
	{
		FString str = UInsiderSubsystem::Get().PrintAllUClasses();

		Ar.Log(TEXT("Insider"), ELogVerbosity::Display, str);
		FPlatformApplicationMisc::ClipboardCopy(*str);
		return true;
	}
	if (FParse::Command(&Command, TEXT("i.PrintAllEnums")))
	{
		FString str = UInsiderSubsystem::Get().PrintAllEnums();

		Ar.Log(TEXT("Insider"), ELogVerbosity::Display, str);
		FPlatformApplicationMisc::ClipboardCopy(*str);

		return true;
	}
	if (FParse::Command(&Command, TEXT("i.PrintAllStructs")))
	{
		FString str = UInsiderSubsystem::Get().PrintAllStructs();

		Ar.Log(TEXT("Insider"), ELogVerbosity::Display, str);
		return true;
	}
	if (FParse::Command(&Command, TEXT("i.PrintAllMetaDataKeys")))
	{
		FString str = UInsiderSubsystem::Get().PrintAllMetaDataKeys();
		FPlatformApplicationMisc::ClipboardCopy(*str);

		Ar.Log(TEXT("Insider"), ELogVerbosity::Display, str);
		return true;
	}
	if (FParse::Command(&Command, TEXT("i.PrintObjectsWithOuter")))
	{
		if (UObject* obj = FindObjectHelperWithCommand(Command, Ar))
		{
			FString str = UInsiderSubsystem::Get().PrintObjectsWithOuter(obj);

			Ar.Log(TEXT("Insider"), ELogVerbosity::Display, str);

		}
		return true;
	}

	if (FParse::Command(&Command, TEXT("i.PrintDerivedClasses")))
	{
		if (UClass* obj = FindClassHelperWithCommand<UClass>(Command, Ar))
		{
			bool recursive = FParse::Command(&Command, TEXT("1"));
			FString str = UInsiderSubsystem::Get().PrintDerivedClasses(obj, recursive);

			Ar.Log(TEXT("Insider"), ELogVerbosity::Display, str);

		}
		return true;
	}

	if (FParse::Command(&Command, TEXT("i.PrintObjectOfClass")))
	{
		if (UClass* classObj = FindClassHelperWithCommand<UClass>(Command, Ar))
		{
			TArray<UObject*> objs;
			GetObjectsOfClass(classObj,objs);
			PrintObjectsHelper(objs,Ar);
		}
		return true;
	}

	if (FParse::Command(&Command, TEXT("i.PrintSuperClasses")))
	{
		if (UClass* obj = FindClassHelperWithCommand<UClass>(Command, Ar))
		{
			bool recursive = FParse::Command(&Command, TEXT("1"));
			FString str = UInsiderSubsystem::Get().PrintSuperClasses(obj);

			Ar.Log(TEXT("Insider"), ELogVerbosity::Display, str);

		}
		return true;
	}

	if (FParse::Command(&Command, TEXT("i.PrintInterfacesWithClass")))
	{
		if (UClass* obj = FindClassHelperWithCommand<UClass>(Command, Ar))
		{
			bool recursive = FParse::Command(&Command, TEXT("1"));
			FString str = UInsiderSubsystem::Get().PrintInterfacesWithClass(obj);

			Ar.Log(TEXT("Insider"), ELogVerbosity::Display, str);

		}
		return true;
	}

	if (FParse::Command(&Command, TEXT("i.PrintClassesWithInterface")))
	{
		if (UClass* obj = FindClassHelperWithCommand<UClass>(Command, Ar))
		{
			FString str = UInsiderSubsystem::Get().PrintClassesWithInterface(obj);

			Ar.Log(TEXT("Insider"), ELogVerbosity::Display, str);
			FPlatformApplicationMisc::ClipboardCopy(*str);
		}
		return true;
	}

	if (FParse::Command(&Command, TEXT("i.NewObject")))
	{
		if (UClass* classObj = FindClassHelperWithCommand<UClass>(Command, Ar))
		{
			FName realObjectName;
			FString objName;
			if (FParse::Token(Command, objName, false))
			{
				realObjectName = FName(*objName);
			}

			UObject* obj = UInsiderSubsystem::Get().K2_NewObject(classObj, realObjectName);
			FString str;
			str += FString::Printf(TEXT("SucceedCreated:%s\n"), *obj->GetFullName());
			str += UInsiderSubsystem::Get().PrintObject(obj);

			Ar.Log(TEXT("Insider"), ELogVerbosity::Display, str);
			FPlatformApplicationMisc::ClipboardCopy(*str);
		}
		return true;
	}

	if (FParse::Command(&Command, TEXT("i.RemoveFromRoot")))
	{
		if (UObject* obj = FindObjectHelperWithCommand(Command, Ar))
		{
			FString str;
			str = FString::Printf(TEXT("SucceedRemove:%s"), *obj->GetFullName());

			Ar.Log(TEXT("Insider"), ELogVerbosity::Display, str);
			FPlatformApplicationMisc::ClipboardCopy(*str);

			obj->RemoveFromRoot();
			obj->ConditionalBeginDestroy();

		}
		return true;
	}

	if (FParse::Command(&Command, TEXT("i.PrintProperty")))
	{
		if (UObject* obj = FindObjectHelperWithCommand(Command, Ar))
		{
			FString propertyName;
			if (FParse::Token(Command, propertyName, false))
			{
				FString str = UInsiderSubsystem::Get().K2_PrintProperty(obj, FName(*propertyName));

				Ar.Log(TEXT("Insider"), ELogVerbosity::Display, str);
				FPlatformApplicationMisc::ClipboardCopy(*str);
			}
			else
			{
				Ar.Log(ELogVerbosity::Error, TEXT("Must have PropertyName."));
			}
		}
		return true;
	}

	if (FParse::Command(&Command, TEXT("i.SetPropertyValue")))
	{
		if (UObject* obj = FindObjectHelperWithCommand(Command, Ar))
		{
			FString propertyName;
			if (FParse::Token(Command, propertyName, false))
			{
				FString propertyValue;
				if (FParse::Token(Command, propertyValue, false))
				{
					FString str = UInsiderSubsystem::Get().SetPropertyValue(obj, FName(*propertyName), propertyValue);

					Ar.Log(TEXT("Insider"), ELogVerbosity::Display, str);
					FPlatformApplicationMisc::ClipboardCopy(*str);
				}
				else
				{
					Ar.Log(ELogVerbosity::Error, TEXT("Must have PropertyValue."));
				}
			}
			else
			{
				Ar.Log(ELogVerbosity::Error, TEXT("Must have PropertyName."));
			}
		}
		return true;
	}

	if (FParse::Command(&Command, TEXT("i.SetMetaData")))
	{
		if (UObject* obj = FindObjectHelperWithCommand(Command, Ar))
		{
			FString key;
			if (FParse::Token(Command, key, false))
			{
				FString value;
				if (FParse::Token(Command, value, false))
				{
					FString str = UInsiderSubsystem::Get().SetMetaData(obj, FName(*key), value);

					Ar.Log(TEXT("Insider"), ELogVerbosity::Display, str);
					FPlatformApplicationMisc::ClipboardCopy(*str);
				}
				else
				{
					Ar.Log(ELogVerbosity::Error, TEXT("Must have Key."));
				}
			}
			else
			{
				Ar.Log(ELogVerbosity::Error, TEXT("Must have Value."));
			}
		}
		return true;
	}


	if (FParse::Command(&Command, TEXT("i.RemoveMetaData")))
	{
		if (UObject* obj = FindObjectHelperWithCommand(Command, Ar))
		{
			FString key;
			if (FParse::Token(Command, key, false))
			{
				FString str = UInsiderSubsystem::Get().RemoveMetaData(obj, FName(*key));

				Ar.Log(TEXT("Insider"), ELogVerbosity::Display, str);
				FPlatformApplicationMisc::ClipboardCopy(*str);
			}
			else
			{
				Ar.Log(ELogVerbosity::Error, TEXT("Must have Key."));
			}
		}
		return true;
	}

	if (FParse::Command(&Command, TEXT("i.Call")))
	{
		if (UClass* obj = FindClassHelperWithCommand(Command, Ar))
		{
			FString functionName;
			if (FParse::Token(Command, functionName, false))
			{
				if (UFunction* func = obj->FindFunctionByName(*functionName))
				{
					UReflectionLibrary::InvokeFunction(obj, func);
				}
				else
				{
					Ar.Logf(ELogVerbosity::Error, TEXT("Cannot find function:%s."), *functionName);
				}
			}
			else
			{
				Ar.Log(ELogVerbosity::Error, TEXT("Must have FunctionName."));
			}
		}
		return true;
	}

	return false;
}


void FInsiderExec::PrintObjectHelper(UObject* obj, FOutputDevice& Ar)
{
	FString str = UInsiderSubsystem::Get().PrintObject(obj);
	Ar.Log(TEXT("Insider"), ELogVerbosity::Display, str);
	FPlatformApplicationMisc::ClipboardCopy(*str);
}

void FInsiderExec::PrintObjectsHelper(const TArray<UObject*>& objs, FOutputDevice& Ar)
{
	FString result;
	for (UObject* obj : objs)
	{
		FString str = UInsiderSubsystem::Get().PrintObject(obj);
		result+=str;
	}

	Ar.Log(TEXT("Insider"), ELogVerbosity::Display, result);
	FPlatformApplicationMisc::ClipboardCopy(*result);
}

FInsiderExec gInsiderExec(nullptr);

