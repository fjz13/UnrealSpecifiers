# OverridingInputProperty

- **Function description:** Specifies the other FExpressionInput properties that this float in UMaterialExpression is intended to override.
- **Use location:** UPROPERTY
- **Engine module:** Material
- **Metadata type:** bool
- **Restriction type:** UMaterialExpression::float
- **Related items:** [RequiredInput](../RequiredInput.md)
- **Frequency:** ★★★

Within UMaterialExpression, this float specifies the other FExpressionInput properties it is to override.

- In material expressions, there are properties for which we want to provide a default value when the user has not made a connection. In such cases, this float attribute's value can serve as the default.
- However, when the user does connect, this pin should function as a standard input, which necessitates another FExpressionInput property. Hence, the OverridingInputProperty is used to specify this alternate property.
- The FExpressionInput property designated by OverridingInputProperty typically has RequiredInput set to "false", as the usual logic dictates that if a default value is provided, the user is not required to input a value. Nonetheless, setting RequiredInput to "true" is also possible, reminding the user that an input is preferred, but a default value is available if none is provided.
- Many pins like BaseColor on the output node both require an input and offer a default value.

## Test Code:

In the Compile function, we mimic the source code to demonstrate how to properly handle this attribute to obtain a value. You may also refer to other examples in the source code for guidance.

```cpp
UCLASS()
class UMyProperty_MyMaterialExpression : public UMaterialExpression
{
	GENERATED_UCLASS_BODY()
public:
	UPROPERTY()
	FExpressionInput MyInput_Default;

	UPROPERTY(meta = (RequiredInput = "true"))
	FExpressionInput MyInput_Required;

	UPROPERTY(meta = (RequiredInput = "false"))
	FExpressionInput MyInput_NotRequired;
public:
	UPROPERTY(EditAnywhere, Category = OverridingInputProperty, meta = (RequiredInput = "false"))
	FExpressionInput MyAlpha;

	/** only used if MyAlpha is not hooked up */
	UPROPERTY(EditAnywhere, Category = OverridingInputProperty, meta = (OverridingInputProperty = "MyAlpha"))
	float ConstAlpha = 1.f;

	UPROPERTY(EditAnywhere, Category = OverridingInputProperty, meta = (RequiredInput = "true"))
	FExpressionInput MyAlpha2;

	/** only used if MyAlpha is not hooked up */
	UPROPERTY(EditAnywhere, Category = OverridingInputProperty, meta = (OverridingInputProperty = "MyAlpha2"))
	float ConstAlpha2 = 1.f;
public:

	//~ Begin UMaterialExpression Interface
#if WITH_EDITOR
	virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override
	{
		int32 IndexAlpha = MyAlpha.GetTracedInput().Expression ? MyAlpha.Compile(Compiler) : Compiler->Constant(ConstAlpha);
		return 0;
	}
	virtual void GetCaption(TArray<FString>& OutCaptions) const override;

	virtual bool GenerateHLSLExpression(FMaterialHLSLGenerator& Generator, UE::HLSLTree::FScope& Scope, int32 OutputIndex, UE::HLSLTree::FExpression const*& OutExpression) const override;
#endif
	//~ End UMaterialExpression Interface
};

```

## Test Results:

It is evident that both MyAlpha and MyAlpha2 have default values on their right sides, with one appearing gray and the other white due to their differing RequiredInput settings.

The other three MyInput pins are provided for comparison.

The various pins on the final output expression of the material on the right present different scenarios for your reference.

![Untitled](Untitled.png)

## Principle:

Actually, the principle involves altering the editability of the pin and the input field based on the Meta tag.

```cpp

bool UMaterialExpression::CanEditChange(const FProperty* InProperty) const
{
	bool bIsEditable = Super::CanEditChange(InProperty);
	if (bIsEditable && InProperty != nullptr)
	{
		// Automatically set property as non-editable if it has OverridingInputProperty metadata
		// pointing to an FExpressionInput property which is hooked up as an input.
		//
		// e.g. in the below snippet, meta=(OverridingInputProperty = "A") indicates that ConstA will
		// be overridden by an FExpressionInput property named 'A' if one is connected, and will thereby
		// be set as non-editable.
		//
		//	UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstA' if not specified"))
		//	FExpressionInput A;
		//
		//	UPROPERTY(EditAnywhere, Category = MaterialExpressionAdd, meta = (OverridingInputProperty = "A"))
		//	float ConstA;
		//

		static FName OverridingInputPropertyMetaData(TEXT("OverridingInputProperty"));

		if (InProperty->HasMetaData(OverridingInputPropertyMetaData))
		{
			const FString& OverridingPropertyName = InProperty->GetMetaData(OverridingInputPropertyMetaData);

			FStructProperty* StructProp = FindFProperty<FStructProperty>(GetClass(), *OverridingPropertyName);
			if (ensure(StructProp != nullptr))
			{
				static FName RequiredInputMetaData(TEXT("RequiredInput"));

				// Must be a single FExpressionInput member, not an array, and must be tagged with metadata RequiredInput="false"
				if (ensure(	StructProp->Struct->GetFName() == NAME_ExpressionInput &&
							StructProp->ArrayDim == 1 &&
							StructProp->HasMetaData(RequiredInputMetaData) &&
							!StructProp->GetBoolMetaData(RequiredInputMetaData)))
				{
					const FExpressionInput* Input = StructProp->ContainerPtrToValuePtr<FExpressionInput>(this);

					if (Input->Expression != nullptr && Input->GetTracedInput().Expression != nullptr)
					{
						bIsEditable = false;
					}
				}
			}
		}

		if (bIsEditable)
		{
			// If the property has EditCondition metadata, then whether it's editable depends on the other EditCondition property
			const FString EditConditionPropertyName = InProperty->GetMetaData(TEXT("EditCondition"));
			if (!EditConditionPropertyName.IsEmpty())
			{
				FBoolProperty* EditConditionProperty = FindFProperty<FBoolProperty>(GetClass(), *EditConditionPropertyName);
				{
					bIsEditable = *EditConditionProperty->ContainerPtrToValuePtr<bool>(this);
				}
			}
		}
	}

	return bIsEditable;
}

```