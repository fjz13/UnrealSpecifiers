#include "MyClass_Config.h"


UMyClass_Config::UMyClass_Config(const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/)
	:Super(ObjectInitializer)
{

}

void UMyClass_Config_Test::TestConfigSave()
{
	UMyClass_Config* testObject = NewObject<UMyClass_Config>(GetTransientPackage(), TEXT("testObject"));

	const UMyClass_Config* testObjectDefault = UMyClass_Config::StaticClass()->GetDefaultObject<UMyClass_Config>();

	testObject->MyProperty = 777;
	testObject->MyPropertyWithConfig = 777;

	testObject->SaveConfig();
	//testObject->LoadConfig();
}


void UMyClass_Config_Test::TestConfigLoad()
{
	const UMyClass_Config* testObjectDefault = UMyClass_Config::StaticClass()->GetDefaultObject<UMyClass_Config>();

	UMyClass_Config* testObject = NewObject<UMyClass_Config>(GetTransientPackage(), TEXT("testObject"));

	//testObject��testObjectDefault��ֵ��ͬ
	//testObject->LoadConfig();//����Ҫ��ʽ����LoadConfig
}

void UMyClass_Config_Test::TestPerObjectConfigSave()
{
	UMyClass_PerObjectConfig* testObject1 = NewObject<UMyClass_PerObjectConfig>(GetTransientPackage(), TEXT("testObject1"));
	testObject1->MyPropertyWithConfig = 456;
	testObject1->SaveConfig();

	UMyClass_PerObjectConfig* testObject2 = NewObject<UMyClass_PerObjectConfig>(GetTransientPackage(), TEXT("testObject2"));
	testObject2->MyPropertyWithConfig = 789;
	testObject2->SaveConfig();

}

void UMyClass_Config_Test::TestPerObjectConfigLoad()
{
	UMyClass_PerObjectConfig* testObject1 = NewObject<UMyClass_PerObjectConfig>(GetTransientPackage(), TEXT("testObject1"));
	//testObject1->LoadConfig();	//����Ҫ��ʽ����LoadConfig

	UMyClass_PerObjectConfig* testObject2 = NewObject<UMyClass_PerObjectConfig>(GetTransientPackage(), TEXT("testObject2"));
	//testObject2->LoadConfig();
}

void UMyClass_Config_Test::TestConfigCheckDefaultSave()
{
	auto* testObject = NewObject<UMyClass_ConfigDoNotCheckDefaults>(GetTransientPackage(), TEXT("testObjectCheckDefault"));
	auto* testObject2 = NewObject<UMyClass_ConfigDefaultChild>(GetTransientPackage(), TEXT("testObjectDefaultChild"));

	testObject->SaveConfig();
	testObject2->SaveConfig();

}

void UMyClass_Config_Test::TestConfigCheckDefaultLoad()
{
	auto* testObject = NewObject<UMyClass_ConfigDoNotCheckDefaults>(GetTransientPackage(), TEXT("testObjectCheckDefault"));
	auto* testObject2 = NewObject<UMyClass_ConfigDefaultChild>(GetTransientPackage(), TEXT("testObjectDefaultChild"));

}


void UMyClass_Config_Test::TestGlobalConfig()
{

}

void UMyClass_Config_Test::RunTest()
{
	//TestPerObjectConfigLoad();
}
