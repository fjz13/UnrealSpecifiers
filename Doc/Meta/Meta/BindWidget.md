# BindWidget

Usage: UPROPERTY
Feature: UMG
Type: bool
Description: 指定在C++类中该Widget属性一定要绑定到UMG的某个同名控件。
Example: UPROPERTY(meta=(BindWidget))
LimitedType: UUserWidget子类里属性
Status: Done
Group: Widget Property
Sub-item: BindWidgetOptional (BindWidgetOptional.md), OptionalWidget (OptionalWidget.md)

指定在C++类中该Widget属性一定要绑定到UMG的某个同名控件。

一种平常通用的编程范式是在C++中定义一个UUserWidget子类，然后再在UMG中继承于这个C++类，这样就能把一些逻辑放在C++中实现，而在UMG中排布控件。这个时候常常就会有个需求：需要在C++中用属性引用到UMG中定义的具体控件。

- 在C++里常见的作法是用WidgetTree->FindWidget来通过控件名字查找。但如果类里定义有几十个控件，一一这么做就很繁琐。
- 因此更便利的方式是在C++里定义同名的控件属性，这样就会自动的关联起来，UMG蓝图对象在创建后引擎会自动的给C++中的Widget属性自动赋值到同名的控件。
- 必须要指出：BindWidget只是用作UMG编辑器的编辑和编译提示，让你记得要一一把名字关联上。在C++里定义的该属性，要记得在UMG里也创建同名控件。在UMG中创建或更改的控件名字时，知道在C++中有一个同名属性来关联接收，就不会报错，否则会提示和C++定义的名字冲突。
- 总结BindWidget的作用有二：一是提醒UMG一定要相应的创建同名控件，否则编译抱错误。二是在定义同C++里属性同名的控件的时候，让UMG不会报错。
- 用法建议是为所有你想要绑定的同名属性都显式的加上BindWidget，不要依赖含糊默认的自动同名绑定机制。

## 测试代码：

```cpp
UCLASS(BlueprintType)
class INSIDER_API UMyProperty_BindWidget :public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTextBlock* MyTextBlock_NotFound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTextBlock* MyTextBlock_SameName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* MyTextBlock_Bind;
};

void UMyProperty_BindWidget::RunTest()
{
	//C++里查找Widget的方式
	UTextBlock* bindWidget= WidgetTree->FindWidget(TEXT("MyTextBlock_Bind"));
	check(bindWidget==MyTextBlock_Bind);
}
```

## 测试效果：

测试操作是在C++中定义如上图的UUserWidget基类，然后在UMG中创建蓝图子类。控件的列表如下图所示。

- 为了对比验证，分别在C++和蓝图中定义3个控件，有同名的和非同名的。然后在CreateWidet后在C++中调试查看这3个属性值。
- 可以发现MyTextBlock_Bind和MyTextBlock_SameName都自动的关联上了值，发现关联属性值的逻辑其跟有没有标上BindWidget并没有关系。但是如果在MyTextBlock_SameName勾上变量，也会报名字冲突的错。这是因为勾上变量，会在蓝图中创建一个属性，这样自然就和C++里的冲突。而没有勾上变量的时候，MyTextBlock_SameName本质上只是一个在WidgetTree下的对象，编辑器可以提示同名冲突（C++里先定义然后UMG里再定义），也可以选择不提示（BindWidget的作用了其实）。但如果是也要相应创建BP里的MyTextBlock_SameName变量，这个冲突就是必然存在了。这个时候如果没有加上BindWidget，引擎就会认为这是两个独立的不同的属性（假如你在C++里明明没写BindWidget而引擎自作主张给你BindWidget了，实际可能反而出现更多莫名错误）。只有显式的加上BindWidget，这个时候我们为MyTextBlock_Bind勾上变量，引擎知道C++里已经有个C++属性了，就没必要再创建一个蓝图属性了（这个时候BP面板里没有）。
- MyTextBlock_NotFound并没有值，这很符合逻辑，因为我们也没有在UMG中定义该控件。但是值得注意的是假如我们尝试在UMG中定义该名字的控件，会报错提示名字已经被占用。也很正常，因为这就像C++类的子类里定义成员变量，肯定不能出现成员变量冲突。但假如我们定义MyTextBlock_Bind就不会报这个“名字占用”的错，因为引擎知道C++里有一个同名属性是要用来引用该控件。因此这才是BindWidget的精确作用含义，只是作为提示。这个时候可能有人会问那我的UMG里的MyTextBlock_SameName是怎么创建上去的？不是会报错吗？答案是先在UMG里定义好，然后再在C++里定义，这样就不会报错了。
- 假如最后MyTextBlock_Bind没有在UMG中定义，那么UMG在编译的时候会报想要绑定的控件找不到，提醒你自己说想要BindWidget结果你又不创建。

![Untitled](BindWidget/Untitled.png)

## 原理：

判断一个属性是否是BindWidget的函数是IsBindWidgetProperty这个函数。

在控件改名或编译的时候，用来判断是否要生成错误提示的操作在FinishCompilingClass，大致逻辑就是根据IsBindWidgetProperty判断该控件是否想要绑定，然后根据当前情况，生成提示。

而因为同名而自动关联值的逻辑操作在UWidgetBlueprintGeneratedClass::InitializeWidgetStatic，逻辑其实是遍历WidgetTree下的控件，根据其名字去C++中查找，如果找到就自动的赋值。

```cpp
void UWidgetBlueprintGeneratedClass::InitializeWidgetStatic()
{
	// Find property with the same name as the template and assign the new widget to it.
	if (FObjectPropertyBase** PropPtr = ObjectPropertiesMap.Find(Widget->GetFName()))
	{
		FObjectPropertyBase* Prop = *PropPtr;
		check(Prop);
		Prop->SetObjectPropertyValue_InContainer(UserWidget, Widget);
		UObject* Value = Prop->GetObjectPropertyValue_InContainer(UserWidget);
		check(Value == Widget);
	}
	
}

void FWidgetBlueprintCompilerContext::FinishCompilingClass(UClass* Class)
{
	// Check that all BindWidget properties are present and of the appropriate type
	for (TFObjectPropertyBase<UWidget*>* WidgetProperty : TFieldRange<TFObjectPropertyBase<UWidget*>>(ParentClass))
	{
		bool bIsOptional = false;
	
		if (FWidgetBlueprintEditorUtils::IsBindWidgetProperty(WidgetProperty, bIsOptional))
		{}
	}
	
}

bool FWidgetBlueprintEditorUtils::IsBindWidgetProperty(const FProperty* InProperty, bool& bIsOptional)
{
	if ( InProperty )
	{
		bool bIsBindWidget = InProperty->HasMetaData("BindWidget") || InProperty->HasMetaData("BindWidgetOptional");
		bIsOptional = InProperty->HasMetaData("BindWidgetOptional") || ( InProperty->HasMetaData("OptionalWidget") || InProperty->GetBoolMetaData("OptionalWidget") );

		return bIsBindWidget;
	}

	return false;
}
```