---
title: "PerObjectConfig"
id: "UCLASS.PerObjectConfig"
kind: "specifier"
symbol: "PerObjectConfig"
scope: "UCLASS"
category: "Config"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "在已经有config配置文件名字的情况下，指定应该按每个对象实例来存储值，而不是一个类一个存储值"
usage: "UCLASS / Config"
---

# PerObjectConfig

## Decision Summary

- **Use when:** 每个对象实例需要独立的 config section 存储配置属性。
- **Do not use when:** 类级默认配置已经足够，或值属于运行时状态。
- **Requires:** 类和属性侧 config 语义配套，且对象命名/持久化策略稳定。
- **Conflicts:** 不替代 SaveGame 或实例编辑保存。
- **Prefer instead:** 普通类配置用 `Config`；玩家进度用 SaveGame。

- **功能描述：**  在已经有config配置文件名字的情况下，指定应该按每个对象实例来存储值，而不是一个类一个存储值。
- **引擎模块：** Config
- **元数据类型：** bool
- **作用机制：** 在ClassFlags中增加CLASS_PerObjectConfig
- **关联项：** [Config](Config.md)
- **常用程度：★★★★★**

在已经有config配置文件名字的情况下，指定应该按每个对象实例来存储值，而不是一个类一个存储值。

- 此类的配置信息将按对象存储，在.ini文件中，每个对象都有一个分段，根据对象命名，格式为[ObjectName ClassName]。
- 此说明符会传播到子类。指定该配置是对每个对象都单独保存。

## 示例代码：

注意ObjectName必须一致

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
	//testObject1->LoadConfig();	//不需要显式调用LoadConfig

	UMyClass_PerObjectConfig* testObject2 = NewObject<UMyClass_PerObjectConfig>(GetTransientPackage(), TEXT("testObject2"));
	//testObject2->LoadConfig();
}

//\Saved\Config\WindowsEditor\Game.ini
[testObject1 MyClass_PerObjectConfig]
MyPropertyWithConfig=456

[testObject2 MyClass_PerObjectConfig]
MyPropertyWithConfig=789
```

## 原理：

对象构造的末期会尝试去读取配置。

```cpp
void FObjectInitializer::PostConstructInit()
{
	//在NewObject构造中后面会调用
	if (bIsCDO || Class->HasAnyClassFlags(CLASS_PerObjectConfig))
	{
		Obj->LoadConfig(NULL, NULL, bIsCDO ? UE::LCPF_ReadParentSections : UE::LCPF_None);
	}
}
```

## 行为

UE5.8 UHT 写入 `CLASS_PerObjectConfig`，使 config 按对象实例维度保存。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `UhtClassSpecifiers.cs` class specifier branch
  - UE5.8 `UhtClass.cs` class flag/metadata resolution and validation

## 常见误用

把 class specifier 的 metadata/flag 结果和 property/function specifier 混淆；或忽略继承/撤销类 specifier 的相互作用。
