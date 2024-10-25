# Setter

- **Function Description:** Adds a C++ Set function to the attribute, applicable solely at the C++ level.
- **Metadata Type:** string="abc"
- **Engine Module:** Blueprint
- **Associated Items:** [Getter](../Getter.md)
- **Usage Frequency:** ★★★

Adds a C++ Set function to the attribute, applicable solely at the C++ level.

- If no function name is provided for the Getter, the default name SetXXX will be used. Alternatively, a different function name can be specified.
- These Getter functions are not marked with UFUNCTION, differing from BlueprintGetters.
- A more fitting name might be NativeSetter.
- The SetXXX function must be manually written; otherwise, UHT will generate an error.
- We can also manually write GetSet functions without specifying Getter and Setter metadata. The benefit of explicitly defining Getters and Setters is that if reflection is used elsewhere in the project to access or modify values, the absence of these markings would result in direct property access, bypassing the custom Get/Set logic we intend to use.

## Test Code:

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

## Blueprint Behavior:

During testing, it is observed that using the reflection method SetValue_InContainer to set a value automatically invokes SetMyFloat, effectively setting a different value.

![Untitled](Untitled.png)

![Untitled](Untitled%201.png)

## Principle:

Upon analyzing Setter annotations, UHT generates the corresponding function wrappers in gen.cpp. When constructing FProperty, TPropertyWithSetterAndGetter is created, and during GetSingleValue_InContainer, CallGetter is invoked.

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