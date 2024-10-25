# ProjectUserConfig

- **Function Description:** Specifies that the configuration file level to save to is the project user settings at Project/Config/UserXXX.ini.
- **Engine Module:** Config
- **Metadata Type:** bool
- **Action Mechanism:** Add [CLASS_ProjectUserConfig](../../../../Flags/EClassFlags/CLASS_ProjectUserConfig.md) within ClassFlags
- **Associated Items:** [Config](../Config.md)
- **Common Usage:** ★★★

Specifies that the configuration file level to save to is the project user settings at Project/Config/UserXXX.ini.

## Sample Code:

The directory to save to is \Hello\Config\UserMyGame.ini

```cpp
UCLASS(Config = MyGame, ProjectUserConfig)
class INSIDER_API UMyClass_ProjectUserConfig :public UDeveloperSettings
{
	GENERATED_BODY()
public:
	/** Gets the settings container name for the settings, either Project or Editor */
	virtual FName GetContainerName() const override { return TEXT("Project"); }
	/** Gets the category for the settings, some high level grouping like, Editor, Engine, Game...etc. */
	virtual FName GetCategoryName() const override { return TEXT("MyGame"); }
	/** The unique name for your section of settings, uses the class's FName. */
	virtual FName GetSectionName() const override { return TEXT("MyProjectGame"); }
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Config)
		int32 MyPropertyWithConfig = 123;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, GlobalConfig)
		int32 MyPropertyWithGlobalConfig = 456;
};

//Result: \Hello\Config\UserMyGame.ini
[/Script/Insider.MyClass_ProjectUserConfig]
MyPropertyWithConfig=777
MyPropertyWithGlobalConfig=888
```

## Example Effect:

![Untitled](Untitled.png)

## Search in the source code:

```cpp
UCLASS(config = Engine, projectuserconfig, meta = (DisplayName = "Rendering Overrides (Local)"))
class ENGINE_API URendererOverrideSettings : public UDeveloperSettings
{
}
```