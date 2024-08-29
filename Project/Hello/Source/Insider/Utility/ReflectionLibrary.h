#pragma once

#include "InsiderTypes.h"
#include "ReflectionLibrary.generated.h"


UCLASS(Category = Insider)
class INSIDER_API UReflectionLibrary :public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
#pragma region Dynamic
	UFUNCTION(BlueprintCallable, Category = Insider)
		static UEnum* FindEnum(FName name);
	UFUNCTION(BlueprintCallable, Category = Insider)
		static void AddEnumItem(UEnum* enumClass, FName name, int32 value);
	UFUNCTION(BlueprintCallable, Category = Insider)
		static void AddEnumItems(UEnum* enumClass, const TMap<FName, int32>& newItems);
	UFUNCTION(BlueprintCallable, Category = Insider)
		static void RemoveEnumItem(UEnum* enumClass, FName name);
#pragma endregion Dynamic


#pragma region Function
public:
	UFUNCTION(BlueprintCallable, DisplayName = InvokeFunction, Category = Insider)
		static FString K2_InvokeFunction(UObject* obj, FName functionName);


public://1 return and args
//member function
	template<typename TFirstReturn, typename... TArgs, typename TObject = UObject>
	static TFirstReturn InvokeFunction(TObject* obj, UFunction* func, TArgs&&... args)
	{
		return InvokeFunction_Internal<TFirstReturn>(nullptr, obj, func, Forward<TArgs>(args)...).Get<0>();
	}
	template<typename TFirstReturn, typename... TArgs, typename TObject = UObject>
	static TFirstReturn InvokeFunction(TObject* obj, FName functionName, TArgs&&... args)
	{
		UFunction* func = obj->FindFunctionChecked(functionName);
		return InvokeFunction_Internal<TFirstReturn>(nullptr, obj, func, Forward<TArgs>(args)...).Get<0>();
	}
	//static function
	template<typename TFirstReturn, typename... TArgs>
	static TFirstReturn InvokeFunction(UFunction* func, TArgs&&... args)
	{
		return InvokeFunction_Internal<TFirstReturn>(func->GetOuterUClass(), nullptr, func, Forward<TArgs>(args)...).Get<0>();
	}

	template<typename TFirstReturn, typename... TArgs>
	static TFirstReturn InvokeFunction(UClass* outerClass, FName functionName, TArgs&&... args)
	{
		UFunction* func = outerClass->FindFunctionByName(functionName);
		return InvokeFunction_Internal<TFirstReturn>(outerClass, nullptr, func, Forward<TArgs>(args)...).Get<0>();
	}

	template<typename TClass, typename TFirstReturn, typename... TArgs>
	static TFirstReturn InvokeFunction(FName functionName, TArgs&&... args)
	{
		UClass* outerClass = TClass::StaticClass();
		UFunction* func = outerClass->FindFunctionByName(functionName);
		return InvokeFunction_Internal<TFirstReturn>(outerClass, nullptr, func, Forward<TArgs>(args)...).Get<0>();
	}

	template<typename TFirstReturn, typename... TArgs>
	static TFirstReturn InvokeFunctionByName(FName functionName, TArgs&&... args)
	{
		UFunction* func = (UFunction*)StaticFindObjectFast(UFunction::StaticClass(), nullptr, functionName, false, true, RF_Transient);	//exclude SKEL_XXX_C:Func
		return InvokeFunction_Internal<TFirstReturn>(func->GetOuterUClass(), nullptr, func, Forward<TArgs>(args)...).Get<0>();
	}

public://returns and args
	//member function
	template<typename TFirstReturn, typename TSecondReturn, typename... TReturns, typename... TArgs, typename TObject = UObject>
	static TTuple<TFirstReturn, TSecondReturn, TReturns...> InvokeFunction(TObject* obj, UFunction* func, TArgs&&... args)
	{
		return InvokeFunction_Internal<TFirstReturn, TSecondReturn, TReturns...>(nullptr, obj, func, Forward<TArgs>(args)...);
	}
	template<typename TFirstReturn, typename TSecondReturn, typename... TReturns, typename... TArgs, typename TObject = UObject>
	static TTuple<TFirstReturn, TSecondReturn, TReturns...> InvokeFunction(TObject* obj, FName functionName, TArgs&&... args)
	{
		UFunction* func = obj->FindFunctionChecked(functionName);
		return InvokeFunction_Internal<TFirstReturn, TSecondReturn, TReturns...>(nullptr, obj, func, Forward<TArgs>(args)...);
	}
	//static function
	template<typename TFirstReturn, typename TSecondReturn, typename... TReturns, typename... TArgs>
	static TTuple<TFirstReturn, TSecondReturn, TReturns...> InvokeFunction(UFunction* func, TArgs&&... args)
	{
		return InvokeFunction_Internal<TFirstReturn, TSecondReturn, TReturns...>(func->GetOuterUClass(), nullptr, func, Forward<TArgs>(args)...);
	}

	template<typename TFirstReturn, typename TSecondReturn, typename... TReturns, typename... TArgs>
	static TTuple<TFirstReturn, TSecondReturn, TReturns...> InvokeFunction(UClass* outerClass, FName functionName, TArgs&&... args)
	{
		UFunction* func = outerClass->FindFunctionByName(functionName);
		return InvokeFunction_Internal<TFirstReturn, TSecondReturn, TReturns...>(outerClass, nullptr, func, Forward<TArgs>(args)...);
	}

	template<typename TClass, typename TFirstReturn, typename TSecondReturn, typename... TReturns, typename... TArgs>
	static TTuple<TFirstReturn, TSecondReturn, TReturns...> InvokeFunction(FName functionName, TArgs&&... args)
	{
		UClass* outerClass = TClass::StaticClass();
		UFunction* func = outerClass->FindFunctionByName(functionName);
		return InvokeFunction_Internal<TFirstReturn, TSecondReturn, TReturns...>(outerClass, nullptr, func, Forward<TArgs>(args)...);
	}

	template<typename TFirstReturn, typename TSecondReturn, typename... TReturns, typename... TArgs>
	static TTuple<TFirstReturn, TSecondReturn, TReturns...> InvokeFunctionByName(FName functionName, TArgs&&... args)
	{
		UFunction* func = (UFunction*)StaticFindObjectFast(UFunction::StaticClass(), nullptr, functionName, false, true, RF_Transient);	//exclude SKEL_XXX_C:Func
		return InvokeFunction_Internal<TFirstReturn, TSecondReturn, TReturns...>(func->GetOuterUClass(), nullptr, func, Forward<TArgs>(args)...);
	}
public: //void return
	template< typename... TArgs, typename TObject = UObject>
	static void InvokeFunction(TObject* obj, UFunction* func, TArgs&&... args)
	{
		return InvokeFunction_Internal(nullptr, obj, func, Forward<TArgs>(args)...);
	}
	template< typename... TArgs, typename TObject = UObject>
	static void InvokeFunction(TObject* obj, FName functionName, TArgs&&... args)
	{
		UFunction* func = obj->FindFunctionChecked(functionName);
		return InvokeFunction_Internal(nullptr, obj, func, Forward<TArgs>(args)...);
	}
	//static function
	template< typename... TArgs>
	static void InvokeFunction(UFunction* func, TArgs&&... args)
	{
		return InvokeFunction_Internal(func->GetOuterUClass(), nullptr, func, Forward<TArgs>(args)...);
	}

	template< typename... TArgs>
	static void InvokeFunction(UClass* outerClass, FName functionName, TArgs&&... args)
	{
		UFunction* func = outerClass->FindFunctionByName(functionName);
		return InvokeFunction_Internal(outerClass, nullptr, func, Forward<TArgs>(args)...);
	}

	template<typename TClass, typename... TArgs>
	static void InvokeFunction(FName functionName, TArgs&&... args)
	{
		UClass* outerClass = TClass::StaticClass();
		UFunction* func = outerClass->FindFunctionByName(functionName);
		return InvokeFunction_Internal(outerClass, nullptr, func, Forward<TArgs>(args)...);
	}

	template< typename... TArgs>
	static void InvokeFunctionByName(FName functionName, TArgs&&... args)
	{
		UFunction* func = (UFunction*)StaticFindObjectFast(UFunction::StaticClass(), nullptr, functionName, false, true, RF_Transient);	//exclude SKEL_XXX_C:Func
		return InvokeFunction_Internal(func->GetOuterUClass(), nullptr, func, Forward<TArgs>(args)...);
	}
private:
	template<typename... TReturns, typename... TArgs>
	static TTuple<TReturns...> InvokeFunction_Internal(UClass* objClass, UObject* obj, UFunction* func, TArgs&&... args)
	{
		objClass = obj != nullptr ? obj->GetClass() : objClass;
		UObject* context = obj != nullptr ? obj : objClass;
		TTuple<TReturns...> outParams = MakeTuple(TReturns()...);
		uint8* outPramsBuffer = (uint8*)&outParams;

		if (func->HasAnyFunctionFlags(FUNC_Native))
		{
			TTuple<TArgs..., TReturns...> params = MakeTuple(Forward<TArgs>(args)..., TReturns()...);
			context->ProcessEvent(func, &params);

			for (TFieldIterator<FProperty> i(func); i; ++i)
			{
				FProperty* prop = *i;
				if (prop->PropertyFlags & CPF_OutParm)
				{
					void* propBuffer = prop->ContainerPtrToValuePtr<void*>(&params);
					prop->CopyCompleteValue(outPramsBuffer, propBuffer);
					outPramsBuffer += prop->GetSize();
				}
			}
			return outParams;
		}

		TTuple<TArgs...> inParams = MakeTuple(Forward<TArgs>(args)...);
		void* funcPramsBuffer = (uint8*)FMemory_Alloca(func->ParmsSize);

		uint8* inPramsBuffer = (uint8*)&inParams;

		for (TFieldIterator<FProperty> i(func); i; ++i)
		{
			FProperty* prop = *i;
			if (prop->GetFName().ToString().StartsWith("__"))
			{
				//ignore private param like __WolrdContext of function in blueprint funcion library
				continue;
			}
			void* propBuffer = prop->ContainerPtrToValuePtr<void*>(funcPramsBuffer);
			if (prop->PropertyFlags & CPF_OutParm)
			{
				prop->CopyCompleteValue(propBuffer, outPramsBuffer);
				outPramsBuffer += prop->GetSize();
			}
			else if (prop->PropertyFlags & CPF_Parm)
			{
				prop->CopyCompleteValue(propBuffer, inPramsBuffer);
				inPramsBuffer += prop->GetSize();
			}
		}

		context->ProcessEvent(func, funcPramsBuffer);	//call function

		outPramsBuffer = (uint8*)&outParams;	//reset to begin

		//copy back out params
		for (TFieldIterator<FProperty> i(func); i; ++i)
		{
			FProperty* prop = *i;
			if (prop->PropertyFlags & CPF_OutParm)
			{
				void* propBuffer = prop->ContainerPtrToValuePtr<void*>(funcPramsBuffer);
				prop->CopyCompleteValue(outPramsBuffer, propBuffer);
				outPramsBuffer += prop->GetSize();
			}
		}

		return outParams;
	}

	template<typename... TReturns>
	static TTuple<TReturns...> InvokeFunction_Internal(UClass* objClass, UObject* obj, UFunction* func)
	{
		objClass = obj != nullptr ? obj->GetClass() : objClass;
		UObject* context = obj != nullptr ? obj : objClass;
		TTuple<TReturns...> outParams = MakeTuple(TReturns()...);

		if (func->HasAnyFunctionFlags(FUNC_Native))
		{
			context->ProcessEvent(func, &outParams);
			return outParams;
		}

		void* funcPramsBuffer = (uint8*)FMemory_Alloca(func->ParmsSize);//may be bigger than sizeof(outParams)
		uint8* outPramsBuffer = (uint8*)&outParams;

		for (TFieldIterator<FProperty> i(func); i; ++i)
		{
			FProperty* prop = *i;
			if (prop->GetFName().ToString().StartsWith("__"))
			{
				//ignore private param like __WolrdContext of function in blueprint funcion library
				continue;
			}

			void* propBuffer = prop->ContainerPtrToValuePtr<void*>(funcPramsBuffer);
			if (prop->PropertyFlags & CPF_OutParm)
			{
				prop->CopyCompleteValue(propBuffer, outPramsBuffer);
				outPramsBuffer += prop->GetSize();
			}
		}

		context->ProcessEvent(func, funcPramsBuffer);	//call function

		outPramsBuffer = (uint8*)&outParams;	//reset to begin

		//copy back out params
		for (TFieldIterator<FProperty> i(func); i; ++i)
		{
			FProperty* prop = *i;
			if (prop->PropertyFlags & CPF_OutParm)
			{
				void* propBuffer = prop->ContainerPtrToValuePtr<void*>(funcPramsBuffer);
				prop->CopyCompleteValue(outPramsBuffer, propBuffer);
				outPramsBuffer += prop->GetSize();
			}
		}

		return outParams;
	}

	template<typename... TArgs>
	static void InvokeFunction_Internal(UClass* objClass, UObject* obj, UFunction* func, TArgs&&... args)
	{
		objClass = obj != nullptr ? obj->GetClass() : objClass;
		UObject* context = obj != nullptr ? obj : objClass;
		TTuple<TArgs...> inParams = MakeTuple(Forward<TArgs>(args)...);

		if (func->HasAnyFunctionFlags(FUNC_Native))
		{
			context->ProcessEvent(func, &inParams);
			return;
		}

		void* funcPramsBuffer = (uint8*)FMemory_Alloca(func->ParmsSize);
		uint8* inPramsBuffer = (uint8*)&inParams;

		for (TFieldIterator<FProperty> i(func); i; ++i)
		{
			FProperty* prop = *i;
			if (prop->GetFName().ToString().StartsWith("__"))
			{
				//ignore private param like __WolrdContext of function in blueprint funcion library
				continue;
			}

			void* propBuffer = prop->ContainerPtrToValuePtr<void*>(funcPramsBuffer);
			if (prop->PropertyFlags & CPF_Parm)
			{
				prop->CopyCompleteValue(propBuffer, inPramsBuffer);
				inPramsBuffer += prop->GetSize();
			}
		}
		context->ProcessEvent(func, funcPramsBuffer);	//call function
	}

	static void InvokeFunction_Internal(UClass* objClass, UObject* obj, UFunction* func)
	{
		objClass = obj != nullptr ? obj->GetClass() : objClass;
		UObject* context = obj != nullptr ? obj : objClass;
		context->ProcessEvent(func, nullptr);	//call function
	}

#pragma endregion Function

};