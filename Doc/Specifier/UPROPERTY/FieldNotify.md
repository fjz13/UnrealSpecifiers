# FieldNotify

Type: bool
Feature: UHT
LimitedType: ViewModel里的属性
Description: 在打开MVVM插件后，使得该属性变成支持FieldNotify的属性。
Status: Done

在打开MVVM插件后，使得该属性变成支持FieldNotify的属性。

测试代码：

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

测试效果：

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

![Untitled](FieldNotify/Untitled.png)