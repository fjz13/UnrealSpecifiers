# BlueprintGetter

- **Function Description:** Define a custom Get function for the attribute to read.

- **Metadata Type:** string="abc"
- **Engine Module:** Blueprint
- **Action Mechanism:** Include [CPF_BlueprintReadOnly](../../../../Flags/EPropertyFlags/CPF_BlueprintReadOnly.md) and [CPF_BlueprintVisible](../../../../Flags/EPropertyFlags/CPF_BlueprintVisible.md) in PropertyFlags, and add [BlueprintGetter](../../../../Meta/Blueprint/BlueprintGetter.md) in Meta
- **Common Usage:** ★★★

Define a custom Get function for the attribute to read.
If BlueprintSetter or BlueprintReadWrite is not set, BlueprintReadOnly will be set by default, making this property read-only.

## Example Code:

```cpp
public:
	//(BlueprintGetter = , Category = Blueprint, ModuleRelativePath = Property/MyProperty_Test.h)
	UFUNCTION(BlueprintGetter, Category = Blueprint)	//or BlueprintPure
		int32 MyInt_Getter()const { return MyInt_WithGetter * 2; }

	//(BlueprintSetter = , Category = Blueprint, ModuleRelativePath = Property/MyProperty_Test.h)
	UFUNCTION(BlueprintSetter, Category = Blueprint)	//or BlueprintCallable
		void MyInt_Setter(int NewValue) { MyInt_WithSetter = NewValue / 4; }
private:
	//(BlueprintGetter = MyInt_Getter, Category = Blueprint, ModuleRelativePath = Property/MyProperty_Test.h)
	//PropertyFlags:	CPF_BlueprintVisible | CPF_BlueprintReadOnly | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPrivate
	UPROPERTY(BlueprintGetter = MyInt_Getter, Category = Blueprint)
		int32 MyInt_WithGetter = 123;

	//(BlueprintSetter = MyInt_Setter, Category = Blueprint, ModuleRelativePath = Property/MyProperty_Test.h)
	//PropertyFlags:	CPF_BlueprintVisible | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPrivate
	UPROPERTY(BlueprintSetter = MyInt_Setter, Category = Blueprint)
		int32 MyInt_WithSetter = 123;
```

## Example Effect:

"MyInt_WithGetter" is read-only.

"MyInt_WithSetter" is readable and writable.

![Untitled](Untitled.png)