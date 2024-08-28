#include "MyClass_UseMinimalAPI.h"
//#include "Class/MyClass_ModuleAPI.h"
//#include "Class/MyClass_WithoutAPI.h"
//#include "Class/MyClass_NoExport.h"
//#include "Struct/MyStruct_ModuleAPI.h"
//#include "Struct/MyStruct_NoExport.h"

#include "Class/DllExport/MyClass_MinimalAPI.h"





void UMyClass_UseMinimalAPI::TestFunc()
{
	{
		//UMyClass_MinimalAPI* a = NewObject<UMyClass_MinimalAPI>();

		//error LNK2019: unresolved external symbol "public: void __cdecl UMyClass_MinimalAPI::MyFunc(void)" (?MyFunc@UMyClass_MinimalAPI@@QEAAXXZ) referenced in function "public: void __cdecl UMyClass_UseMinimalAPI::TestFunc(void)" (?TestFunc@UMyClass_UseMinimalAPI@@QEAAXXZ)
		//a->MyFunc();

		//a->MyProperty++;
	}
	
	{
		//error LNK2019: unresolved external symbol "private: static class UClass * __cdecl UMyClass_NotMinimalAPI::GetPrivateStaticClass(void)" (?GetPrivateStaticClass@UMyClass_NotMinimalAPI@@CAPEAVUClass@@XZ)
		//referenced in function "class UMyClass_NotMinimalAPI * __cdecl NewObject<class UMyClass_NotMinimalAPI>(class UObject *)" (??$NewObject@VUMyClass_NotMinimalAPI@@@@YAPEAVUMyClass_NotMinimalAPI@@PEAVUObject@@@Z)
		//auto* a = NewObject<UMyClass_NotMinimalAPI>();
		//a->MyFunc();

		//a->MyProperty++;
	}


	

	{
		//error LNK2019: unresolved external symbol "public: static void __cdecl UMyClass_MinimalAPI_BlueprintFunctionLibary::MyFuncInMinimalAPI(void)" (?MyFuncInMinimalAPI@UMyClass_MinimalAPI_BlueprintFunctionLibary@@SAXXZ) 
		//referenced in function "public: void __cdecl UMyClass_UseMinimalAPI::TestFunc(void)" (?TestFunc@UMyClass_UseMinimalAPI@@QEAAXXZ)
		//UMyClass_MinimalAPI_BlueprintFunctionLibary::MyFuncInMinimalAPI();

		//UMyClass_MinimalAPI_BlueprintFunctionLibary::MyFuncInMinimalAPIWithAPI();

		/*auto* a= NewObject<UMyClass_ModuleAPI>();
		a->MyFunc();
		a->MyProperty++;*/
	}

	//{
	//	auto* a = NewObject<UMyClass_WithoutAPI>();
	//	a->MyFunc();
	//	a->MyProperty++;
	//}

	/*{
		auto* a = NewObject<UMyClass_NoExport>();
		a->MyFunc();
		a->MyProperty++;
	}*/

	{
		//UScriptStruct* ss = StaticStruct<FMyStruct_ModuleAPI>();

	}

	{
		//UScriptStruct* ss = StaticStruct<FVector>();

	}

	{

		//UScriptStruct* ss = StaticStruct<FMyStruct_NoExport>();
	}

	
}