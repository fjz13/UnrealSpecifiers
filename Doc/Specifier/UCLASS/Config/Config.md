# Config

- **功能描述：** 指定配置文件的名字，把该对象的值保存到ini配置文件中。
- **引擎模块：**Config
- **元数据类型：**string="abc"
- **作用机制：**Config文件名存在FName UClass::ClassConfigName这个参数里
- **关联项：**[PerObjectConfig](PerObjectConfig.md)、[ConfigDoNotCheckDefaults](ConfigDoNotCheckDefaults.md)、[DefaultConfig](DefaultConfig/DefaultConfig.md)、[GlobalUserConfig](GlobalUserConfig/GlobalUserConfig.md)、[ProjectUserConfig](ProjectUserConfig/ProjectUserConfig.md)
- **常用程度：★★★★★**

指定配置文件的名字，把该对象的值保存到ini配置文件中。

- 一整个类在ini中只有一个节的值，因此一般是保存的CDO对象，但也可以用普通对象。
- Config文件名称的元数据值保存在FName UClass::ClassConfigName。
- 默认是保存在Saved/XXX.ini的Local文件中。
- 此说明符会传播到所有子类并且无法使此说明符无效，但是子类可通过重新声明config说明符并提供不同的ConfigName来更改配置文件。
- 常见的ConfigName值是“Engine”、“Editor”、“Input”和“Game”。
- 可以自己手动调用SaveConfig和LoadConfig来读写配置值。CDO的值会被引擎自己的从配置中读取而更新。
- 想保存到配置文件里的属性要相应的用UPROPERTY(config)修饰。

## 示例代码：

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

## 原理：

在引擎启动的时候UObjectLoadAllCompiledInDefaultProperties会加载所有Class的CDO，在多个调用链条之后会自动的调用CDO的LoadConfig来初始化CDO的值。

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