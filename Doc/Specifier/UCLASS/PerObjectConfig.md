# PerObjectConfig

Type: bool
Feature: Config
Description: 此类的配置信息将按对象存储，在.ini文件中，每个对象都有一个分段，根据对象命名，格式为[ObjectName ClassName]。此说明符会传播到子类。指定该配置是对每个对象都单独保存。
在ini里会把每个对象的信息当做一个section，类似于[ObjectName ClassName]。
EClassFlagsOperation: |=
EClassFlags: CLASS_PerObjectConfig (../../Flags/EClassFlags/CLASS_PerObjectConfig.md)
Status: Done

注意Object Name必须一致

测试代码：

```cpp
UCLASS(Config = Game,PerObjectConfig)
class INSIDER_API UMyClass_PerObjectConfig :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyProperty = 123;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Config)
		int32 MyPropertyWithConfig = 123;
};

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
	//testObject1->LoadConfig();	//不需要显式调用LoadConfig

	UMyClass_PerObjectConfig* testObject2 = NewObject<UMyClass_PerObjectConfig>(GetTransientPackage(), TEXT("testObject2"));
	//testObject2->LoadConfig();
}

//\Saved\Config\WindowsEditor\Game.ini
[testObject1 MyClass_PerObjectConfig]
MyPropertyWithConfig=456

[testObject2 MyClass_PerObjectConfig]
MyPropertyWithConfig=789
```

引擎机制代码：

```cpp
void FObjectInitializer::PostConstructInit()
{
//在NewObject构造中后面会调用
if (bIsCDO || Class->HasAnyClassFlags(CLASS_PerObjectConfig))
{
	Obj->LoadConfig(NULL, NULL, bIsCDO ? UE::LCPF_ReadParentSections : UE::LCPF_None);
}
}
```