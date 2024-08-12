# ShowAsInputPin

Description: 使得UMaterialExpression里的一些基础类型属性变成材质节点上的引脚。
Usage: UPROPERTY
Feature: Blueprint
Group: Material
Type: bool
LimitedType: UMaterialExpression里的属性
Status: Done

使得UMaterialExpression里的一些基础类型属性变成材质节点上的引脚。

- 所谓基础类型，指的是float，FVector这种常用的类型。
- 默认这些基础类型属性是不显示为引脚的。
- ShowAsInputPin 值有两个选项，Primary可以直接显示出来，Advanced需要展开箭头后显示。

测试代码：

```cpp

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PinTest)
	float MyFloat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PinTest, meta = (ShowAsInputPin = "Primary"))
	float MyFloat_Primary;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PinTest, meta = (ShowAsInputPin = "Advanced"))
	float MyFloat_Advanced;
```

测试结果：

可见MyFloat没有显示在节点上。

MyFloat_Primary显示在节点上。

MyFloat_Advanced需要展开箭头后才显示出来。

![Untitled](ShowAsInputPin/Untitled.png)

原理：

遍历UMaterialExpression里的属性，根据含有ShowAsInputPin 的类型来生成引脚。

```cpp
TArray<FProperty*> UMaterialExpression::GetPropertyInputs() const
{
	TArray<FProperty*> PropertyInputs;

	static FName OverridingInputPropertyMetaData(TEXT("OverridingInputProperty"));
	static FName ShowAsInputPinMetaData(TEXT("ShowAsInputPin"));
	for (TFieldIterator<FProperty> InputIt(GetClass(), EFieldIteratorFlags::IncludeSuper, EFieldIteratorFlags::ExcludeDeprecated); InputIt; ++InputIt)
	{
		bool bCreateInput = false;
		FProperty* Property = *InputIt;
		// Don't create an expression input if the property is already associated with one explicitly declared
		bool bOverridingInputProperty = Property->HasMetaData(OverridingInputPropertyMetaData);
		// It needs to have the 'EditAnywhere' specifier
		const bool bEditAnywhere = Property->HasAnyPropertyFlags(CPF_Edit);
		// It needs to be marked with a valid pin category meta data
		const FString ShowAsInputPin = Property->GetMetaData(ShowAsInputPinMetaData);
		const bool bShowAsInputPin = ShowAsInputPin == TEXT("Primary") || ShowAsInputPin == TEXT("Advanced");

		if (!bOverridingInputProperty && bEditAnywhere && bShowAsInputPin)
		{
			// Check if the property type fits within the allowed widget types
			FFieldClass* PropertyClass = Property->GetClass();
			if (PropertyClass == FFloatProperty::StaticClass()
				|| PropertyClass == FDoubleProperty::StaticClass()
				|| PropertyClass == FIntProperty::StaticClass()
				|| PropertyClass == FUInt32Property::StaticClass()
				|| PropertyClass == FByteProperty::StaticClass()
				|| PropertyClass == FBoolProperty::StaticClass()
				)
			{
				bCreateInput = true;
			}
			else if (PropertyClass == FStructProperty::StaticClass())
			{
				FStructProperty* StructProperty = CastField<FStructProperty>(Property);
				UScriptStruct* Struct = StructProperty->Struct;
				if (Struct == TBaseStructure<FLinearColor>::Get()
					|| Struct == TBaseStructure<FVector4>::Get()
					|| Struct == TVariantStructure<FVector4d>::Get()
					|| Struct == TBaseStructure<FVector>::Get()
					|| Struct == TVariantStructure<FVector3f>::Get()
					|| Struct == TBaseStructure<FVector2D>::Get()
					)
				{
					bCreateInput = true;
				}
			}
		}
		if (bCreateInput)
		{
			PropertyInputs.Add(Property);
		}
	}

	return PropertyInputs;
}
```