# DisableNativeTick

- **功能描述：** 禁用该UserWidget的NativeTick。
- **使用位置：** UCLASS
- **引擎模块：** Widget Property
- **元数据类型：** bool
- **限制类型：** UserWidget的子类
- **常用程度：** ★★★

禁用该UserWidget的NativeTick。

如果只有C++类则不起作用，因为纯C++的Widget没有WidgetBPClass 。

而且BP的子类要删除Tick蓝图节点。

## 测试代码：

```cpp
UCLASS(BlueprintType, meta=())
class INSIDER_API UMyWidget_WithNativeTick :public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override
	{
		Super::NativeTick(MyGeometry, InDeltaTime);
		UKismetSystemLibrary::PrintString(nullptr, TEXT("WithNativeTick"), true);
	}
};

UCLASS(BlueprintType,meta=(DisableNativeTick))
class INSIDER_API UMyWidget_DisableNativeTick :public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override
	{
		Super::NativeTick(MyGeometry, InDeltaTime);
		UKismetSystemLibrary::PrintString(nullptr, TEXT("DisableNativeTick"), true);
	}
};
```

## 测试效果：

在蓝图中分别创建UMyWidget_WithNativeTick 和UMyWidget_DisableNativeTick 的子类UMG_WithTick和UMG_DisableTick。然后把他们都添加到一个UMG里，添加到屏幕上后观察NativeTick的调用情况。

可见只有WithNativeTick调用。

![Untitled](Untitled.png)

## 原理：

在UCLASS上标记会导致UMG蓝图的bClassRequiresNativeTick=false。继而在UUserWidget的UpdateCanTick里判断。如果WidgetBPClass不为空（是蓝图子类）且ClassRequiresNativeTick为false，bCanTick 才一开始为false。然后判断bHasScriptImplementedTick则要求蓝图中没有EventTick（默认会创建，自己要手动删掉）。然后后面继续判断要没有延迟蓝图节点，没有动画。总之就是这个Widget要真的没有Tick的需求，则可以真的最后bCanTick=false。

```cpp

void UWidgetBlueprint::UpdateTickabilityStats(bool& OutHasLatentActions, bool& OutHasAnimations, bool& OutClassRequiresNativeTick)
{
		static const FName DisableNativeTickMetaTag("DisableNativeTick");
		const bool bClassRequiresNativeTick = !NativeParent->HasMetaData(DisableNativeTickMetaTag);
		OutClassRequiresNativeTick = bClassRequiresNativeTick;

}

void FWidgetBlueprintCompilerContext::CopyTermDefaultsToDefaultObject(UObject* DefaultObject)
{
		WidgetBP->UpdateTickabilityStats(bClassOrParentsHaveLatentActions, bClassOrParentsHaveAnimations, bClassRequiresNativeTick);
		WidgetClass->SetClassRequiresNativeTick(bClassRequiresNativeTick);
}

void UUserWidget::UpdateCanTick()
{
		UWidgetBlueprintGeneratedClass* WidgetBPClass = Cast<UWidgetBlueprintGeneratedClass>(GetClass());
		bCanTick |= !WidgetBPClass || WidgetBPClass->ClassRequiresNativeTick();
		bCanTick |= bHasScriptImplementedTick;
		bCanTick |= World->GetLatentActionManager().GetNumActionsForObject(this) != 0;
		bCanTick |= ActiveSequencePlayers.Num() > 0;
		bCanTick |= QueuedWidgetAnimationTransitions.Num() > 0;
		SafeGCWidget->SetCanTick(bCanTick);
}
```