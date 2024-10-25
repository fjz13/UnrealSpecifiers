# Config

- **Function description:** Specify the name of the configuration file and save the object's values to the INI configuration file.
- **Engine module:** Config
- **Metadata type:** string="abc"
- **Action mechanism:** The name of the Config file is stored in the parameter FName UClass::ClassConfigName
- **Related items:** [PerObjectConfig](PerObjectConfig.md), [ConfigDoNotCheckDefaults](ConfigDoNotCheckDefaults.md), [DefaultConfig](DefaultConfig/DefaultConfig.md), [GlobalUserConfig](GlobalUserConfig/GlobalUserConfig.md), [ProjectUserConfig](ProjectUserConfig/ProjectUserConfig.md)
- **Commonly used:** ★★★★★

Specify the name of the configuration file and save the object's values to the INI configuration file.

- An entire class is represented by only one section in the INI file, so it is generally a CDO object that is saved, but a regular object can also be used.
- The metadata value for the Config file name is stored in FName UClass::ClassConfigName.
- By default, it is saved in the Local file under Saved/XXX.ini.
- This specifier propagates to all subclasses and cannot be disabled; however, subclasses can change the configuration file by re-declaring the config specifier and providing a different ConfigName.
- Common values for ConfigName include "Engine", "Editor", "Input", and "Game".
- You can manually invoke SaveConfig and LoadConfig to read and write configuration values. The CDO's values will be updated by the engine reading from the configuration.
- Properties intended for saving in the configuration file must be annotated with UPROPERTY(config).

## Sample Code:

```cpp
UCLASS(Config = Game)
class INSIDER_API UMyClass_Config :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyProperty = 123;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Config)
		int32 MyPropertyWithConfig = 123;
};

//Test Code
UMyClass_Config* testObject = NewObject<UMyClass_Config>(GetTransientPackage(),TEXT("testObject"));
testObject->SaveConfig();

//Generate
\Hello\Saved\Config\WindowsEditor\Game.ini
[/Script/Insider.MyClass_Config]
MyPropertyWithConfig=123
```

## Principle:

When the engine starts, UObjectLoadAllCompiledInDefaultProperties loads the CDO for all classes, and after a series of function calls, it automatically invokes LoadConfig to initialize the CDO's values.

```cpp
static void UObjectLoadAllCompiledInDefaultProperties(TArray<UClass*>& OutAllNewClasses)
{
	for (UClass* Class : NewClasses)
	{
		UE_LOG(LogUObjectBootstrap, Verbose, TEXT("GetDefaultObject Begin %s %s"), *Class->GetOutermost()->GetName(), *Class->GetName());
		Class->GetDefaultObject();
		UE_LOG(LogUObjectBootstrap, Verbose, TEXT("GetDefaultObject End %s %s"), *Class->GetOutermost()->GetName(), *Class->GetName());
	}
}
```