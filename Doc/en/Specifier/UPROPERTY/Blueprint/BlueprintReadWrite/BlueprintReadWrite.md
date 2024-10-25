# BlueprintReadWrite

- **Functional Description:** This property can be read from or written to within a Blueprint.

- **Metadata type:** boolean
- **Engine module:** Blueprint
- **Action mechanism:** Include [CPF_BlueprintVisible](../../../../Flags/EPropertyFlags/CPF_BlueprintVisible.md) in the PropertyFlags
- **Commonly used:** ★★★★★

This property can be read from or written to within a Blueprint.

This specifier is not compatible with the BlueprintReadOnly specifier.

## Sample Code:

```cpp
public:
	//PropertyFlags:	CPF_BlueprintVisible | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
	UPROPERTY(BlueprintReadWrite, Category = Blueprint)
		int32 MyInt_ReadWrite = 123;
	//PropertyFlags:	CPF_BlueprintVisible | CPF_BlueprintReadOnly | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
	UPROPERTY(BlueprintReadOnly, Category = Blueprint)
		int32 MyInt_ReadOnly = 123;
```

## Example Effect:

Readable and writable in Blueprints:

![Untitled](Untitled.png)

## Fundamental Principle:

If CPF_Edit or | CPF_BlueprintVisible | CPF_BlueprintAssignable is present, the property can be retrieved.

```cpp
EPropertyAccessResultFlags PropertyAccessUtil::CanGetPropertyValue(const FProperty* InProp)
{
	if (!InProp->HasAnyPropertyFlags(CPF_Edit | CPF_BlueprintVisible | CPF_BlueprintAssignable))
	{
		return EPropertyAccessResultFlags::PermissionDenied | EPropertyAccessResultFlags::AccessProtected;
	}

	return EPropertyAccessResultFlags::Success;
}

```