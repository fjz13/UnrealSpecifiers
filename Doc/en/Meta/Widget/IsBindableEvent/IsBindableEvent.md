#IsBindableEvent

- **Function description:** Exposes a dynamic unicast delegate to UMG blueprints for event binding.
- **Use location:** UPROPERTY
- **Engine module:** Widget Property
- **Metadata type:** bool
- **Restriction type:** Dynamic unicast properties in UWidget subclasses
- **Commonality:** ★★★

Expose a dynamic unicast delegate to UMG blueprints to bind corresponding events.

Points to consider:

- It must be a dynamic delegate, specifically those prefixed with DYNAMIC, to enable serialization in blueprints.
- Dynamic multicast delegates (DECLARE_DYNAMIC_MULTICAST_DELEGATE) are bindable in UMG by default, so there's no need to add IsBindableEvent. They often include BlueprintAssignable as well, allowing manual binding in blueprints.
- Dynamic unicast delegates (DECLARE_DYNAMIC_DELEGATE) are not exposed in UMG by default. However, adding IsBindableEvent allows binding in the instance's details panel.
- Why are there both multicast and unicast events in UMG? Apart from the difference in the number of recipients, the key distinction is that multicast events do not return a value. For example, compare the OnClicked multicast event in UButton with the OnMouseButtonDownEvent unicast delegate in UImage. The former is a click event, already a "conclusive" action that may be handled by multiple recipients, hence designed as multicast. The latter is a mouse press event, where the logic to determine whether the event should continue routing depends on the return value FEventReply, thus requiring unicast.

## Source Code Example:

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

## Test Code:

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

## Test Results:

The steps involve creating another UMG outside UMG_BindTest, making UMG_BindTest a child widget, and observing the event bindings on its instance, as shown in the figure on the right.

- It can be observed that dynamic multicast delegates automatically appear with a customizable bind button, such as MyClickedMulticastDelegate.
- When a dynamic multicast delegate is marked with BlueprintAssignable (not applicable to unicast delegates), it can be bound in blueprints, as shown in the lower left image.
- With IsBindableEvent added to MyClickedDelegate_Bind, a dropdown button for binding appears. After binding, the function name is displayed and can be cleared.
- Without IsBindableEvent, MyClickedDelegate_Default does not appear in the bindable buttons, and you must bind it manually in C++.
- MyClickedEvent without IsBindableEvent also shows a bindable button because its name ends with Event, which can be considered a current workaround. The source code comments suggest this will be removed in the future.
- Although I've added EditAnywhere to these delegates, it's known that they are not actually editable.

![Untitled](Untitled.png)

## Principle:

For the widget's details panel, the engine defines various customizations, including FBlueprintWidgetCustomization. The code for the binding part is as follows.

The code is straightforward: dynamic multicast delegates are bound by default, while dynamic unicast delegates are bound if IsBindableEvent is added or the name ends with Event.

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