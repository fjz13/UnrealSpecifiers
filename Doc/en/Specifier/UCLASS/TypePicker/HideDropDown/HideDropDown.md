# HideDropDown

- **Function Description:** Hide this class within the class selector
- **Engine Module:** TypePicker
- **Metadata Type:** bool
- **Action Mechanism:** Add [CLASS_HideDropDown](../../../../Flags/EClassFlags/CLASS_HideDropDown.md) to ClassFlags
- **Commonality:** ★★

Within the class selector, hide this class, typically triggered by TSubClassOf or initiated by the Class variable. In such cases, this specifier can prevent its appearance. In source code, this is usually applied to deprecated classes, Test classes, Abstract classes, and base classes.

## Example Code:

```cpp
UCLASS(Blueprintable)
class INSIDER_API UMyClass_HideDropDownBase :public UObject
{
	GENERATED_BODY()
public:
};

UCLASS(Blueprintable, hidedropdown)
class INSIDER_API UMyClass_HideDropDown :public UMyClass_HideDropDownBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyProperty;
};

UCLASS(Blueprintable, hidedropdown)
class INSIDER_API UMyClass_NoHideDropDown :public UMyClass_HideDropDownBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyProperty;
};

UCLASS(Blueprintable)
class INSIDER_API UMyClass_HideDropDown_Test :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UMyClass_HideDropDownBase> DropDownClass;
};
```

## Example Results:

![Untitled](Untitled.png)

## Conceptual Framework:

The HideDropDown flag sets the CLASS_HideDropDown marker, thereby excluding the class from the type UI customization list.

```cpp
template <typename TClass>
bool FPropertyEditorClassFilter::IsClassAllowedHelper(TClass InClass)
{
	bool bMatchesFlags = !InClass->HasAnyClassFlags(CLASS_Hidden | CLASS_HideDropDown | CLASS_Deprecated) &&
		(bAllowAbstract || !InClass->HasAnyClassFlags(CLASS_Abstract));

	if (bMatchesFlags && InClass->IsChildOf(ClassPropertyMetaClass)
		&& (!InterfaceThatMustBeImplemented || InClass->ImplementsInterface(InterfaceThatMustBeImplemented)))
	{
		auto PredicateFn = [InClass](const UClass* Class)
		{
			return InClass->IsChildOf(Class);
		};

		if (DisallowedClassFilters.FindByPredicate(PredicateFn) == nullptr &&
			(AllowedClassFilters.Num() == 0 || AllowedClassFilters.FindByPredicate(PredicateFn) != nullptr))
		{
			return true;
		}
	}

	return false;
}
```