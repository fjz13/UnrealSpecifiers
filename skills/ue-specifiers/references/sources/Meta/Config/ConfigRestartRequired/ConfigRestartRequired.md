---
title: "ConfigRestartRequired"
id: "meta.ConfigRestartRequired"
kind: "meta"
symbol: "ConfigRestartRequired"
category: "Config"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "使属性在设置里改变后弹出重启编辑器的对话框"
usage: "UPROPERTY"
---

# ConfigRestartRequired

- **功能描述：** 使属性在设置里改变后弹出重启编辑器的对话框。
- **使用位置：** UPROPERTY
- **引擎模块：** Config
- **元数据类型：** bool
- **常用程度：** ★★★

使属性在设置里改变后弹出重启编辑器的对话框。

自然的，一般是用于真的需要重启编辑器的设置。

## 测试代码：

```cpp
public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = ConfigRestartRequired, meta = (ConfigRestartRequired="true"))
	FString MyString_ConfigRestartRequired;
```

## 测试效果：


## 原理：

在SSettingsEditor生效，可见得是在UI窗口发生改变。然后弹出对话框。

```cpp
void SSettingsEditor::NotifyPostChange( const FPropertyChangedEvent& PropertyChangedEvent, class FEditPropertyChain* PropertyThatChanged )
{
		static const FName ConfigRestartRequiredKey = "ConfigRestartRequired";
		if (PropertyChangedEvent.Property->GetBoolMetaData(ConfigRestartRequiredKey) || PropertyChangedEvent.MemberProperty->GetBoolMetaData(ConfigRestartRequiredKey))
		{
						OnApplicationRestartRequiredDelegate.ExecuteIfBound();
		}
}
```

## 行为

UE5.8 property metadata；SettingsEditor/DeveloperSettings 读取它，提示修改后需要重启。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `ObjectMacros.h` config property metadata declaration/comment
  - UE5.8 `SettingsEditor`/`DeveloperSettings` metadata usage

## 常见误用

参数名、属性名或目标宏写错导致 metadata 被保留但没有对应编辑器/Blueprint 行为。
