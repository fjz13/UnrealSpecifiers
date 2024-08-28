#include "MyClass_EditorConfig.h"


void UMyClass_EditorConfig_Test::TestConfigSave()
{
	//must run after editor initialization
	auto* testObject = NewObject<UMyClass_EditorConfig>(GetTransientPackage(), TEXT("testObject_EditorConfig"));
	testObject->MyPropertyWithConfig = 777;
	testObject->SaveEditorConfig();

}

void UMyClass_EditorConfig_Test::TestConfigLoad()
{
	auto* testObject = NewObject<UMyClass_EditorConfig>(GetTransientPackage(), TEXT("testObject_EditorConfig"));
	testObject->LoadEditorConfig();
}

void UMyClass_EditorConfig_Test::RunTest()
{
	//TestPerObjectConfigLoad();
	TestConfigSave();
}
