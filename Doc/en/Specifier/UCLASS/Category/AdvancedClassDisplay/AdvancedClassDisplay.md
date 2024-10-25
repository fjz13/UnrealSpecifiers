# AdvancedClassDisplay

- **Function description:** By default, display all properties of this class in the advanced directory
- **Engine module:** Category
- **Metadata type:** bool
- **Action mechanism:** Add [AdvancedClassDisplay](../../../../Meta/DetailsPanel/AdvancedClassDisplay.md) to the Meta class
- **Commonly used:** ★★★★

Make all properties of this class appear under the "Advanced" section of the class's Detail panel.

However, this can be overridden by using SimpleDisplay on an individual property. After searching through the source code, it was found that only 3 Actors use AdvancedClassDisplay, and none of these 3 Actors have redefined properties.

## Sample Code:

```cpp
UCLASS(Blueprintable,AdvancedClassDisplay)
class INSIDER_API UMyClass_AdvancedClassDisplay :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyProperty;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,SimpleDisplay)
		int32 MyProperty_Simple;
};

UCLASS(Blueprintable)
class INSIDER_API UMyClass_NoAdvancedClassDisplay :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyProperty;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay)
		int32 MyProperty_Simple;
};
```

## Example Effect:

MyProperty_Simple remains a straightforward display, even within the AdvancedClassDisplay class.

![Untitled](Untitled.png)

## Principle:

```cpp
// Property is advanced if it is marked advanced or the entire class is advanced and the property not marked as simple
static const FName Name_AdvancedClassDisplay("AdvancedClassDisplay");
bool bAdvanced = Property.IsValid() ? ( Property->HasAnyPropertyFlags(CPF_AdvancedDisplay) || ( !Property->HasAnyPropertyFlags( CPF_SimpleDisplay ) && Property->GetOwnerClass() && Property->GetOwnerClass()->GetBoolMetaData(Name_AdvancedClassDisplay) ) ) : false;
```