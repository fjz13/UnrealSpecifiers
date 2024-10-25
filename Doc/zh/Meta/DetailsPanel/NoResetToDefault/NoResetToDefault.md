# NoResetToDefault

- **功能描述：** 禁用和隐藏属性在细节面板上的“重置”功能。
- **使用位置：** UPROPERTY
- **引擎模块：** DetailsPanel
- **元数据类型：** bool
- **常用程度：** ★★★

禁用和隐藏属性在细节面板上的“重置”功能。

## 测试代码：

```cpp
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category=ResetToDefaultTest)
	int32 MyInt_Default = 123;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category=ResetToDefaultTest, meta = (NoResetToDefault))
	int32 MyInt_NoResetToDefault = 123;
```

## 测试效果：

可以发现默认的属性在改变值后，右侧会出现一个重置按钮，以便让属性重置回默认值。NoResetToDefault的作用就是去除这个功能。

![ResetToDefaultTest](ResetToDefaultTest.gif)

## 原理：

编辑器里会判断这个meta，如果没有则创建SResetToDefaultPropertyEditor。

```cpp
bool SSingleProperty::GeneratePropertyCustomization()
{
		if (!PropertyEditor->GetPropertyHandle()->HasMetaData(TEXT("NoResetToDefault")) && !bShouldHideResetToDefault)
		{
			HorizontalBox->AddSlot()
			.Padding( 2.0f )
			.AutoWidth()
			.VAlign( VAlign_Center )
			[
				SNew( SResetToDefaultPropertyEditor,  PropertyEditor->GetPropertyHandle() )
			];
		}
}
```