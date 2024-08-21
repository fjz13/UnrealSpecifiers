# DocumentationPolicy

- **功能描述：** 指定文档验证的规则，当前只能设为Strict
- **使用位置：** Any
- **引擎模块：** UHT
- **元数据类型：** string="abc"
- **常用程度：** ★

在UHT的ValidateDocumentationPolicy函数里，会发现这个值主要是用来判断类型或字段上是否有提供Comment或Tooltip，或者Float变量是否配了对应的“UIMin / UIMax”，以便提取出来这些信息生成对应的文档。

当前只有一个配置是Strict，里面默认是开启了所有的检查。所有可以理解为在C++源码里配置上DocumentationPolicy=Strict，就意味着想要引擎来检查文档配置。

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
//。。。
}
```

## 源码中的类似例子：

```cpp
USTRUCT(meta=(DisplayName="Set Transform", Category="Transforms", TemplateName = "Set Transform", DocumentationPolicy = "Strict", Keywords="SetBoneTransform,SetControlTransform,SetInitialTransform,SetSpaceTransform", NodeColor="0, 0.364706, 1.0", Varying))
struct CONTROLRIG_API FRigUnit_SetTransform : public FRigUnitMutable
{
}
```

## 自己的测试代码：

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
		int MyFunc_ValidateParamFailed(FString keyName,int keyValue){return 0;}//必须至少有一个@param才会开启参数注释的验证

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

## 产生的UHT编译报错：

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
