# Setter

Description: 为属性增加一个C++的Set函数，只在C++层面应用。
Type: string="abc"
Feature: Blueprint
Example: Setter=SetterFunctionName
EPropertyFlagsOperation: |=
Status: Done

为属性增加一个C++的Set函数，只在C++层面应用。

- Getter上如不提供函数名，那就用默认的SetXXX的名字。也可以提供另外一个函数名。
- 这些Getter函数是不加UFUNCTION的，这点要和BlueprintGetter区分。
- 感觉更好的名字是NativeSetter。
- SetXXX的函数必须自己手写，否则UHT会报错。
- 我们当然也可以自己写GetSet函数，不需要写Getter和Setter的元数据。但写上Getter和Settter的好处是，万一在项目里别的地方，用到了反射来获取和设置值，这个时候如果没有标上Getter和Setter，就会直接从属性上获取值，从而跳过我们想要的自定义Get/Set流程。

测试代码：

```cpp
public:
	UPROPERTY(BlueprintReadWrite, Setter)
	float MyFloat = 1.0f;

	UPROPERTY(BlueprintReadWrite, Setter = SetMyCustomFloat)
	float MyFloat2 = 1.0f;
public:
	void SetMyFloat(float val) { MyFloat = val + 100.f; }
	void SetMyCustomFloat(float val) { MyFloat2 = val + 100.f; }

public:
	UFUNCTION(BlueprintCallable)
	void RunTest();
};

void UMyProperty_Set::RunTest()
{
	float OldValue=MyFloat;

	FProperty* prop=GetClass()->FindPropertyByName(TEXT("MyFloat"));
	const float Value2=20.f;

	prop->SetValue_InContainer(this,&Value2);

	float NewValue=MyFloat;
}
```

蓝图表现：

在测试的时候，可见如果是用SetValue_InContainer这种反射的方式来获取值，就会自动的调用到SetMyFloat，从而实际上设置到不同的值。

![Untitled](Setter/Untitled.png)

![Untitled](Setter/Untitled%201.png)

原理：

UHT在分析Setter标记后，会在gen.cpp里生成相应的函数包装。在构建FProperty的时候，就会创建TPropertyWithSetterAndGetter，之后在GetSingleValue_InContainer的时候就会调用到CallGetter。

```cpp
void UMyProperty_Set::SetMyFloat_WrapperImpl(void* Object, const void* InValue)
{
	UMyProperty_Set* Obj = (UMyProperty_Set*)Object;
	float& Value = *(float*)InValue;
	Obj->SetMyFloat(Value);
}

const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UMyProperty_Set_Statics::NewProp_MyFloat = { "MyFloat", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, &UMyProperty_Set::SetMyFloat_WrapperImpl, nullptr, 1, STRUCT_OFFSET(UMyProperty_Set, MyFloat), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MyFloat_MetaData), NewProp_MyFloat_MetaData) };

template <typename PropertyType, typename PropertyParamsType>
PropertyType* NewFProperty(FFieldVariant Outer, const FPropertyParamsBase& PropBase)
{
	const PropertyParamsType& Prop = (const PropertyParamsType&)PropBase;
	PropertyType* NewProp = nullptr;

	if (Prop.SetterFunc || Prop.GetterFunc)
	{
		NewProp = new TPropertyWithSetterAndGetter<PropertyType>(Outer, Prop);
	}
	else
	{
		NewProp = new PropertyType(Outer, Prop);
	}
}

void FProperty::SetSingleValue_InContainer(void* OutContainer, const void* InValue, int32 ArrayIndex) const
{
	checkf(ArrayIndex <= ArrayDim, TEXT("ArrayIndex (%d) must be less than the property %s array size (%d)"), ArrayIndex, *GetFullName(), ArrayDim);
	if (!HasSetter())
	{
		// Fast path - direct memory access
		CopySingleValue(ContainerVoidPtrToValuePtrInternal((void*)OutContainer, ArrayIndex), InValue);
	}
	else
	{
		if (ArrayDim == 1)
		{
			// Slower but no mallocs. We can copy the value directly to the resulting param
			CallSetter(OutContainer, InValue);
		}
		else
		{
			// Malloc a temp value that is the size of the array. We will then copy the entire array to the temp value
			uint8* ValueArray = (uint8*)AllocateAndInitializeValue();
			GetValue_InContainer(OutContainer, ValueArray);
			// Replace the value at the specified index in the temp array with the InValue
			CopySingleValue(ValueArray + ArrayIndex * ElementSize, InValue);
			// Now call a setter to replace the entire array and then destroy the temp value
			CallSetter(OutContainer, ValueArray);
			DestroyAndFreeValue(ValueArray);
		}
	}
}
```