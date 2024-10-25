# DisplayPriority

- **Function Description:** Specifies the display order priority of this attribute within the details panel; lower values indicate higher priority.
- **Usage Location:** UPROPERTY
- **Engine Module:** DetailsPanel
- **Metadata Type:** int32
- **Commonly Used:** ★★★

Specifies the display order priority of this attribute within the details panel; lower values indicate higher priority.

- If there is a setting for DisplayAfter, it takes precedence over the priority value.
- The same restriction applies within the same Category.

## Test Code:

```cpp
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PriorityTest, meta = (DisplayPriority = 3))
	int32 MyInt_P3 = 123;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PriorityTest, meta = (DisplayPriority = 1))
	int32 MyInt_P1 = 123;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PriorityTest, meta = (DisplayPriority = 2))
	int32 MyInt_P2 = 123;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PriorityTest, meta = (DisplayPriority = 4,DisplayAfter="MyInt_P1"))
	int32 MyInt_P4 = 123;
```

## Test Results:

Even with a lower priority, P4 is still placed after P1 due to the DisplayAfter setting.

![Untitled](Untitled.png)

## Principle:

The sorting logic is contained within this function; a simple insertion sort algorithm is employed.

```cpp
void PropertyEditorHelpers::OrderPropertiesFromMetadata(TArray<FProperty*>& Properties)
{}
```