#include "ReflectionLibrary.h"
#include "Utility/InsiderSubsystem.h"


#pragma region Reflection

UEnum* UReflectionLibrary::FindEnum(FName name)
{
	return FindObject<UEnum>(nullptr, *name.ToString());
}

void UReflectionLibrary::AddEnumItem(UEnum* enumClass, FName name, int32 value)
{
	TArray<TPair<FName, int64>> originalEnumNames;
	originalEnumNames.Reserve(enumClass->NumEnums() + 1);

	FString newName = enumClass->GenerateFullEnumName(*name.ToString());

	bool hasMax = enumClass->ContainsExistingMax();
	bool hasItem = false;
	for (int i = 0; i < enumClass->NumEnums(); ++i)
	{
		FString curName = enumClass->GetNameStringByIndex(i);
		if (curName.EndsWith("MAX") || curName.EndsWith("_MAX"))	//do not add max item
		{
			continue;
		}

		curName = enumClass->GenerateFullEnumName(*curName);
		int curValue = enumClass->GetValueByIndex(i);
		if (curName == newName)
		{
			curValue = value;
			hasItem = true;
		}

		originalEnumNames.Emplace(FName(*curName), curValue);
	}

	if (!hasItem)
	{
		originalEnumNames.Emplace(FName(*newName), value);
	}
	enumClass->SetEnums(originalEnumNames, enumClass->GetCppForm(), EEnumFlags::None,hasMax);

}

void UReflectionLibrary::AddEnumItems(UEnum* enumClass, const TMap<FName, int32>& newItems)
{
	TArray<TPair<FName, int64>> originalEnumNames;
	originalEnumNames.Reserve(enumClass->NumEnums() + newItems.Num());

	TMap<FString, int32> allItems;
	for (const auto& kv:newItems)
	{
		allItems.Add(enumClass->GenerateFullEnumName(*kv.Key.ToString()), kv.Value);
	}

	bool hasMax = enumClass->ContainsExistingMax();
	for (int i = 0; i < enumClass->NumEnums(); ++i)
	{
		FString curName = enumClass->GetNameStringByIndex(i);
		if (curName.EndsWith("MAX") || curName.EndsWith("_MAX"))	//do not add max item
		{
			continue;
		}

		curName = enumClass->GenerateFullEnumName(*curName);
		int curValue = enumClass->GetValueByIndex(i);
		int* newValue= allItems.Find(curName);
		if (newValue!=nullptr)	//override value
		{
			curValue = *newValue;
			allItems.Remove(curName);
		}

		originalEnumNames.Emplace(FName(*curName), curValue);
	}
	for (const auto& kv : allItems)
	{
		originalEnumNames.Emplace(FName(*kv.Key), kv.Value);
	}

	enumClass->SetEnums(originalEnumNames, enumClass->GetCppForm(), EEnumFlags::None, hasMax);
}

void UReflectionLibrary::RemoveEnumItem(UEnum* enumClass, FName name)
{
	if (enumClass->GetIndexByName(name) == INDEX_NONE)	//not found
	{
		return;
	}

	TArray<TPair<FName, int64>> originalEnumNames;
	originalEnumNames.Reserve(enumClass->NumEnums());

	FString newName = enumClass->GenerateFullEnumName(*name.ToString());

	bool hasMax = enumClass->ContainsExistingMax();
	for (int i = 0; i < enumClass->NumEnums(); ++i)
	{
		FString curName = enumClass->GetNameStringByIndex(i);
		if (curName.EndsWith("MAX") || curName.EndsWith("_MAX"))	//do not add max item
		{
			continue;
		}

		curName = enumClass->GenerateFullEnumName(*curName);
		int curValue = enumClass->GetValueByIndex(i);
		if (curName != newName)
		{
			originalEnumNames.Emplace(FName(*curName), curValue);
		}
	}

	enumClass->SetEnums(originalEnumNames, enumClass->GetCppForm(), EEnumFlags::None, hasMax);
}

FString UReflectionLibrary::K2_InvokeFunction(UObject* obj, FName functionName)
{

	FString str;

	/*FString str;
	UClass* classObj = obj->GetClass();
	UFunction* func = obj->FindFunction(functionName);
	if (func == nullptr)
	{
		str += FString::Printf(L"\tCannot find Function:\t%s\n", *functionName.ToString());
		return str;
	}
*/
//InvokeFunction(obj, "MyEvent", 123.f);
//int r = 0;

/*UFunction* func2 = FindObject<UFunction>(ANY_PACKAGE, TEXT("/Game/MyFuncLibrary.SKEL_MyFuncLibrary_C:HelloFunc2"));
int r = InvokeFunctionStatic<int>(func2, 123.f);*/

//HelloFunc2
	//UClass* funcLibary = FindObject<UClass>(ANY_PACKAGE, TEXT("MyFuncLibrary_C"));
	//int rt3 = InvokeFunction<int>(funcLibary, functionName, 123.f);


	//UFunction* func = FindObject<UFunction>(ANY_PACKAGE, *functionName.ToString());

		//UMyClass* testObj = NewObject<UMyClass>();
		//TTuple<int> rt = InvokeBlueprintLibraryFunction<int>(funcLibary, functionName, 123.f);
		//TTuple<int> rt = InvokeBlueprintLibraryFunction<int>(nullptr,obj, "HelloFunc", 123.f);

	//int rt2 = InvokeFunctionByName<int>(functionName, 123.f);
	FString rt = InvokeFunction<UInsiderSubsystem, FString>("PrintSuperClasses", UInsiderSubsystem::Get().StaticClass());

	//TTuple<FString> rt = InvokeBlueprintLibraryFunction<FString>(UReflectionLibrary::StaticClass(), nullptr, "PrintSuperClasses", UReflectionLibrary::StaticClass());



	//int r = rt.Get<0>();
	int r = 0;

	//int r= InvokeFunction<int>(obj,functionName,123.f);

	//TTuple<FString> params1;
	//UFunction* func2= UInsiderSubsystem::StaticClass()->FindFunctionByName("PrintAllUClasses");
	//FFrame frame1(nullptr, func2, &params1, nullptr, func2->Children);
	//func2->Invoke(nullptr, frame1, &params1 + func2->ReturnValueOffset);
	////UInsiderSubsystem::StaticClass()->GetDefaultObject()->ProcessEvent(func2, &params1);

	//TTuple<float, int> params;
	//params.Get<0>() = 123;
	//params.Get<1>() = 456;
	//FFrame frame(obj, func, &params, nullptr, func->Children);
	//obj->CallFunction(frame, &params.Get<1>(), func);
	////func->Invoke(obj, frame, &params.Get<1>());
	//int r = params.Get<1>();


	str += FString::Printf(L"\tInvokeFunction:\t%s Return:%d\n", *functionName.ToString(), r);
	return str;
}



#pragma endregion Reflection
