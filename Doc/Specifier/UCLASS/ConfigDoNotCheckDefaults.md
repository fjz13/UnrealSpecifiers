# ConfigDoNotCheckDefaults

Type: bool
Feature: Config
Description: 在保存配置的时候，决定是否要先根据Base或Default的配置来检查属性是否一致，如果一致就不用序列化写入下来。
EClassFlagsOperation: |=
EClassFlags: CLASS_ConfigDoNotCheckDefaults (../../Flags/EClassFlags/CLASS_ConfigDoNotCheckDefaults.md)
Status: Done

在SaveConfig的时候，决定是否要先检查Parent的CDO值是否一致，默认的行为是如果一致，就不用保存。但加上这个标志后，就无论如何都要保存。

UCLASS(config=XXX,configdonotcheckdefaults)：表示这个类对应的配置文件不会检查XXX层级上层的DefaultXXX配置文件是否有该信息（后面会解释层级），就直接存储到Saved目录下。

```cpp
const bool bShouldCheckIfIdenticalBeforeAdding = !GetClass()->HasAnyClassFlags(CLASS_ConfigDoNotCheckDefaults) && !bPerObject && bIsPropertyInherited;
//简单的示例判断
if (!bPropDeprecated && (!bShouldCheckIfIdenticalBeforeAdding || !Property->Identical_InContainer(this, SuperClassDefaultObject, Index)))
{
	FString	Value;
	Property->ExportText_InContainer( Index, Value, this, this, this, PortFlags );
	Config->SetString( *Section, *Key, *Value, PropFileName );
}
else
{
	// If we are not writing it to config above, we should make sure that this property isn't stagnant in the cache.
	Config->RemoveKey( *Section, *Key, PropFileName );
}
```

测试代码

```cpp
UCLASS(Config = Game,configdonotcheckdefaults)
class INSIDER_API UMyClass_ConfigDoNotCheckDefaults :public UMyClass_Config
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Config)
		int32 MyPropertyWithConfigSub = 123;
};

UCLASS(Config = Game)
class INSIDER_API UMyClass_ConfigDefaultChild :public UMyClass_Config
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Config)
		int32 MyPropertyWithConfigSub = 123;
};

void UMyClass_Config_Test::TestConfigCheckDefaultSave()
{
	auto* testObject = NewObject<UMyClass_ConfigDoNotCheckDefaults>(GetTransientPackage(), TEXT("testObjectCheckDefault"));
	auto* testObject2 = NewObject<UMyClass_ConfigDefaultChild>(GetTransientPackage(), TEXT("testObjectDefaultChild"));

	testObject->SaveConfig();
	testObject2->SaveConfig();
}

生成：
[/Script/Insider.MyClass_Config]
MyPropertyWithConfig=777

[/Script/Insider.MyClass_ConfigDoNotCheckDefaults]
MyPropertyWithConfigSub=123
MyPropertyWithConfig=777

[/Script/Insider.MyClass_ConfigDefaultChild]
MyPropertyWithConfigSub=123
```

由此可见，MyPropertyWithConfig的值默认跟UMyClass_Config中的777值一致，但是依然会写入进来。在第二个类中，MyPropertyWithConfig的值因为没有改变，就会被略过。

在源码里搜configdonotcheckdefaults的时候发现常常和defaultconfig配合使用。什么时候应该使用configdonotcheckdefaults？感觉是为了保持自己的完整性，无论如何都要全部写入进去。

UCLASS(config=GameUserSettings, configdonotcheckdefaults)
class ENGINE_API UGameUserSettings : public UObject