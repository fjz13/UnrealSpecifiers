# AllowedLocators

- **Function Description:** Used for Sequencer to locate objects that can be bound
- **Usage Location:** UPROPERTY
- **Engine Module:** Scene
- **Metadata Type:** string="abc"
- **Restriction Type:** FUniversalObjectLocator
- **Commonly Used:** ★

Used to identify objects that can be bound for the Sequencer.

Appears to be an auxiliary locator used by the Sequencer for binding properties to Actors. It is typically only utilized within the predefined attribute FUniversalObjectLocator, and generally, there is no need to expand this section; hence, it is marked as OnlyInternal.

## Searchable in the source code:

```cpp

	// Helper struct for Binding Properties UI for locators.
USTRUCT()
struct FMovieSceneUniversalLocatorInfo
{
	GENERATED_BODY()

	// Locator for the entry
	UPROPERTY(EditAnywhere, Category = "Default", meta=(AllowedLocators="Actor"))
	FUniversalObjectLocator Locator;

	// Flags for how to resolve the locator
	UPROPERTY()
	ELocatorResolveFlags ResolveFlags = ELocatorResolveFlags::None;
};
```

Seems to be the type of object that is allowed to be located.

## Principle:

```cpp
TMap<FName, TSharedPtr<ILocatorEditor>> ApplicableLocators;

void FUniversalObjectLocatorCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
		TArray<FString> AllowedTypes;
		if (PropertyHandle->HasMetaData("AllowedLocators"))
		{
			PropertyHandle->GetMetaData("AllowedLocators").ParseIntoArray(AllowedTypes, TEXT(","));
		}
}

FUniversalObjectLocatorEditorModule& Module = FModuleManager::Get().LoadModuleChecked<FUniversalObjectLocatorEditorModule>("UniversalObjectLocatorEditor");
for (TPair<FName, TSharedPtr<ILocatorEditor>> Pair : Module.LocatorEditors)
{
	if (AllowedTypes.Num() == 0 || AllowedTypes.Contains(Pair.Key.ToString()))
	{
		ApplicableLocators.Add(Pair.Key, Pair.Value);
	}
}
```