# PerObjectConfig

- **Function description:** Specifies that when a config file name already exists, values should be stored for each object instance rather than for the entire class.
- **Engine module:** Config
- **Metadata type:** bool
- **Action mechanism:** Add [CLASS_PerObjectConfig](../../../Flags/EClassFlags/CLASS_PerObjectConfig.md) to ClassFlags
- **Associated items:** [Config](Config.md)
- **Commonly used:** ★★★★★

When a config file name already exists, it specifies that values should be stored per object instance rather than per class.

- The configuration information for this class will be stored per object. In the .ini file, each object will have a dedicated section named after the object, formatted as [ObjectName ClassName].
- This specifier is inherited by subclasses. It indicates that the configuration should be saved individually for each object.

## 1	Example Code:

Note that ObjectName must be consistent

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
	//testObject1->LoadConfig();	// LoadConfig does not need to be explicitly called

	UMyClass_PerObjectConfig* testObject2 = NewObject<UMyClass_PerObjectConfig>(GetTransientPackage(), TEXT("testObject2"));
	//testObject2->LoadConfig();
}

//\Saved\Config\WindowsEditor\Game.ini
[testObject1 MyClass_PerObjectConfig]
MyPropertyWithConfig=456

[testObject2 MyClass_PerObjectConfig]
MyPropertyWithConfig=789
```

## 2	Principle:

At the end of object construction, the object attempts to read its configuration.

```cpp
void FObjectInitializer::PostConstructInit()
{
	//During the NewObject construction, it will be called subsequently
	if (bIsCDO || Class->HasAnyClassFlags(CLASS_PerObjectConfig))
	{
		Obj->LoadConfig(NULL, NULL, bIsCDO ? UE::LCPF_ReadParentSections : UE::LCPF_None);
	}
}
```