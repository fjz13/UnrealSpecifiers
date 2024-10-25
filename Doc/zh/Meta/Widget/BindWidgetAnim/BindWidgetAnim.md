# BindWidgetAnim

- **功能描述：** 指定在C++类中该UWidgetAnimation属性一定要绑定到UMG下的某个动画
- **使用位置：** UPROPERTY
- **引擎模块：** Widget Property
- **元数据类型：** bool
- **限制类型：** UWidget子类里UWidgetAnimation属性
- **关联项：** [BindWidgetAnimOptional](../BindWidgetAnimOptional/BindWidgetAnimOptional.md)
- **常用程度：** ★★★★★

指定在C++类中该UWidgetAnimation属性一定要绑定到UMG下的某个动画。

作用同BindWidget类似，都是用来把C++的属性和BP里的控件或动画赋值绑定起来。但又有一些区别：

- UWidgetAnimation和Widget不同，Widget的属性和控件只要同名就可以自动绑定起来，而UWidgetAnimation就不允许不加BindWidgetAnim而同名，否则会名字冲突报错。这是由于UMG里创建的Widget默认是不创建BP变量的，子控件只是WidgetTree下的一个对象，但是动画是默认会创建BP变量的。因此即使是UMG里先定义动画，然后C++里再定义同名属性，也是会过不了编译的。
- UWidgetAnimation属性必须得是Transient，否则也会报错。我想这是因为UWidgetAnimation自然会在BP里作为子对象序列化，而不需要在C++序列的时候访问到该属性，因此强制Transient以免不小心序列化它。另外UWidgetAnimation只是用作表现，因此其实也会自动的加上CPF_RepSkip，跳过网络复制。

## 测试代码：

```cpp
UCLASS(BlueprintType)
class INSIDER_API UMyProperty_BindWidget :public UUserWidget
{
	GENERATED_BODY()
	UMyProperty_BindWidget(const FObjectInitializer& ObjectInitializer);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetAnimation* MyAnimation_NotFound;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//class UWidgetAnimation* MyAnimation_SameName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* MyAnimation_Bind;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient, meta = (BindWidgetAnimOptional))
	class UWidgetAnimation* MyAnimation_BindOptional;
};
```

## 测试效果：

测试过程和BindWidget类似，在C++和UMG中定义不同类型属性和动画对象。可以根据VS里实际对象的值发现：

- MyAnimation_Bind和MyAnimation_BindOptional都自动的绑定了正确的动画对象。
- 没有加BindWidgetAnim的MyAnimation_SameName必须注释掉，否则会和UMG里的MyAnimation_SameName名字冲突。
- 再提一下，不能像Widget里一样先UMG里定义动画，然后再C++定义同名属性，因为WidgetAnimation是一定会创建BP变量的，这是关键不同。

![Untitled](Untitled.png)

## 原理：

大致逻辑和BindWidget类似，都是判断属性是否BindWidgetAnim。然后相应的在编译和改名的时候判断。

关于动画变量设置PropertyFlags的逻辑在CreateClassVariablesFromBlueprint里，可以看见加上了4个属性，明确了不要序列化该属性。

而为UWidgetAnimation*属性自动绑定赋值的逻辑在BindAnimationsStatic，一眼就懂。

```cpp
bool FWidgetBlueprintEditorUtils::IsBindWidgetAnimProperty(const FProperty* InProperty, bool& bIsOptional)
{
	if (InProperty)
	{
		bool bIsBindWidgetAnim = InProperty->HasMetaData("BindWidgetAnim") || InProperty->HasMetaData("BindWidgetAnimOptional");
		bIsOptional = InProperty->HasMetaData("BindWidgetAnimOptional");

		return bIsBindWidgetAnim;
	}

	return false;
}

void FWidgetBlueprintCompilerContext::CreateClassVariablesFromBlueprint()
{
	for (UWidgetAnimation* Animation : WidgetBP->Animations)
	{
		FEdGraphPinType WidgetPinType(UEdGraphSchema_K2::PC_Object, NAME_None, Animation->GetClass(), EPinContainerType::None, true, FEdGraphTerminalType());
		FProperty* AnimationProperty = CreateVariable(Animation->GetFName(), WidgetPinType);

		if ( AnimationProperty != nullptr )
		{
			const FString DisplayName = Animation->GetDisplayName().ToString();
			AnimationProperty->SetMetaData(TEXT("DisplayName"), *DisplayName);

			AnimationProperty->SetMetaData(TEXT("Category"), TEXT("Animations"));

			AnimationProperty->SetPropertyFlags(CPF_Transient);
			AnimationProperty->SetPropertyFlags(CPF_BlueprintVisible);
			AnimationProperty->SetPropertyFlags(CPF_BlueprintReadOnly);
			AnimationProperty->SetPropertyFlags(CPF_RepSkip);

			WidgetAnimToMemberVariableMap.Add(Animation, AnimationProperty);
		}
	}
}

void FWidgetBlueprintCompilerContext::FinishCompilingClass(UClass* Class)
{
	if (!WidgetAnimProperty->HasAnyPropertyFlags(CPF_Transient))
	{
			const FText BindWidgetAnimTransientError = LOCTEXT("BindWidgetAnimTransient", "The property @@ uses BindWidgetAnim, but isn't Transient!");
			MessageLog.Error(*BindWidgetAnimTransientError.ToString(), WidgetAnimProperty);
	}
}

void UWidgetBlueprintGeneratedClass::BindAnimationsStatic(UUserWidget* Instance, const TArrayView<UWidgetAnimation*> InAnimations, const TMap<FName, FObjectPropertyBase*>& InPropertyMap)
{
	// Note: It's not safe to assume here that the UserWidget class type is a UWidgetBlueprintGeneratedClass!
	// - @see InitializeWidgetStatic()

	for (UWidgetAnimation* Animation : InAnimations)
	{
		if (Animation->GetMovieScene())
		{
			// Find property with the same name as the animation and assign the animation to it.
			if (FObjectPropertyBase*const* PropPtr = InPropertyMap.Find(Animation->GetMovieScene()->GetFName()))
			{
				check(*PropPtr);
				(*PropPtr)->SetObjectPropertyValue_InContainer(Instance, Animation);
			}
		}
	}
}
```