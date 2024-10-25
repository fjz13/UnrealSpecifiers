# MakeEditWidget

- **Function Description:** Allows FVector and FTransform to appear as draggable widgets within the scene editor.
- **Usage Location:** UPROPERTY
- **Engine Module:** Scene
- **Metadata Type:** bool
- **Restricted Types:** FVector, FTransform
- **Associated Items:** [ValidateWidgetUsing](../ValidateWidgetUsing/ValidateWidgetUsing.md)
- **Commonly Used:** ★★★

Enables FVector and FTransform to appear as draggable widgets within the scene editor.

Offering a more intuitive experience compared to direct numerical editing.

## Test Code:

```cpp
UCLASS(BlueprintType)
class INSIDER_API AMyActor_EditWidget :public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="EditWidget")
	FVector MyVector;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="EditWidget",meta=(MakeEditWidget))
	FVector MyVector_MakeEditWidget;
};

```

## Test Results:

In the AMyActor_EditWidget subclass inherited in the blueprint, adding another FTransform variable allows the "Show 3D Widget" option to be visible. Both this and MyVector_MakeEditWidget are represented as draggable widgets within the scene.

![Untitled](Untitled.png)

## Principle:

If it is determined to be FVector or FTransform and possesses the MakeEditWidget attribute, a widget can be created.

```cpp
/** Value of UPROPERTY can be edited with a widget in the editor (translation, rotation) */
static UNREALED_API const FName MD_MakeEditWidget;
/** Specifies a function used for validation of the current value of a property.  The function returns a string that is empty if the value is valid, or contains an error description if the value is invalid */
static UNREALED_API const FName MD_ValidateWidgetUsing;

bool FLegacyEdModeWidgetHelper::CanCreateWidgetForStructure(const UStruct* InPropStruct)
{
	return InPropStruct && (InPropStruct->GetFName() == NAME_Vector || InPropStruct->GetFName() == NAME_Transform);
}

bool FLegacyEdModeWidgetHelper::ShouldCreateWidgetForProperty(FProperty* InProp)
{
	return CanCreateWidgetForProperty(InProp) && InProp->HasMetaData(MD_MakeEditWidget);
}

```