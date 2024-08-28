#include "MyClass_DefaultConfig.h"


void UMyClass_DefaultConfig_Test::TestDefaultConfigSave()
{
	auto* testObject = NewObject<UMyClass_DefaultConfig>(GetTransientPackage(), TEXT("testObject_DefaultConfig"));
	testObject->MyPropertyWithConfig = 777;
	testObject->TryUpdateDefaultConfigFile();

}

void UMyClass_DefaultConfig_Test::TestDefaultConfigLoad()
{
	auto* testObject = NewObject<UMyClass_DefaultConfig>(GetTransientPackage(), TEXT("testObject_DefaultConfig"));
}

void UMyClass_DefaultConfig_Test::RunTest()
{
	//TestPerObjectConfigLoad();
	TestDefaultConfigSave();
}
