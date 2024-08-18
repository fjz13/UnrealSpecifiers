# SystemGameplayAttribute

功能描述: 把UAbilitySystemComponent子类里面的属性暴露到FGameplayAttribute 选项框里。
使用位置: UPROPERTY
Feature: Blueprint
引擎模块: GAS
元数据类型: bool
限制类型: UAbilitySystemComponent子类里面的属性
Status: Done
Parent item: HideInDetailsView (HideInDetailsView.md)
常用程度: 3

把UAbilitySystemComponent子类里面的属性暴露到FGameplayAttribute 选项框里。

源码例子：

```cpp
UCLASS(ClassGroup=AbilitySystem, hidecategories=(Object,LOD,Lighting,Transform,Sockets,TextureStreaming), editinlinenew, meta=(BlueprintSpawnableComponent))
class GAMEPLAYABILITIES_API UAbilitySystemComponent : public UGameplayTasksComponent, public IGameplayTagAssetInterface, public IAbilitySystemReplicationProxyInterface
{
	/** Internal Attribute that modifies the duration of gameplay effects created by this component */
	UPROPERTY(meta=(SystemGameplayAttribute="true"))
	float OutgoingDuration;

	/** Internal Attribute that modifies the duration of gameplay effects applied to this component */
	UPROPERTY(meta = (SystemGameplayAttribute = "true"))
	float IncomingDuration;
}
```

测试代码：

```cpp
UCLASS(Blueprintable, BlueprintType)
class UMyAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GAS")
	float MyFloat;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GAS", meta = (SystemGameplayAttribute))
	float MyFloat_System;
};

UCLASS()
class UMyAttributeSetTest : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GAS")
	FGameplayAttribute MyAttribute;
};

```

测试效果：

可见MyFloat_System可以暴露到选项列表里去。

![Untitled](SystemGameplayAttribute/Untitled.png)

原理：

也是在GetAllAttributeProperties判断属性上的SystemGameplayAttribute标记。

```cpp
void FGameplayAttribute::GetAllAttributeProperties(TArray<FProperty*>& OutProperties, FString FilterMetaStr, bool UseEditorOnlyData)
{
	// UAbilitySystemComponent can add 'system' attributes
	if (Class->IsChildOf(UAbilitySystemComponent::StaticClass()) && !Class->ClassGeneratedBy)
	{
		for (TFieldIterator<FProperty> PropertyIt(Class, EFieldIteratorFlags::ExcludeSuper); PropertyIt; ++PropertyIt)
		{
			FProperty* Property = *PropertyIt;
	
	
			// SystemAttributes have to be explicitly tagged
			if (Property->HasMetaData(TEXT("SystemGameplayAttribute")) == false)
			{
				continue;
			}
			OutProperties.Add(Property);
		}
	}
}
```