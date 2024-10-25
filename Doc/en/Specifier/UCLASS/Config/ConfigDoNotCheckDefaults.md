# ConfigDoNotCheckDefaults

- **Function description:** Specifies to overlook the consistency check of the parent configuration values when saving configuration values.
- **Engine module:** Config
- **Metadata type:** bool
- **Action mechanism:** Add [CLASS_ConfigDoNotCheckDefaults](../../../Flags/EClassFlags/CLASS_ConfigDoNotCheckDefaults.md) to ClassFlags
- **Associated items:** [Config](Config.md)
- **Commonly used:** ★

Specifies that the consistency check of the parent configuration values is ignored when saving configuration values.

- During configuration saving, it determines whether to check the attributes for consistency based on the Base or Default configuration first. If consistent, there is no need to serialize and write them. However, with this flag set, the values will be saved regardless of whether they match the parent configuration values.

UCLASS(config=XXX,configdonotcheckdefaults): Indicates that the configuration file corresponding to this class will not check if the DefaultXXX configuration file at the XXX level contains this information (the hierarchy will be explained later), and will be saved directly to the Saved directory.

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

## Example Effect:

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

As seen here, the value of MyPropertyWithConfig in MyClass_ConfigDoNotCheckDefaults is identical to the 777 value in UMyClass_Config by default, but it will still be written in. In the MyClass_ConfigDefaultChild class, the value of MyPropertyWithConfig will be omitted because it has not been altered.

When searching for configdonotcheckdefaults in the source code, it is often found to be used in conjunction with defaultconfig. When should configdonotcheckdefaults be used? It seems to be for maintaining completeness, ensuring everything is written in regardless. In defaultConfig, you can ignore the values in Base and write a copy to the Default configuration, making the editing more comprehensive.

## Principle:

```cpp
const bool bShouldCheckIfIdenticalBeforeAdding = !GetClass()->HasAnyClassFlags(CLASS_ConfigDoNotCheckDefaults) && !bPerObject && bIsPropertyInherited;
//Simple example judgment
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