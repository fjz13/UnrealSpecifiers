# FieldNotify

功能描述: 为该函数创建一个FieldNotify的绑定点。
元数据类型: bool
引擎模块: UHT
限制类型: ViewModel里的函数
Status: Done
常用程度: 3

为该函数创建一个FieldNotify的绑定点。

需要注意的是，如果是Get函数则其返回值改变的时候，需要在别的触发改变的地方手动广播事件。正如下面的代码UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetHPPercent);所做的。

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

可见GetHPPercent有生成一个FIELD。

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

进度条可以绑定到GetHPPercent。

![Untitled](FieldNotify/Untitled.png)