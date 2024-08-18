# IsBindableEvent

功能描述: 把一个动态单播委托暴露到UMG蓝图里以绑定相应事件。
使用位置: UPROPERTY
Feature: UMG
引擎模块: Widget Property
元数据类型: bool
限制类型: UWidget子类里动态单播属性
Example: UPROPERTY(meta=(IsBindableEvent))
Status: Done
常用程度: 3

把一个动态单播委托暴露到UMG蓝图里以绑定相应事件。

需要注意的点是：

- 必须是动态委托，就是DYNAMIC的那些，这样才可以在蓝图里序列化。
- 动态多播委托（DECLARE_DYNAMIC_MULTICAST_DELEGATE）默认就可以在UMG里绑定事件，因此没有必要加IsBindableEvent。往往也配合加上BlueprintAssignable以便也可以在蓝图里手动绑定。
- 动态单播委托（DECLARE_DYNAMIC_DELEGATE）默认是不在UMG里暴露的。但可以加上IsBindableEvent以便可以在其实例的细节面板上绑定。
- UMG里的控件事件为什么要有多播和单播？其实多播和单播除了数量不同以外，最大的不同是多播没有返回值。这个例子可以对比UButton下的OnClicked多播事件和UImage下的OnMouseButtonDownEvent单播委托，前者是点击的事件，已经是个“结果”事件了，点击事件可能被多个地方响应，因此要设计成多播。而后者的OnMouseButtonDownEvent是鼠标按下的事件，有一个重要的逻辑是会根据返回值FEventReply的不同而决定该事件是否继续路由上去，因此只能用单播，只能绑定一个。

源码例子：

```cpp
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonClickedEvent);
class UButton : public UContentWidget
{
	UPROPERTY(BlueprintAssignable, Category="Button|Event")
	FOnButtonClickedEvent OnClicked;
}

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(FEventReply, FOnPointerEvent, FGeometry, MyGeometry, const FPointerEvent&, MouseEvent);
class UImage : public UWidget
{
		UPROPERTY(EditAnywhere, Category=Events, meta=( IsBindableEvent="True" ))
		FOnPointerEvent OnMouseButtonDownEvent;
}
```

测试代码：

```cpp
UCLASS(BlueprintType)
class INSIDER_API UMyProperty_BindWidget :public UUserWidget
{
public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMyClickedMulticastDelegate);

	UPROPERTY(EditAnywhere, BlueprintAssignable, Category = MyEvent)
	FOnMyClickedMulticastDelegate MyClickedMulticastDelegate;

public:
	DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(FString,FOnMyClickedDelegate,int32,MyValue);

	UPROPERTY(EditAnywhere, Category = MyEvent)
	FOnMyClickedDelegate MyClickedDelegate_Default;

	UPROPERTY(EditAnywhere, Category = MyEvent)
	FOnMyClickedDelegate MyClickedEvent;

	UPROPERTY(EditAnywhere, Category = MyEvent, meta = (IsBindableEvent = "True"))
	FOnMyClickedDelegate MyClickedDelegate_Bind;
}
```

测试结果：

操作步骤是在UMG_BindTest外再创建一个UMG，然后让UMG_BindTest成为子控件，然后观察其实例上的事件绑定，如下图右侧所示。

- 可以发现动态多播委托默认就会出现可以绑定的+定制化按钮，如MyClickedMulticastDelegate。
- 动态多播委托加上BlueprintAssignable（不能加在单播委托上）了之后，就可以在蓝图里绑定事件，如左下侧图。
- 加了IsBindableEvent 的MyClickedDelegate_Bind，可以看见出现了可以Bind的下拉按钮，绑定之后可以显示函数名字，也可以清除。
- 没有加IsBindableEvent 的MyClickedDelegate_Default就没有出现在可绑定的按钮，你只能在C++里自己绑定了。
- 没有加IsBindableEvent 的MyClickedEvent因为名字以Event结尾也出现了可绑定的按钮，这只能说是当前的一个潜规则。源码注释也说以后会去除。
- 另外这些委托我虽然都加上了EditAnywhere，但其实你也知道这并没法办法编辑。

![Untitled](IsBindableEvent/Untitled.png)

## 原理：

对于Widget的细节面板，引擎也定义了各种Customization。其中对应的就是FBlueprintWidgetCustomization。其针对绑定的部分的代码如下。

代码也很容易理解，动态多播委托默认都出现绑定，动态单播委托有加IsBindableEvent或者名字以Event结尾就也创建绑定按钮。

```cpp
PropertyView->RegisterInstancedCustomPropertyLayout(UWidget::StaticClass(), FOnGetDetailCustomizationInstance::CreateStatic(&FBlueprintWidgetCustomization::MakeInstance, BlueprintEditorRef, BlueprintEditorRef->GetBlueprintObj()));

void FBlueprintWidgetCustomization::PerformBindingCustomization(IDetailLayoutBuilder& DetailLayout, const TArrayView<UWidget*> Widgets)
{
	static const FName IsBindableEventName(TEXT("IsBindableEvent"));

	bCreateMulticastEventCustomizationErrorAdded = false;
	if ( Widgets.Num() == 1 )
	{
		UWidget* Widget = Widgets[0];
		UClass* PropertyClass = Widget->GetClass();

		for ( TFieldIterator<FProperty> PropertyIt(PropertyClass, EFieldIteratorFlags::IncludeSuper); PropertyIt; ++PropertyIt )
		{
			FProperty* Property = *PropertyIt;

			if ( FDelegateProperty* DelegateProperty = CastField<FDelegateProperty>(*PropertyIt) )
			{
				//TODO Remove the code to use ones that end with "Event".  Prefer metadata flag.
				if ( DelegateProperty->HasMetaData(IsBindableEventName) || DelegateProperty->GetName().EndsWith(TEXT("Event")) )
				{
					CreateEventCustomization(DetailLayout, DelegateProperty, Widget);
				}
			}
			else if ( FMulticastDelegateProperty* MulticastDelegateProperty = CastField<FMulticastDelegateProperty>(Property) )
			{
				CreateMulticastEventCustomization(DetailLayout, Widget->GetFName(), PropertyClass, MulticastDelegateProperty);
			}
		}
	}
}
```