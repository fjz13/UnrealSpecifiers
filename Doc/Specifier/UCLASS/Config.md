# Config

Description: 指定配置文件的名字。默认是保存在Saved/XXX.ini的Local文件中
把CDO的值存储在init文件中。
指示此类可在配置文件（.ini）中存储数据。如果存在任何使用config或globalconfig说明符声明的类属性，此说明符将使这些属性存储在指定的配置文件中。此说明符会传播到所有子类并且无法使此说明符无效，但是子类可通过重新声明config说明符并提供不同的ConfigName来更改配置文件。常见的ConfigName值是“Engine”、“Editor”、“Input”和“Game”。指定该类的属性可以被保存在ini文件中。这个不可以被子类撤销，但可以重新改写ConfigName
Feature: Config
Type: string="abc"
Example: Config=ConfigName
Common ConfigName values are "Engine", "Editor", "Input", and "Game".
Status: Done
Code: FName UClass::ClassConfigName

Config的值保存在FName UClass::ClassConfigName中

保存CDO对象的值到ini配置文件中

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

//测试代码
UMyClass_Config* testObject = NewObject<UMyClass_Config>(GetTransientPackage(),TEXT("testObject"));
testObject->SaveConfig();

//生成
\Hello\Saved\Config\WindowsEditor\Game.ini
[/Script/Insider.MyClass_Config]
MyPropertyWithConfig=123
```

在引擎启动的时候UObjectLoadAllCompiledInDefaultProperties会加载所有Class的CDO，从而会自动的调用CDO的LoadConfig