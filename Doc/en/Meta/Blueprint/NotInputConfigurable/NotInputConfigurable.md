# NotInputConfigurable

- **Function Description:** Prevents certain UInputModifier and UInputTrigger instances from being configurable in ProjectSettings.
- **Usage Location:** UCLASS
- **Engine Module:** Blueprint
- **Metadata Type:** bool
- **Restricted Types:** Subclasses of UInputModifier and UInputTrigger
- **Commonality:** ★

Prevents certain UInputModifier and UInputTrigger instances from being configurable in ProjectSettings.

## Source Code Example:

```cpp
UCLASS(NotBlueprintable, meta = (DisplayName = "Chorded Action", NotInputConfigurable = "true"))
class ENHANCEDINPUT_API UInputTriggerChordAction : public UInputTrigger
{}

UCLASS(NotBlueprintable, meta = (DisplayName = "Combo (Beta)", NotInputConfigurable = "true"))
class ENHANCEDINPUT_API UInputTriggerCombo : public UInputTrigger
{}
```

## Test Code:

```cpp
UCLASS( meta = (NotInputConfigurable = "true"))
class INSIDER_API UMyInputTrigger_NotInputConfigurable :public UInputTrigger
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	float MyFloat = 123;
};

UCLASS( meta = ())
class INSIDER_API UMyInputTrigger_Configurable :public UInputTrigger
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	float MyFloatConfigurable = 123;
};

```

## Test Results:

Only UMyInputTrigger_Configurable is visible for editing the default value.

![Untitled](Untitled.png)

## Principle:

The UI customization in UEnhancedInputDeveloperSettings gathers the CDO objects of UInputModifier and UInputTrigger, then filters out those that are not configurable based on the NotInputConfigurable metadata.

```cpp

	GatherNativeClassDetailsCDOs(UInputModifier::StaticClass(), ModifierCDOs);
	GatherNativeClassDetailsCDOs(UInputTrigger::StaticClass(), TriggerCDOs);


void FEnhancedInputDeveloperSettingsCustomization::GatherNativeClassDetailsCDOs(UClass* Class, TArray<UObject*>& CDOs)
{
			// Strip objects with no config stored properties
		CDOs.RemoveAll([Class](UObject* Object) {
			UClass* ObjectClass = Object->GetClass();
			if (ObjectClass->GetMetaData(TEXT("NotInputConfigurable")).ToBool())
			{
				return true;
			}
			while (ObjectClass)
			{
				for (FProperty* Property : TFieldRange<FProperty>(ObjectClass, EFieldIteratorFlags::ExcludeSuper, EFieldIteratorFlags::ExcludeDeprecated))
				{
					if (Property->HasAnyPropertyFlags(CPF_Config))
					{
						return false;
					}
				}

				// Stop searching at the base type. We don't care about configurable properties lower than that.
				ObjectClass = ObjectClass != Class ? ObjectClass->GetSuperClass() : nullptr;
			}
			return true;
		});
}
```