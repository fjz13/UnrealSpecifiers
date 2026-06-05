---
title: "CustomFieldNotify"
id: "UCLASS.CustomFieldNotify"
kind: "specifier"
symbol: "CustomFieldNotify"
scope: "UCLASS"
category: "UHT"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "阻止UHT为该类生成FieldNotify的相关代码"
usage: "UCLASS / UHT"
---

# CustomFieldNotify

## Decision Summary

- **Use when:** `CustomFieldNotify` specifier 的 `UCLASS / UHT` 场景需要：阻止UHT为该类生成FieldNotify的相关代码。
- **Do not use when:** 声明宏、目标类型或代码契约不属于 `UCLASS / UHT`。
- **Requires:** specifier 必须放在 UE5.8 UHT 支持的宏和声明位置，并满足正文 caveat。
- **Conflicts:** 不要和同类互斥 specifier 或语义相反的暴露/持久化/网络规则混用。
- **Prefer instead:** 能用更窄暴露范围或更明确 metadata 表达时，优先选择更窄方案。

- **功能描述：** 阻止UHT为该类生成FieldNotify的相关代码。

- **引擎模块：** UHT
- **元数据类型：** bool
- **作用机制：** 在ClassFlags中增加HasCustomFieldNotify
- **常用程度：** 0

阻止UHT为该类生成FieldNotify的相关代码。

在源码里只在UWidget上使用，例如该类里面的bIsEnabled是FieldNotify，正常来说UHT要为其生成代码。但如果该类想自己手动书写这些UHT代码，则可以加上CustomFieldNotify来阻止UHT生成。UWidget的cpp里因为要用别的方式UE_FIELD_NOTIFICATION_IMPLEMENT_CLASS_DESCRIPTOR，因此要拒绝UHT生成。

如果自己的类也要自己UE_FIELD_NOTIFICATION_IMPLEMENT_CLASS_DESCRIPTOR，则可以用上CustomFieldNotify。
## UE5.8 审计结论

UE5.8 UHT 或宏路径仍保留该条目；本轮按 UE5.8 标记为已验证。P3 中不少条目属于引擎内部、NoExportTypes 或插件专用用法，不建议普通项目代码直接套用。

## 源码例子：

```cpp
//E:\P4V\Engine\Source\Runtime\UMG\Public\FieldNotification\FieldNotificationDeclaration.h
UCLASS(Abstract, BlueprintType, Blueprintable, CustomFieldNotify)
class UMG_API UWidget : public UVisual, public INotifyFieldValueChanged
{
	GENERATED_UCLASS_BODY()
public:
	UE_FIELD_NOTIFICATION_DECLARE_CLASS_DESCRIPTOR_BASE_BEGIN(UMG_API)
		UE_FIELD_NOTIFICATION_DECLARE_FIELD(ToolTipText)
		UE_FIELD_NOTIFICATION_DECLARE_FIELD(Visibility)
		UE_FIELD_NOTIFICATION_DECLARE_FIELD(bIsEnabled)
		UE_FIELD_NOTIFICATION_DECLARE_ENUM_FIELD_BEGIN(ToolTipText)
		UE_FIELD_NOTIFICATION_DECLARE_ENUM_FIELD(Visibility)
		UE_FIELD_NOTIFICATION_DECLARE_ENUM_FIELD(bIsEnabled)
		UE_FIELD_NOTIFICATION_DECLARE_ENUM_FIELD_END()
	UE_FIELD_NOTIFICATION_DECLARE_CLASS_DESCRIPTOR_BASE_END();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Getter="GetIsEnabled", Setter="SetIsEnabled", BlueprintGetter="GetIsEnabled", BlueprintSetter="SetIsEnabled", Category="Behavior")
	uint8 bIsEnabled:1;

	//cpp
UE_FIELD_NOTIFICATION_IMPLEMENT_CLASS_DESCRIPTOR_ThreeFields(UWidget, ToolTipText, Visibility, bIsEnabled);

```

## 原理：

在判断条件上可见HasCustomFieldNotify的判断。

```cpp
		protected static bool NeedFieldNotifyCodeGen(UhtClass classObj)
		{
			return
				!classObj.ClassExportFlags.HasAnyFlags(UhtClassExportFlags.HasCustomFieldNotify) &&
				classObj.ClassExportFlags.HasAnyFlags(UhtClassExportFlags.HasFieldNotify);
		}

```
