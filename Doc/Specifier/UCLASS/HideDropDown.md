# HideDropDown

Type: bool
Feature: DetailsPanel
Description: 在类选择器中隐藏此类
EClassFlagsOperation: |=
EClassFlags: CLASS_HideDropDown (../../Flags/EClassFlags/CLASS_HideDropDown.md)
Status: Done

在类选择器中隐藏此类，通常是TSubClassOf触发，或者Class变量触发的类选择窗口。这个时候，这个标识符可以阻止其出现。在源码里的使用，通常是一些旧的废弃的类或者Test类，Abstract类和基类。

```cpp
UCLASS(Blueprintable)
class INSIDER_API UMyClass_HideDropDownBase :public UObject
{
	GENERATED_BODY()
public:
};

UCLASS(Blueprintable, hidedropdown)
class INSIDER_API UMyClass_HideDropDown :public UMyClass_HideDropDownBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyProperty;
};

UCLASS(Blueprintable, hidedropdown)
class INSIDER_API UMyClass_NoHideDropDown :public UMyClass_HideDropDownBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyProperty;
};

UCLASS(Blueprintable)
class INSIDER_API UMyClass_HideDropDown_Test :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UMyClass_HideDropDownBase> DropDownClass;
};
```

![Untitled](HideDropDown/Untitled.png)