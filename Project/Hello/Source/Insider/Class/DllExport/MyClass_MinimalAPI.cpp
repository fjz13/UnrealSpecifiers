#include "MyClass_MinimalAPI.h"

void UMyClass_NotMinimalAPI::MyFunc()
{
	++MyProperty;
}

void UMyClass_MinimalAPI::MyFunc()
{
	++MyProperty;
}

void UMyClass_DefaultExport::MyFunc()
{
	++MyProperty;
}

void UMyClass_MinimalAPI_BlueprintFunctionLibary::MyFuncInMinimalAPI()
{

}

INSIDER_API void UMyClass_MinimalAPI_BlueprintFunctionLibary::MyFuncInMinimalAPIWithAPI()
{

}
