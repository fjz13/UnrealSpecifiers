# AutoCollapseCategories

- **Function description:** The AutoCollapseCategories specifier overrides the effect of the AutoExpandCategories specifier on the listed categories of the parent class.
- **Engine module:** Category
- **Metadata type:** strings = (abc, "d|e", "x|y|z")
- **Mechanism of action:** Add [AutoCollapseCategories](../../../../Meta/DetailsPanel/AutoCollapseCategories.md) to Meta and remove [AutoExpandCategories](../../../../Meta/DetailsPanel/AutoExpandCategories.md)
- **Related items:** [DontAutoCollapseCategories](../DontAutoCollapseCategories.md), [AutoExpandCategories](../AutoExpandCategories/AutoExpandCategories.md)
- **Frequency:** ★

## Sample Code:

```cpp
UCLASS(Blueprintable, AutoCollapseCategories = ("MyGroup2|MyGroup22"))
class INSIDER_API UMyClass_AutoCollapseCategories :public UMyClass_AutoExpandCategories
{
	GENERATED_BODY()
public:
};
```

## Example Results:

The expansion of Group22 is disabled, but the expansion of 444 is still inherited

![Untitled](Untitled.png)