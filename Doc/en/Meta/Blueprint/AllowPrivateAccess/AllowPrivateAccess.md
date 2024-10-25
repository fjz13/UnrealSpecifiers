# AllowPrivateAccess

- **Function Description:** Allows a C++ private attribute to be accessible in Blueprints.
- **Usage Location:** UPROPERTY
- **Metadata Type:** bool
- **Associated Items:** [BlueprintProtected](../BlueprintProtected/BlueprintProtected.md)
- **Commonality:** ★★★★★

Allows a C++ private attribute to be accessible in Blueprints.

The purpose of AllowPrivateAccess is to permit the attribute to remain private in C++ and inaccessible to C++ subclasses, while still exposing it for access in Blueprints.

## Test Code:

```cpp
public:
	//CPF_BlueprintVisible | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
	UPROPERTY(BlueprintReadWrite)
	int32 MyNativeInt_NativePublic;
private:
	//CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPrivate
	//error : BlueprintReadWrite should not be used on private members
	UPROPERTY()
	int32 MyNativeInt_NativePrivate;

	//(AllowPrivateAccess = TRUE, Category = MyFunction_Access, ModuleRelativePath = Function/MyFunction_Access.h)
	//CPF_BlueprintVisible | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPrivate
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 MyNativeInt_NativePrivate_AllowPrivateAccess;
```

Attempting to add BlueprintReadWrite or BlueprintReadOnly to MyNativeInt_NativePrivate will trigger a UHT compilation error.

## Blueprint Effects:

By default, the access permissions for MyNativeInt_NativePrivate_AllowPrivateAccess in Blueprints are consistent with MyNativeInt_NativePublic.

If users wish to modify the access permissions of the property in Blueprints, they can combine it with BlueprintProtected and BlueprintPrivate.

![Untitled](Untitled.png)

## Principle:

When UHT identifies the BlueprintReadWrite or BlueprintReadOnly specifiers for an attribute, it simultaneously checks for the presence of AllowPrivateAccess. If it is absent, an error is triggered.

Therefore, the role of AllowPrivateAccess is actually to prevent UHT from reporting an error. Once this error check is bypassed, the BlueprintReadWrite or BlueprintReadOnly on the attribute will be recognized and take effect, enabling access within Blueprints.

```cpp
	private static void BlueprintReadWriteSpecifier(UhtSpecifierContext specifierContext)
	{
			bool allowPrivateAccess = context.MetaData.TryGetValue(UhtNames.AllowPrivateAccess, out string? privateAccessMD) && !privateAccessMD.Equals("false", StringComparison.OrdinalIgnoreCase);
			if (specifierContext.AccessSpecifier == UhtAccessSpecifier.Private && !allowPrivateAccess)
			{
				context.MessageSite.LogError("BlueprintReadWrite should not be used on private members");
			}
	}

	private static void BlueprintReadOnlySpecifier(UhtSpecifierContext specifierContext)
	{
			bool allowPrivateAccess = context.MetaData.TryGetValue(UhtNames.AllowPrivateAccess, out string? privateAccessMD) && !privateAccessMD.Equals("false", StringComparison.OrdinalIgnoreCase);
			if (specifierContext.AccessSpecifier == UhtAccessSpecifier.Private && !allowPrivateAccess)
			{
				context.MessageSite.LogError("BlueprintReadOnly should not be used on private members");
			}
	}

```