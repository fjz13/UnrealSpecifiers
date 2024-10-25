# SimpleDisplay

- **Function Description:** Directly visible in the Details Panel without being collapsed into the Advanced section.
- **Metadata Type:** bool
- **Engine Module:** DetailsPanel, Editor
- **Action Mechanism:** Include [CPF_SimpleDisplay](../../../../Flags/EPropertyFlags/CPF_SimpleDisplay.md) in PropertyFlags
- **Common Usage:** ★★★

Visible directly in the Details Panel without being collapsed into the Advanced section.

By default, it remains uncollapsed, but it can be used to override the AdvancedClassDisplay setting on the class. See the code and effects of AdvancedClassDisplay for specifics.

## Sample Code:

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyProperty_Test :public UObject
{
	//PropertyFlags:	CPF_Edit | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_SimpleDisplay | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
	UPROPERTY(EditAnywhere, SimpleDisplay, Category = Display)
		int32 MyInt_SimpleDisplay = 123;

	//PropertyFlags:	CPF_Edit | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_AdvancedDisplay | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = Display)
		int32 MyInt_AdvancedDisplay = 123;
}
```

## Example Effect:

![Untitled](Untitled.png)

## Principle:

If CPF_SimpleDisplay is present, then bAdvanced = false

```cpp
void FPropertyNode::InitNode(const FPropertyNodeInitParams& InitParams)
{
	// Property is advanced if it is marked advanced or the entire class is advanced and the property not marked as simple
	static const FName Name_AdvancedClassDisplay("AdvancedClassDisplay");
	bool bAdvanced = Property.IsValid() ? ( Property->HasAnyPropertyFlags(CPF_AdvancedDisplay) || ( !Property->HasAnyPropertyFlags( CPF_SimpleDisplay ) && Property->GetOwnerClass() && Property->GetOwnerClass()->GetBoolMetaData(Name_AdvancedClassDisplay) ) ) : false;

}
```