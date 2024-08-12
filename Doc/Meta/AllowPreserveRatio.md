# AllowPreserveRatio

Description: 在细节面板上为FVector属性添加一个比率锁。
Usage: UPROPERTY
Feature: Editor
Group: Numeric Property
Type: bool
LimitedType: FVector
Status: Done

在细节面板上为FVector属性添加一个比率锁。

测试代码：

```cpp
public:
	UPROPERTY(EditAnywhere, Category = VectorTest)
	FVector MyVector_Default;

	UPROPERTY(EditAnywhere, Category = VectorTest, meta = (AllowPreserveRatio))
	FVector MyVector_AllowPreserveRatio;

	UPROPERTY(EditAnywhere, Category = VectorTest, meta = (ShowNormalize))
	FVector MyVector_ShowNormalize;
```

测试结果：

可见MyVector_AllowPreserveRatio的值在锁上之后可以形成固定的比率。

![AllowPreserveRatio.gif](AllowPreserveRatio/AllowPreserveRatio.gif)

原理：

其实就是UI定制化的时候检测出AllowPreserveRatio就创建单独的UI。

```cpp
void FMathStructCustomization::MakeHeaderRow(TSharedRef<class IPropertyHandle>& StructPropertyHandle, FDetailWidgetRow& Row)
{
		if (StructPropertyHandle->HasMetaData("AllowPreserveRatio"))
		{
			if (!GConfig->GetBool(TEXT("SelectionDetails"), *(StructPropertyHandle->GetProperty()->GetName() + TEXT("_PreserveScaleRatio")), bPreserveScaleRatio, GEditorPerProjectIni))
			{
				bPreserveScaleRatio = true;
			}
		
			HorizontalBox->AddSlot()
			.AutoWidth()
			.MaxWidth(18.0f)
			.VAlign(VAlign_Center)
			[
				// Add a checkbox to toggle between preserving the ratio of x,y,z components of scale when a value is entered
				SNew(SCheckBox)
				.IsChecked(this, &FMathStructCustomization::IsPreserveScaleRatioChecked)
				.OnCheckStateChanged(this, &FMathStructCustomization::OnPreserveScaleRatioToggled, StructWeakHandlePtr)
				.Style(FAppStyle::Get(), "TransparentCheckBox")
				.ToolTipText(LOCTEXT("PreserveScaleToolTip", "When locked, scales uniformly based on the current xyz scale values so the object maintains its shape in each direction when scaled"))
				[
					SNew(SImage)
					.Image(this, &FMathStructCustomization::GetPreserveScaleRatioImage)
					.ColorAndOpacity(FSlateColor::UseForeground())
				]
			];
		}

}
```