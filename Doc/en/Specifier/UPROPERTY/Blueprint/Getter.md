# Getter

- **Function Description:** Add a C++ Get function to the attribute, applicable only at the C++ level.

- **Metadata Type:** string = "abc"
- **Engine Module:** Blueprint
- **Commonality:** ★★★

Add a C++ Get function to the attribute, applicable only at the C++ level.

- Should a function name not be specified for the Getter, the default name of GetXXX will be used. Alternatively, a different function name can be provided.
- These Getter functions do not include the UFUNCTION decorator, which should be distinguished from BlueprintGetter.
- "NativeGetter" might be a more appropriate name.
- The GetXXX function must be manually implemented; otherwise, UHT will generate an error.
- Of course, we can also manually write GetSet functions without specifying Getter and Setter metadata. However, the benefit of including Getters and Setters is that if reflection is used to access and modify values elsewhere in the project, and if Getters and Setters are not marked, the values will be accessed directly from the properties, bypassing the custom Get/Set process we intend to implement.

## Test Code:

```cpp
public:
	//GetterFunc:	Has Native Getter
	UPROPERTY(BlueprintReadWrite, Getter)
	float MyFloat = 1.0f;

	//GetterFunc:	Has Native Getter
	UPROPERTY(BlueprintReadWrite, Getter = GetMyCustomFloat)
	float MyFloat2 = 1.0f;
public:
	float GetMyFloat()const { return MyFloat + 100.f; }

	float GetMyCustomFloat()const { return MyFloat2 + 100.f; }

void UMyProperty_Get::RunTest()
{
	float Value1=MyFloat;

	FProperty* prop=GetClass()->FindPropertyByName(TEXT("MyFloat"));
	float Value2=0.f;

	prop->GetValue_InContainer(this,&Value2);
}
```

## Blueprint Performance:

During testing, it is evident that if the GetValue_InContainer reflection method is used to retrieve the value, it will automatically invoke GetMyFloat, resulting in different values being returned.

Directly calling Get MyFloat in the blueprint still results in 1.

![Untitled](Setter/Untitled.png)

## Principle:

UHT, after analyzing the Getter marker, generates the corresponding function wrapper in gen.cpp. During the construction of FProperty, TPropertyWithSetterAndGetter is created, and CallGetter is invoked when GetSingleValue_InContainer is called.

```cpp
void UMyProperty_Get::GetMyFloat_WrapperImpl(const void* Object, void* OutValue)
{
	const UMyProperty_Get* Obj = (const UMyProperty_Get*)Object;
	float& Result = *(float*)OutValue;
	Result = (float)Obj->GetMyFloat();
}

const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UMyProperty_Get_Statics::NewProp_MyFloat = { "MyFloat", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, &UMyProperty_Get::GetMyFloat_WrapperImpl, 1, STRUCT_OFFSET(UMyProperty_Get, MyFloat), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MyFloat_MetaData), NewProp_MyFloat_MetaData) };

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

void FProperty::GetSingleValue_InContainer(const void* InContainer, void* OutValue, int32 ArrayIndex) const
{
	checkf(ArrayIndex <= ArrayDim, TEXT("ArrayIndex (%d) must be less than the property %s array size (%d)"), ArrayIndex, *GetFullName(), ArrayDim);
	if (!HasGetter())
	{
		// Fast path - direct memory access
		CopySingleValue(OutValue, ContainerVoidPtrToValuePtrInternal((void*)InContainer, ArrayIndex));
	}
	else
	{
		if (ArrayDim == 1)
		{
			// Slower but no mallocs. We can copy the value directly to the resulting param
			CallGetter(InContainer, OutValue);
		}
		else
		{
			// Malloc a temp value that is the size of the array. Getter will then copy the entire array to the temp value
			uint8* ValueArray = (uint8*)AllocateAndInitializeValue();
			GetValue_InContainer(InContainer, ValueArray);
			// Copy the item we care about and free the temp array
			CopySingleValue(OutValue, ValueArray + ArrayIndex * ElementSize);
			DestroyAndFreeValue(ValueArray);
		}
	}
}

```