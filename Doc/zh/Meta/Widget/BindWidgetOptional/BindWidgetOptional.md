# BindWidgetOptional

- **功能描述：** 指定在C++类中该Widget属性可以绑定到UMG的某个同名控件，也可以不绑定。
- **使用位置：** UPROPERTY
- **引擎模块：** Widget Property
- **元数据类型：** bool
- **限制类型：** UWidget子类里属性
- **关联项：** [BindWidget](../BindWidget/BindWidget.md)
- **常用程度：** ★★★

指定在C++类中该Widget属性可以绑定到UMG的某个同名控件，也可以不绑定。

大致作用和BindWidget一样，区别是：

- BindWidgetOptional顾名思义是可选的，意思是UMG里即使不定义该控件在编译的时候也不会报错。编译会通过，但是会提示警告缺少控件。
-
- 和不加BindWidgetOptional的控件同名属性的区别是，前者在UMG里定义同名控件的时候不会报错，但后者是会提示同名冲突报错。

BindWidgetOptional的写法有两种：
BindWidgetOptional可以看作是BindWidget和OptionalWidget的合并版。

```cpp
UCLASS(BlueprintType)
class INSIDER_API UMyProperty_BindWidget :public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTextBlock* MyTextBlock_SameName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetOptional))
	class UTextBlock* MyTextBlock_Optional1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, OptionalWidget))
	class UTextBlock* MyTextBlock_Optional2;
};
```

## 测试效果：

![Untitled](Untitled.png)

## 原理：

```cpp

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