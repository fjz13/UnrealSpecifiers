---
title: "Config"
id: "UPROPERTY.Config"
kind: "specifier"
symbol: "Config"
scope: "UPROPERTY"
category: "Config"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定该属性是一个配置属性，该属性可以被序列化读写到ini文件（路径由uclass的config标签指定）中"
usage: "UPROPERTY / Config"
---

# Config

- **功能描述：** 指定该属性是一个配置属性，该属性可以被序列化读写到ini文件（路径由uclass的config标签指定）中。
- **元数据类型：** bool
- **引擎模块：** Config
- **作用机制：** [CPF_Config](../../../Flags/EPropertyFlags/CPF_Config.md)
- **常用程度：** ★★★

指定该属性是一个配置属性，该属性可以被序列化读写到ini文件（路径由uclass的config标签指定）中。

在载入的时候会自动从ini中加载。如果没再加写标记，则会隐含该属性为ReadOnly。

参见UCLASS中的config标记的示例代码和效果。

## 行为

`Config` 会给属性加入 `CPF_Config`。该属性可通过 `LoadConfig` / `SaveConfig` 从 ini 配置读取或写入；配置文件分支由所属类的 `UCLASS(Config=...)` 等 class config 规则决定。

常见写法是类上声明 `UCLASS(Config=Game)` 或项目自定义 config 名，属性上声明 `UPROPERTY(Config)`。如果希望编辑器或 Blueprint 也能访问，还需要额外组合 `EditAnywhere`、`BlueprintReadWrite` 等访问 specifier。

## UE5.8 审计结论

状态：`verified_UE5.8`

UE5.8 UHT 源码 `C:/Program Files/Epic Games/UE_5.8/Engine/Source/Programs/Shared/EpicGames.UHT/Specifiers/UhtPropertyMemberSpecifiers.cs` 中，`Config` 会设置 `EPropertyFlags.Config`。

UE5.8 CoreUObject 源码 `Runtime/CoreUObject/Private/UObject/Obj.cpp` 中，`SaveConfig` 默认以 `CPF_Config` 为 required property flags；`LoadConfig` / `SaveConfig` 通过类 config 名和 section 处理配置读写。

在 `D:/github/GitWorkspace/Hello/Source/Insider/Property/Config/MyProperty_Config.h` 中，`MyPropertyWithConfig` 使用 `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config)`；对应 cpp 中调用 `SaveConfig(CPF_Config, *fileName)` 和 `LoadConfig(nullptr, *fileName)`。`bat/build-hello.bat` 已在 UE5.8 下成功编译 `HelloEditor Win64 Development`。

## 常见误用

- `Config` 本身不指定配置文件名；配置文件名来自 `UCLASS(Config=...)` 或相关 class config 规则。
- `Config` 不等于 SaveGame，也不适合保存频繁变化的玩家进度。
- `Config` 不自动提供 Details Panel 编辑或 Blueprint 访问；这些是独立 specifier。
- 对派生类不应覆盖的配置项，应考虑 `GlobalConfig`。
