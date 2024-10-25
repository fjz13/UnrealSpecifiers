# EditAnywhere

- **Function description:** Editable in both the default value and the instance's detail panel
- **Metadata type:** bool
- **Engine module:** DetailsPanel, Editor
- **Action mechanism:** Include [CPF_Edit](../../../../Flags/EPropertyFlags/CPF_Edit.md) in PropertyFlags
- **Commonly used:** ★★★★★

Editable in both the default value and the instance's detail panel.

## Sample Code:

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyProperty_Test :public UObject
{
	public:
	//PropertyFlags:	CPF_Edit | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
	UPROPERTY(EditAnywhere, Category = Edit)
		int32 MyInt_EditAnywhere = 123;

	//PropertyFlags:	CPF_Edit | CPF_ZeroConstructor | CPF_DisableEditOnInstance | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
	UPROPERTY(EditDefaultsOnly, Category = Edit)
		int32 MyInt_EditDefaultsOnly = 123;

	//PropertyFlags:	CPF_Edit | CPF_ZeroConstructor | CPF_DisableEditOnTemplate | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
	UPROPERTY(EditInstanceOnly, Category = Edit)
		int32 MyInt_EditInstanceOnly = 123;

	//PropertyFlags:	CPF_Edit | CPF_ZeroConstructor | CPF_EditConst | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
	UPROPERTY(VisibleAnywhere, Category = Edit)
		int32 MyInt_VisibleAnywhere = 123;

	//PropertyFlags:	CPF_Edit | CPF_ZeroConstructor | CPF_DisableEditOnInstance | CPF_EditConst | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
	UPROPERTY(VisibleDefaultsOnly, Category = Edit)
		int32 MyInt_VisibleDefaultsOnly = 123;

	//PropertyFlags:	CPF_Edit | CPF_ZeroConstructor | CPF_DisableEditOnTemplate | CPF_EditConst | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
	UPROPERTY(VisibleInstanceOnly, Category = Edit)
		int32 MyInt_VisibleInstanceOnly = 123;
}
```

## Example Effect:

![Untitled](Untitled.png)

## Fundamental Principle:

CPF_Edit is extensively used in the source code, determining the visibility and editability of attributes in numerous locations. Those interested can search for the usage of CPF_Edit on their own.