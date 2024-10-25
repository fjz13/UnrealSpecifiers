# EditorConfig

- **Function description:** Used for saving information in the editor mode.
- **Engine modules:** Config, Editor
- **Metadata type:** string="abc"
- **Action mechanism:** Add [EditorConfig](../../../../Meta/Config/EditorConfig.md) within Meta
- **Commonly used: ★**

Used for saving information in the editor mode.

Generally used in the EditorTarget module for configuring corresponding editor settings, such as column width, bookmarks, etc., saved in JSON format.

Saved in: C:\Users\{user name}\AppData\Local\UnrealEngine\Editor. Presently includes:

![Untitled](Untitled.png)

After searching the source code, it must be used by inheriting from the base class:

```cpp
/** Inherit from this class to simplify saving and loading properties from editor configs. */
UCLASS()
class EDITORCONFIG_API UEditorConfigBase : public UObject
{
	GENERATED_BODY()

public:

	/** Load any properties of this class into properties marked with metadata tag "EditorConfig" from the class's EditorConfig */
	bool LoadEditorConfig();

	/** Save any properties of this class in properties marked with metadata tag "EditorConfig" into the class's EditorConfig. */
	bool SaveEditorConfig() const;
};
```

## Sample code:

```cpp
UCLASS(EditorConfig = "MyEditorGame")
class INSIDER_API UMyClass_EditorConfig : public UEditorConfigBase
{
public:
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditorConfig))
	int32 MyPropertyWithConfig = 123;
};

void UMyClass_EditorConfig_Test::TestConfigSave()
{
	//must run after editor initialization
	auto* testObject = NewObject<UMyClass_EditorConfig>(GetTransientPackage(), TEXT("testObject_EditorConfig"));
	testObject->MyPropertyWithConfig = 777;
	testObject->SaveEditorConfig();

}

void UMyClass_EditorConfig_Test::TestConfigLoad()
{
	auto* testObject = NewObject<UMyClass_EditorConfig>(GetTransientPackage(), TEXT("testObject_EditorConfig"));
	testObject->LoadEditorConfig();
}

//Save result after executing Save: C:\Users\jack.fu\AppData\Local\UnrealEngine\Editor\MyEditorGame.json

{
	"$type": "MyClass_EditorConfig",
	"MyPropertyWithConfig": 777
}
```