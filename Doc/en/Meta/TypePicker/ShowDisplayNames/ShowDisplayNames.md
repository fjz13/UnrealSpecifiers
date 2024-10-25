# ShowDisplayNames

- **Function Description:** Specifies that for Class and Struct properties, an alternative display name should be shown in the class selector instead of the class's original name.
- **Usage Location:** UPROPERTY
- **Engine Module:** TypePicker
- **Metadata Type:** bool
- **Restricted Types:** TSubClassOf, FSoftClassPath, UClass*, UScriptStruct*
- **Commonality:** ★

For Class and Struct properties, specifies that an alternative display name should be shown in the class selector rather than the class's original name.

The class display name refers to the name assigned to the DisplayName on UCLASS or UStruct, which is typically more user-friendly. The original class name is the class's type name.

## Test Code:

```cpp
UCLASS(BlueprintType, NotBlueprintable,DisplayName="This is MyCommonObjectChild")
class INSIDER_API UMyCommonObjectChild_HasDisplayName :public UMyCommonObject
{
	GENERATED_BODY()
public:
};

USTRUCT(BlueprintType,DisplayName="This is MyCommonStructChild")
struct INSIDER_API FMyCommonStructChild_HasDisplayName:public FMyCommonStruct
{
	GENERATED_BODY()
};

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShowDisplayNamesTest|TSubclassOf", meta = ())
TSubclassOf<UMyCommonObjectChild_HasDisplayName> MyClass_NotShowDisplayNames;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShowDisplayNamesTest|TSubclassOf", meta = (ShowDisplayNames))
TSubclassOf<UMyCommonObjectChild_HasDisplayName> MyClass_ShowDisplayNames;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShowDisplayNamesTest|UClass*", meta = (AllowedClasses = "MyCommonObjectChild_HasDisplayName"))
UClass* MyClassPtr_NotShowDisplayNames;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShowDisplayNamesTest|UClass*", meta = (AllowedClasses = "MyCommonObjectChild_HasDisplayName", ShowDisplayNames))
UClass* MyClassPtr_ShowDisplayNames;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShowDisplayNamesTest|FSoftClassPath", meta = (MetaClass = "MyCommonObjectChild_HasDisplayName"))
FSoftClassPath MySoftClass_NotShowDisplayNames;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShowDisplayNamesTest|FSoftClassPath", meta = (MetaClass = "MyCommonObjectChild_HasDisplayName", ShowDisplayNames))
FSoftClassPath MySoftClass_ShowDisplayNames;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShowDisplayNamesTest|UScriptStruct*", meta = (MetaStruct = "MyCommonStructChild_HasDisplayName"))
UScriptStruct* MyStructPtr_NotShowDisplayNames;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShowDisplayNamesTest|UScriptStruct*", meta = (MetaStruct = "MyCommonStructChild_HasDisplayName", ShowDisplayNames))
UScriptStruct* MyStructPtr_ShowDisplayNames;
```

## Test Results:

It is evident that with ShowDisplayNames added, the name displayed in the list is a more friendly "This is XXX," rather than the direct class name.

To make the effect more intuitive, the test code also includes MetaClass, MetaStruct, and AllowedClasses to restrict the selection range.

![ShowDisplayNames](ShowDisplayNames.jpg)

## Principle:

In the source code, it is apparent that if bShowDisplayNames is enabled, the display will be (Class, Struct) → GetDisplayNameText instead of (Class, Struct) → GetName.

Because FInstancedStructDetails does not utilize this Meta, the option is not supported.

```cpp
void FSoftClassPathCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	const bool bShowDisplayNames = PropertyHandle->HasMetaData("ShowDisplayNames");
	SNew(SClassPropertyEntryBox)
	.ShowDisplayNames(bShowDisplayNames)
}

void SPropertyEditorClass::Construct(const FArguments& InArgs, const TSharedPtr< FPropertyEditor >& InPropertyEditor)
{
		bShowViewOptions = Property->GetOwnerProperty()->HasMetaData(TEXT("HideViewOptions")) ? false : true;
		bShowTree = Property->GetOwnerProperty()->HasMetaData(TEXT("ShowTreeView"));
		bShowDisplayNames = Property->GetOwnerProperty()->HasMetaData(TEXT("ShowDisplayNames"));
}
void SPropertyEditorStruct::Construct(const FArguments& InArgs, const TSharedPtr< class FPropertyEditor >& InPropertyEditor)
{
		bShowViewOptions = Property->GetOwnerProperty()->HasMetaData(TEXT("HideViewOptions")) ? false : true;
		bShowTree = Property->GetOwnerProperty()->HasMetaData(TEXT("ShowTreeView"));
		bShowDisplayNames = Property->GetOwnerProperty()->HasMetaData(TEXT("ShowDisplayNames"));
}

static FText GetClassDisplayName(const UObject* Object, bool bShowDisplayNames)
{
	const UClass* Class = Cast<UClass>(Object);
	if (Class != nullptr)
	{
		if (bShowDisplayNames)
		{
			return Class->GetDisplayNameText();
		}

		UBlueprint* BP = UBlueprint::GetBlueprintFromClass(Class);
		if(BP != nullptr)
		{
			return FText::FromString(BP->GetName());
		}
	}
	return (Object) ? FText::FromString(Object->GetName()) : LOCTEXT("InvalidObject", "None");
}

FText SPropertyEditorStruct::GetDisplayValue() const
{
		static bool bIsReentrant = false;

		auto GetStructDisplayName = [this](const UObject* InObject) -> FText
		{
			if (const UScriptStruct* Struct = Cast<UScriptStruct>(InObject))
			{
				return bShowDisplayNames
					? Struct->GetDisplayNameText()
					: FText::AsCultureInvariant(Struct->GetName());
			}
			return LOCTEXT("None", "None");
		};
	}
```