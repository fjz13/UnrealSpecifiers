# DocumentationPolicy

- **Function Description:** Specifies the rules for document validation, which can currently only be set to Strict
- **Usage Location:** Anywhere
- **Engine Module:** UHT
- **Metadata Type:** string="abc"
- **Commonality:** ★

Within the ValidateDocumentationPolicy function of UHT, this value primarily determines if a Comment or Tooltip is provided for a type or field, or if a Float variable has corresponding "UIMin / UIMax" settings. This information is then extracted to generate the corresponding documentation.

Currently, the only available configuration is Strict, which enables all checks by default.  Therefore, configuring DocumentationPolicy=Strict in the C++ source code implies a desire for the engine to enforce documentation standards.

```cpp
_documentationPolicies["Strict"] = new()
{
	ClassOrStructCommentRequired = true,
	FunctionToolTipsRequired = true,
	MemberToolTipsRequired = true,
	ParameterToolTipsRequired = true,
	FloatRangesRequired = true,
};

protected override void ValidateDocumentationPolicy(UhtDocumentationPolicy policy)
	{
		if (policy.ClassOrStructCommentRequired)
		{
			string classTooltip = MetaData.GetValueOrDefault(UhtNames.ToolTip);
			if (classTooltip.Length == 0 || classTooltip.Equals(EngineName, StringComparison.OrdinalIgnoreCase))
			{
				this.LogError($"{EngineType.CapitalizedText()} '{SourceName}' does not provide a tooltip / comment (DocumentationPolicy).");
			}
		}
//...
}
```

## Similar examples can be found in the source code:

```cpp
USTRUCT(meta=(DisplayName="Set Transform", Category="Transforms", TemplateName = "Set Transform", DocumentationPolicy = "Strict", Keywords="SetBoneTransform,SetControlTransform,SetInitialTransform,SetSpaceTransform", NodeColor="0, 0.364706, 1.0", Varying))
struct CONTROLRIG_API FRigUnit_SetTransform : public FRigUnitMutable
{
}
```

## My own test code:

```cpp
UCLASS(BlueprintType, meta = (DocumentationPolicy=Strict))
class INSIDER_API UMyClass_DocumentationPolicy :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MyFloat;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString MyString;

	//This is a float
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (UIMin = "0.0", UIMax = "100.0"))
	float MyFloat_WithValidate;


	UFUNCTION(meta = (DocumentationPolicy=Strict))
	void MyFunc(){}

	/**
	 *	Test Func for validate param
	 * 	@param keyOtherName The name of Key
	 *	@param keyValue
	 */
	UFUNCTION(BlueprintCallable, meta = (DocumentationPolicy=Strict))
		int MyFunc_ValidateParamFailed(FString keyName,int keyValue){return 0;}//Parameter annotation verification is only activated when there is at least one "@param" tag

	/**
	 *	Test Func for validate param
	 *
	 *	@param keyName The name of key
	 *	@param keyValue The value of key
	 *	@return Return operation result
	 */
	UFUNCTION(meta = (DocumentationPolicy=Strict))
	int MyFunc_ValidateParam(FString keyName,int keyValue){return 0;}
};

USTRUCT(BlueprintType, meta = (DocumentationPolicy=Strict))
struct INSIDER_API FMyStruct_DocumentationPolicy
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MyFloat;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString MyString;
};

UENUM(BlueprintType, meta = (DocumentationPolicy=Strict))
enum class EMyEnum_DocumentationPolicy :uint8
{
	First,
	Second,
	Third,
};

// This a tooltip / comment
UCLASS(BlueprintType, meta = (DocumentationPolicy = Strict))
class INSIDER_API UMyClass_DocumentationPolicy_TypeA :public UObject
{
	GENERATED_BODY()
};

/**
*	This a tooltip / comment
*
*/
UCLASS(BlueprintType, meta = (DocumentationPolicy = Strict))
class INSIDER_API UMyClass_DocumentationPolicy_TypeB :public UObject
{
	GENERATED_BODY()
};

UCLASS(BlueprintType, meta = (DocumentationPolicy = Strict,ToolTip="This a tooltip"))	//Cannot use ShortToolTip
class INSIDER_API UMyClass_DocumentationPolicy_TypeC :public UObject
{
	GENERATED_BODY()
};
```

## The resulting UHT compilation error:

```cpp
error : Class 'UMyClass_DocumentationPolicy' does not provide a tooltip / comment(DocumentationPolicy).
error : Property 'UMyClass_DocumentationPolicy::MyFloat' does not provide a tooltip / comment(DocumentationPolicy).
error : Property 'UMyClass_DocumentationPolicy::MyString' does not provide a tooltip / comment(DocumentationPolicy).
error : Property 'UMyClass_DocumentationPolicy::MyFloat' does not provide a valid UIMin / UIMax(DocumentationPolicy).
error : Function 'UMyClass_DocumentationPolicy::MyFunc' does not provide a tooltip / comment(DocumentationPolicy).
error : Function 'UMyClass_DocumentationPolicy::MyFunc' does not provide a comment(DocumentationPolicy).
error : Function 'UMyClass_DocumentationPolicy::MyFunc_ValidateParamFailed' doesn't provide a tooltip for parameter 'keyName' (DocumentationPolicy).
error : Function 'UMyClass_DocumentationPolicy::MyFunc_ValidateParamFailed' doesn't provide a tooltip for parameter 'keyValue' (DocumentationPolicy).
error : Function 'UMyClass_DocumentationPolicy::MyFunc_ValidateParamFailed' provides a tooltip for an unknown parameter 'keyOtherName'
error : Struct 'FMyStruct_DocumentationPolicy' does not provide a tooltip / comment(DocumentationPolicy).
error : Property 'FMyStruct_DocumentationPolicy::MyFloat' does not provide a tooltip / comment(DocumentationPolicy).
error : Property 'FMyStruct_DocumentationPolicy::MyString' does not provide a tooltip / comment(DocumentationPolicy).
error : Property 'FMyStruct_DocumentationPolicy::MyFloat' does not provide a valid UIMin / UIMax(DocumentationPolicy).
error : Enum 'EMyEnum_DocumentationPolicy' does not provide a tooltip / comment(DocumentationPolicy)
error : Enum entry 'EMyEnum_DocumentationPolicy::EMyEnum_DocumentationPolicy::First' does not provide a tooltip / comment(DocumentationPolicy)
error : Enum entry 'EMyEnum_DocumentationPolicy::EMyEnum_DocumentationPolicy::Second' does not provide a tooltip / comment(DocumentationPolicy)
error: Enum entry 'EMyEnum_DocumentationPolicy::EMyEnum_DocumentationPolicy::Third' does not provide a tooltip / comment(DocumentationPolicy)
```