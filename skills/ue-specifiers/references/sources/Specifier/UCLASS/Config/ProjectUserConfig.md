---
title: "ProjectUserConfig"
id: "UCLASS.ProjectUserConfig"
kind: "specifier"
symbol: "ProjectUserConfig"
scope: "UCLASS"
category: "Config"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定保存到的配置文件层级是项目用户设置 Project/Config/UserXXX.ini"
usage: "UCLASS / Config"
---

# ProjectUserConfig

## Decision Summary

- **Use when:** `ProjectUserConfig` specifier 的 `UCLASS / Config` 场景需要：指定保存到的配置文件层级是项目用户设置 Project/Config/UserXXX.ini。
- **Do not use when:** 声明宏、目标类型或代码契约不属于 `UCLASS / Config`。
- **Requires:** specifier 必须放在 UE5.8 UHT 支持的宏和声明位置，并满足正文 caveat。
- **Conflicts:** 不要和同类互斥 specifier 或语义相反的暴露/持久化/网络规则混用。
- **Prefer instead:** 能用更窄暴露范围或更明确 metadata 表达时，优先选择更窄方案。

- **功能描述：**  指定保存到的配置文件层级是项目用户设置 Project/Config/UserXXX.ini。
- **引擎模块：** Config
- **元数据类型：** bool
- **作用机制：** 在ClassFlags中增加CLASS_ProjectUserConfig
- **关联项：** [Config](Config.md)
- **常用程度：★★★**

指定保存到的配置文件层级是项目用户设置 Project/Config/UserXXX.ini。

## 示例代码：

保存的目录是\Hello\Config\UserMyGame.ini

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

## 示例效果：


## 在源码中搜索：

```cpp
UCLASS(config = Engine, projectuserconfig, meta = (DisplayName = "Rendering Overrides (Local)"))
class ENGINE_API URendererOverrideSettings : public UDeveloperSettings
{
}
```

## 行为

UE5.8 UHT 写入 `CLASS_ProjectUserConfig`，config 保存到项目用户 override。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `UhtClassSpecifiers.cs` class specifier branch
  - UE5.8 `UhtClass.cs` class flag/metadata resolution and validation

## 常见误用

把 class specifier 的 metadata/flag 结果和 property/function specifier 混淆；或忽略继承/撤销类 specifier 的相互作用。
