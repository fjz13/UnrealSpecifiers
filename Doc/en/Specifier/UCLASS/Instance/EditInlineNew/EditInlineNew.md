# EditInlineNew

- **Function Description:** Specifies that objects of this class can be directly created inline within the property details panel, and this should be coordinated with the attribute's Instanced property.
- **Engine Module:** Instance
- **Metadata Type:** bool
- **Functionality Mechanism:** Add [CLASS_EditInlineNew](../../../../Flags/EClassFlags/CLASS_EditInlineNew.md) to ClassFlags
- **Associated Items:** NotEditInlineNew (NotEditInlineNew.md)
- **Commonly Used:** ★★★★★

Objects of this class can be directly created inline within the property details panel.

If you wish to create objects directly in the details panel, the attribute must first be marked as Instanced or ShowInnerProperties.

EditInlineNew is primarily used on subclasses of UObject. Typically, classes not marked with EditInlineNew are used for references to Actors or assets. Note that EditInlineNew indicates the capability to create object instances directly from the property details panel, not a restriction to creation only within the panel. Of course, you can also manually create a new object and assign it to the object reference attribute.

This is independent of the Instanced capability on UPROPERTY. If EditInlineNew is not added to UCLASS, but Instanced is added to an attribute, after manually assigning a new object to the attribute, the attribute will also expand to show internal properties for editing. This is because the Instanced attribute automatically adds the EditInline meta to the property.

This specifier is inherited by all subclasses; subclasses can override it using the NotEditInlineNew specifier.

## Sample Code:

```cpp
UCLASS(Blueprintable, EditInlineNew)
class INSIDER_API UMyClass_EditInlineNew :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyProperty;
};

UCLASS(Blueprintable, NotEditInlineNew)
class INSIDER_API UMyClass_NotEditInlineNew :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyProperty;
};

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyClass_Edit_Test :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = InstancedProperty)
		UMyClass_EditInlineNew* MyEditInlineNew;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = InstancedProperty)
		UMyClass_NotEditInlineNew* MyNotEditInlineNew;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NormalProperty)
		UMyClass_EditInlineNew* MyEditInlineNew_NotInstanced;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NormalProperty)
		UMyClass_NotEditInlineNew* MyNotEditInlineNew_NotInstanced;
};
```

## Example Effect:

EditInlineNew supports direct creation of object instances from C++ or BP subclasses, allowing editing of the instances on them.

Properties marked with NotEditInlineNew cannot find a supported class to create an object.

If an attribute does not have Instanced, you can only attempt to reference it (the object cannot be found).

![image](image.png)

## Principle:

The class's ability to be created inline for editing is determined by whether it has the CLASS_EditInlineNew flag.

```cpp
template <typename TClass, typename TIsChildOfFunction>
bool FPropertyEditorInlineClassFilter::IsClassAllowedHelper(TClass InClass, TIsChildOfFunction IsClassChildOf, TSharedRef< FClassViewerFilterFuncs > InFilterFuncs)
{
	const bool bMatchesFlags = InClass->HasAnyClassFlags(CLASS_EditInlineNew) &&
		!InClass->HasAnyClassFlags(CLASS_Hidden | CLASS_HideDropDown | CLASS_Deprecated) &&
		(bAllowAbstract || !InClass->HasAnyClassFlags(CLASS_Abstract));
}
```