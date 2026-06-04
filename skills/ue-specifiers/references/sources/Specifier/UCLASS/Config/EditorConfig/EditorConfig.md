---
title: "EditorConfig"
id: "UCLASS.EditorConfig"
kind: "specifier"
symbol: "EditorConfig"
scope: "UCLASS"
category: "Config"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "用来在编辑器状态下保存信息"
usage: "UCLASS / Config"
---

# EditorConfig

- **功能描述：**  用来在编辑器状态下保存信息。
- **引擎模块：** Config, Editor
- **元数据类型：** string="abc"
- **作用机制：** 在Meta中增加[EditorConfig](../../../../Meta/Config/EditorConfig.md)
- **常用程度：★**

用来在编辑器状态下保存信息。

一般用在EditorTarget的Module里，用于配置相应编辑器的信息，比如列宽，收藏夹之类的，用json保存。

保存在：C:\Users\{user name}\AppData\Local\UnrealEngine\Editor。当前有：


在源码里搜索后，使用的时候必须继承于基类：

```cpp
/** Inherit from this class to simplify saving and loading properties from editor configs. */
UCLASS()
class EDITORCONFIG_API UEditorConfigBase : public UObject
{
	GENERATED_BODY()

public:

	/** Load any properties of this class into properties marked with metadata tag "EditorConfig" from the class's EditorConfig */
	bool LoadEditorConfig();

	/** Save any properties of this class in properties marked with metadata tag "EditorConfig" into the class's EditorConfig. */
	bool SaveEditorConfig() const;
};
```

## 示例代码：

```cpp
UCLASS(EditorConfig = "MyEditorGame")
class INSIDER_API UMyClass_EditorConfig : public UEditorConfigBase
{
public:
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditorConfig))
	int32 MyPropertyWithConfig = 123;
};

void UMyClass_EditorConfig_Test::TestConfigSave()
{
	//must run after editor initialization
	auto* testObject = NewObject<UMyClass_EditorConfig>(GetTransientPackage(), TEXT("testObject_EditorConfig"));
	testObject->MyPropertyWithConfig = 777;
	testObject->SaveEditorConfig();

}

void UMyClass_EditorConfig_Test::TestConfigLoad()
{
	auto* testObject = NewObject<UMyClass_EditorConfig>(GetTransientPackage(), TEXT("testObject_EditorConfig"));
	testObject->LoadEditorConfig();
}

//运行Save后的保存结果：C:\Users\jack.fu\AppData\Local\UnrealEngine\Editor\MyEditorGame.json

{
	"$type": "MyClass_EditorConfig",
	"MyPropertyWithConfig": 777
}
```

## 行为

UE5.8 UHT 写入 `EditorConfig` metadata，标记 editor config 上下文。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `UhtClassSpecifiers.cs` class specifier branch
  - UE5.8 `UhtClass.cs` class flag/metadata resolution and validation

## 常见误用

把 class specifier 的 metadata/flag 结果和 property/function specifier 混淆；或忽略继承/撤销类 specifier 的相互作用。
