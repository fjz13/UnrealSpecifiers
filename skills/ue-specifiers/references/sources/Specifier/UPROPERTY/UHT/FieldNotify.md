---
title: "FieldNotify"
id: "UPROPERTY.FieldNotify"
kind: "specifier"
symbol: "FieldNotify"
scope: "UPROPERTY"
category: "UHT"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "在打开MVVM插件后，使得该属性变成支持FieldNotify的属性"
usage: "UPROPERTY / UHT"
---

# FieldNotify

## Decision Summary

- **Use when:** 属性变化需要参与 UE Field Notification/绑定通知工作流。
- **Do not use when:** 属性只是普通数据字段，或通知可以由显式 delegate/event 完成。
- **Requires:** 目标类和模块应支持 FieldNotify 使用路径。
- **Conflicts:** 不替代 replication notify、setter 校验或普通 Blueprint dispatch。
- **Prefer instead:** 普通 gameplay 变化通知用 delegate、event 或 RepNotify。

- **功能描述：** 在打开MVVM插件后，使得该属性变成支持FieldNotify的属性。

- **元数据类型：** bool
- **引擎模块：** MVVM, UHT
- **限制类型：** ViewModel里的属性
- **常用程度：** ★★★★

在打开MVVM插件后，使得该属性变成支持FieldNotify的属性。
## UE5.8 审计结论

UE5.8 UHT 或宏路径仍保留该条目；本轮按 UE5.8 标记为已验证。P3 中不少条目属于引擎内部、NoExportTypes 或插件专用用法，不建议普通项目代码直接套用。

## 测试代码：

```cpp
UCLASS(BlueprintType)
class INSIDER_API UMyViewModel :public UMVVMViewModelBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, Setter, BlueprintSetter = SetHP)
	float HP = 1.f;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, Setter, BlueprintSetter = SetMaxHP)
	float MaxHP = 100.f;
public:
	float GetHP()const { return HP; }
	UFUNCTION(BlueprintSetter)
	void SetHP(float val)
	{
		if (UE_MVVM_SET_PROPERTY_VALUE(HP, val))
		{
			UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetHPPercent);
		}
	}

	float GetMaxHP()const { return MaxHP; }
	UFUNCTION(BlueprintSetter)
	void SetMaxHP(float val)
	{
		if (UE_MVVM_SET_PROPERTY_VALUE(MaxHP, val))
		{
			UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetHPPercent);
		}
	}

	//You need to manually notify that GetHealthPercent changed when CurrentHealth or MaxHealth changed.
	UFUNCTION(BlueprintPure, FieldNotify)
	float GetHPPercent() const
	{
		return (MaxHP != 0.f) ? HP / MaxHP : 0.f;
	}
};

```

## 测试效果：

效果一方面是UHT生成的.generated.h里和.gen.cpp里的代码，具体的宏作用就不展开了，大家可查看其他更细致的MVVM相关文章。这里只要知道UHT会为标了FieldNotify的属性定义FFieldId以及FFieldNotificationClassDescriptor来标识一个接受可通知的属性。

```cpp
//MyViewModel.generated.h
#define FID_GitWorkspace_Hello_Source_Insider_Property_MVVM_MyViewModel_h_12_FIELDNOTIFY \
	UE_FIELD_NOTIFICATION_DECLARE_CLASS_DESCRIPTOR_BEGIN(INSIDER_API ) \
	UE_FIELD_NOTIFICATION_DECLARE_FIELD(HP) \
	UE_FIELD_NOTIFICATION_DECLARE_FIELD(MaxHP) \
	UE_FIELD_NOTIFICATION_DECLARE_FIELD(GetHPPercent) \
	UE_FIELD_NOTIFICATION_DECLARE_ENUM_FIELD_BEGIN(HP) \
	UE_FIELD_NOTIFICATION_DECLARE_ENUM_FIELD(MaxHP) \
	UE_FIELD_NOTIFICATION_DECLARE_ENUM_FIELD(GetHPPercent) \
	UE_FIELD_NOTIFICATION_DECLARE_ENUM_FIELD_END() \
	UE_FIELD_NOTIFICATION_DECLARE_CLASS_DESCRIPTOR_END();
//MyViewModel.gen.cpp
	UE_FIELD_NOTIFICATION_IMPLEMENT_FIELD(UMyViewModel, HP)
	UE_FIELD_NOTIFICATION_IMPLEMENT_FIELD(UMyViewModel, MaxHP)
	UE_FIELD_NOTIFICATION_IMPLEMENT_FIELD(UMyViewModel, GetHPPercent)
	UE_FIELD_NOTIFICATION_IMPLEMENTATION_BEGIN(UMyViewModel)
	UE_FIELD_NOTIFICATION_IMPLEMENT_ENUM_FIELD(UMyViewModel, HP)
	UE_FIELD_NOTIFICATION_IMPLEMENT_ENUM_FIELD(UMyViewModel, MaxHP)
	UE_FIELD_NOTIFICATION_IMPLEMENT_ENUM_FIELD(UMyViewModel, GetHPPercent)
	UE_FIELD_NOTIFICATION_IMPLEMENTATION_END(UMyViewModel);
```

蓝图效果：

这些控件的属性就可以和ViewModel里的属性绑定起来。

