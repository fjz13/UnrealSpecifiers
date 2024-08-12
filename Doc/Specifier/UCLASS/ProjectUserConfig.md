# ProjectUserConfig

Type: bool
Feature: Config
Description: 只保存到项目用户设置里，即Project/Config/User*.ini
EClassFlagsOperation: |=
EClassFlags: CLASS_ProjectUserConfig (../../Flags/EClassFlags/CLASS_ProjectUserConfig.md)
Status: Done

保存的目录是\Hello\Config\UserMyGame.ini

在源码中搜索：

```cpp
UCLASS(config = Engine, projectuserconfig, meta = (DisplayName = "Rendering Overrides (Local)"))
class ENGINE_API URendererOverrideSettings : public UDeveloperSettings
{
}
```

测试代码：

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

//结果：\Hello\Config\UserMyGame.ini
[/Script/Insider.MyClass_ProjectUserConfig]
MyPropertyWithConfig=777
MyPropertyWithGlobalConfig=888
```

图片：

![Untitled](ProjectUserConfig/Untitled.png)