# MinimalAPI

- **Function Description:** Specifies that the UInterface object should not be exported to other modules
- **Metadata Type:** bool
- **Engine Module:** DllExport
- **Common Usage:** ★

Refer to the explanation of MinimalAPI within UCLASS for guidance.

Primarily, UInterface objects serve merely as auxiliary interface objects, and therefore do not possess functions that need to be exposed. As a result, the majority of UInterface objects in the source code are designated as MinimalAPI to expedite compilation and prevent their use by other modules.

```cpp
UINTERFACE(MinimalAPI, BlueprintType)
class USoundLibraryProviderInterface : public UInterface
{
	GENERATED_BODY()
};
```