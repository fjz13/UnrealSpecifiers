# DefaultConfig

- **Function description:** Specifies that the configuration file level to save to is Project/Config/DefaultXXX.ini.
- **Engine module:** Config
- **Metadata type:** bool
- **Action mechanism:** Add [CLASS_DefaultConfig](../../../../Flags/EClassFlags/CLASS_DefaultConfig.md) to ClassFlags
- **Associated items:** [Config](../Config.md)
- **Commonly used:** ★★★

The specified level for saving the configuration file is Project/Config/DefaultXXX.ini.

- Instead of the default Saved/XXX.ini
- Usually used in the editor to automatically save Settings to Project/Config/DefaultXXX.ini

## Sample Code:

```cpp
UCLASS(Config = MyGame,DefaultConfig)
class INSIDER_API UMyClass_DefaultConfig :public UDeveloperSettings
{
	GENERATED_BODY()
public:
	/** Gets the settings container name for the settings, either Project or Editor */
	virtual FName GetContainerName() const override { return TEXT("Project"); }
	/** Gets the category for the settings, some high level grouping like, Editor, Engine, Game...etc. */
	virtual FName GetCategoryName() const override { return TEXT("MyGame"); }
	/** The unique name for your section of settings, uses the class's FName. */
	virtual FName GetSectionName() const override { return TEXT("MyGame"); }
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Config)
		int32 MyPropertyWithConfig = 123;
};

//Saved Results:
//Config/DefaultMyGame.ini
[/Script/Insider.MyClass_DefaultConfig]
MyPropertyWithConfig=888

```

## Example Results:

![Untitled](Untitled.png)

## Principle:

In the code, one should use Settings->TryUpdateDefaultConfigFile();, but it has been observed that TryUpdateDefaultConfigFile can be called regardless of whether DefaultConfig exists, and it will save to the Default configuration. Therefore, which SaveConfig method (TryUpdateDefaultConfigFile, UpdateGlobalUserConfigFile, UpdateProjectUserConfigFile) to call can be manually specified.

However, when editing in the editor, the logic can be handled through well-written code. For instance, in SSettingsEditor.cpp, calling Section->Save(); in NotifyPostChange will internally invoke the following code:

```cpp
bool FSettingsSection::Save()
{
	if (ModifiedDelegate.IsBound() && !ModifiedDelegate.Execute())
	{
		return false;
	}

	if (SaveDelegate.IsBound())
	{
		return SaveDelegate.Execute();
	}

	//Update to the Correct File
	if (SettingsObject.IsValid())
	{
		if (SettingsObject->GetClass()->HasAnyClassFlags(CLASS_DefaultConfig))
		{
			SettingsObject->TryUpdateDefaultConfigFile();
		}
		else if (SettingsObject->GetClass()->HasAnyClassFlags(CLASS_GlobalUserConfig))
		{
			SettingsObject->UpdateGlobalUserConfigFile();
		}
		else if (SettingsObject->GetClass()->HasAnyClassFlags(CLASS_ProjectUserConfig))
		{
			SettingsObject->UpdateProjectUserConfigFile();
		}
		else
		{
			SettingsObject->SaveConfig();
		}

		return true;
	}

	return false;
}
```