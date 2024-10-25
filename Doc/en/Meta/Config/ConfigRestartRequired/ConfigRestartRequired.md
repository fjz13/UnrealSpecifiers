#ConfigRestartRequired

- **Function Description:** Prompts a dialog to restart the editor after properties are modified in the settings.
- **Usage Location:** UPROPERTY
- **Engine Module:** Config
- **Metadata Type:** bool
- **Commonality:** ★★★

Triggers a restart dialog for the editor after properties are changed in the settings.

Naturally, it is typically used for settings that necessitate a restart of the editor.

## Test Code:

```cpp
public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = ConfigRestartRequired, meta = (ConfigRestartRequired="true"))
	FString MyString_ConfigRestartRequired;
```

## Test Effects:

![Untitled](Untitled.png)

## Principle:

The effect is active in SSettingsEditor, indicating changes occur within the UI window, followed by a dialog prompt.

```cpp
void SSettingsEditor::NotifyPostChange( const FPropertyChangedEvent& PropertyChangedEvent, class FEditPropertyChain* PropertyThatChanged )
{
		static const FName ConfigRestartRequiredKey = "ConfigRestartRequired";
		if (PropertyChangedEvent.Property->GetBoolMetaData(ConfigRestartRequiredKey) || PropertyChangedEvent.MemberProperty->GetBoolMetaData(ConfigRestartRequiredKey))
		{
						OnApplicationRestartRequiredDelegate.ExecuteIfBound();
		}
}
```