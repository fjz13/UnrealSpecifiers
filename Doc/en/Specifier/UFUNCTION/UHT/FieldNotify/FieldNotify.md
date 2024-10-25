# FieldNotify

- **Function Description:** Establish a binding point for FieldNotify for this function.
- **Metadata Type:** bool
- **Engine Module:** UHT
- **Restriction Type:** Functions within the ViewModel
- **Common Usage:** ★★★

Establish a binding point for FieldNotify for this function.

It should be noted that if it is a Get function, when its return value changes, the event needs to be manually broadcast in other places that trigger the change. As the following code UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED ( GetHPPercent ) ; does.

## Test Code:

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

## Test Results:

It can be seen that GetHPPercent generates a FIELD.

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

## Blueprint Effect:

Progress bars can be bound to GetHPPercent.

![Untitled](Untitled.png)