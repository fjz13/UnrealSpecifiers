# ConfigDoNotCheckDefaults

- **功能描述：** 指定在保存配置值的时候忽略上一级的配置值的一致性检查。
- **引擎模块：**Config
- **元数据类型：**bool
- **作用机制：**在ClassFlags中增加[CLASS_ConfigDoNotCheckDefaults](../../../Flags/EClassFlags/CLASS_ConfigDoNotCheckDefaults.md)
- **关联项：**[Config](Config.md)
- **常用程度：★**

指定在保存配置值的时候忽略上一级的配置值的一致性检查。

- 在保存配置的时候，决定是否要先根据Base或Default的配置来检查属性是否一致，如果一致就不用序列化写入下来。但加上这个标志后，即使同上一个层级的配置值相同也无论如何都要保存下来。

UCLASS(config=XXX,configdonotcheckdefaults)：表示这个类对应的配置文件不会检查XXX层级上层的DefaultXXX配置文件是否有该信息（后面会解释层级），就直接存储到Saved目录下。

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
```

## 示例效果：

```cpp
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

由此可见，MyClass_ConfigDoNotCheckDefaults中的MyPropertyWithConfig的值默认跟UMyClass_Config中的777值一致，但是依然会写入进来。在MyClass_ConfigDefaultChild类中，MyPropertyWithConfig的值因为没有改变，就会被略过。

在源码里搜configdonotcheckdefaults的时候发现常常和defaultconfig配合使用。什么时候应该使用configdonotcheckdefaults？感觉是为了保持自己的完整性，无论如何都要全部写入进去。在defaultConfig的时候，就可以不管Base里的值，都写入一份到Default配置里，这样在编辑上更加的完整。

## 原理：

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