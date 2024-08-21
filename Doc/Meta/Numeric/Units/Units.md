# Units

- **功能描述：** 设定属性值的单位，支持实时根据数值不同动态改变显示的单位。
- **使用位置：** UPROPERTY
- **引擎模块：** Numeric Property
- **元数据类型：** string="abc"
- **限制类型：** float,int32
- **关联项：** [ForceUnits](../ForceUnits.md)
- **常用程度：** ★★★

设定属性值的单位。一个单位有多个别名，如Kilograms和kg，Centimeters和cm，都是可以的。

Units的作用不光是设定单位，而且隐含着这个显示的单位字符串可以根据用户输入的数值自动的进行调整适应。比如100cm其实就是1m，0.5km就是500m。

另外设定了单位之后，还可以接受用户直接在数字框中输入数字和单位的组合，比如直接敲入1km就可以设置值为1，单位为km。或者1ft为1英尺=30.84cm。

要实现自动的调整显示单位的功能，首先需要在项目设置里设置单位系列。比如下图就在距离上设置了厘米，米，千米，毫米的单位（顺序不重要）。然后之后数字框显示距离的单位时就可以在这4者之间转换。

![Untitled](Untitled.png)

## 测试代码：

```cpp
UPROPERTY(EditAnywhere, Category = UnitsTest)
float MyFloat_NoUnits = 0.0;

UPROPERTY(EditAnywhere, Category = UnitsTest, Meta = (Units = "cm"))
float MyFloat_HasUnits_Distance = 100.f;

UPROPERTY(EditAnywhere, Category = UnitsTest, Meta = (ForceUnits = "cm"))
float MyFloat_HasForceUnits_Distance = 100.f;
```

## 测试效果：

- 在项目设置里填入4个单位：cm，m，km，mm后开始测试。
- 发现采用Units的属性，会自动的根据值的不同调整单位。而且也接受数字+单位的输入。
- 发现采用ForceUnits的属性，也可以接受数字+单位的输入，但是在显示上却始终显示为cm，不会调整到别的单位。

![Unit.gif](Unit.gif)

## 原理：

- 如果ForcedUnits有设置，则会同时设置UnderlyingUnits（基础单位），UserDisplayUnits 和FixedDisplayUnits 。
- 否则如果设置Units，则会只设置到UnderlyingUnits和FixedDisplayUnits
- 最后在显示单位的时候，如果有UserDisplayUnits，则优先采用。之后才是FixedDisplayUnits 。
- ToString的时候，是把UnderlyingUnits转到UserDisplayUnits或FixedDisplayUnits。
- 在数字输入框改变的时候，会触发SetupFixedDisplay，从而在内部每次重新计算合适的单位赋值到FixedDisplayUnits。因此如上面说的，如果没有设置UserDisplayUnits（没有ForceUnits），则每次都会调整到新的合适显示单位。否则就会因为UserDisplayUnits优先级最高且一直有值，导致总是以UserDisplayUnits显示保持不变。

```cpp
void SPropertyEditorNumeric<NumericType>::Construct( const FArguments& InArgs, const TSharedRef<FPropertyEditor>& InPropertyEditor )
{
		// First off, check for ForceUnits= meta data. This meta tag tells us to interpret, and always display the value in these units. FUnitConversion::Settings().ShouldDisplayUnits does not apply to such properties
		const FString& ForcedUnits = MetaDataGetter.Execute("ForceUnits");
		TOptional<EUnit> PropertyUnits = FUnitConversion::UnitFromString(*ForcedUnits);
		if (PropertyUnits.IsSet())
		{
			// Create the type interface and set up the default input units if they are compatible
			TypeInterface = MakeShareable(new TNumericUnitTypeInterface<NumericType>(PropertyUnits.GetValue()));
			TypeInterface->UserDisplayUnits = TypeInterface->FixedDisplayUnits = PropertyUnits.GetValue();
		}
		// If that's not set, we fall back to Units=xxx which calculates the most appropriate unit to display in
		else
		{
			if (FUnitConversion::Settings().ShouldDisplayUnits())
			{
				const FString& DynamicUnits = PropertyHandle->GetMetaData(TEXT("Units"));
				if (!DynamicUnits.IsEmpty())
				{
					PropertyUnits = FUnitConversion::UnitFromString(*DynamicUnits);
				}
				else
				{
					PropertyUnits = FUnitConversion::UnitFromString(*MetaDataGetter.Execute("Units"));
				}
			}
		
			if (!PropertyUnits.IsSet())
			{
				PropertyUnits = EUnit::Unspecified;
			}
		}
}

void SPropertyEditorNumeric<NumericType>::OnValueCommitted( NumericType NewValue, ETextCommit::Type CommitInfo )
{

			if (TypeInterface.IsValid())
			{
				TypeInterface->SetupFixedDisplay(NewValue);
			}
}

template<typename NumericType>
void TNumericUnitTypeInterface<NumericType>::SetupFixedDisplay(const NumericType& InValue)
{
	// We calculate this regardless of whether FixedDisplayUnits is used, so that the moment it is used, it's correct
	EUnit DisplayUnit = FUnitConversion::CalculateDisplayUnit(InValue, UnderlyingUnits);
	if (DisplayUnit != EUnit::Unspecified)
	{
		FixedDisplayUnits = DisplayUnit;
	}
}

//在转换的时候
FString TNumericUnitTypeInterface<NumericType>::ToString(const NumericType& Value) const
{
		if (UserDisplayUnits.IsSet())
		{
			auto Converted = FinalValue.ConvertTo(UserDisplayUnits.GetValue());
			if (Converted.IsSet())
			{
				return ToUnitString(Converted.GetValue());
			}
		}
		
		if (FixedDisplayUnits.IsSet())
		{
			auto Converted = FinalValue.ConvertTo(FixedDisplayUnits.GetValue());
			if (Converted.IsSet())
			{
				return ToUnitString(Converted.GetValue());
			}
		}
}
	

```
