# HideAssetPicker

- **Function Description:** Hides the selection list of the AssetPicker on an Object type pin
- **Usage Location:** UFUNCTION
- **Engine Module:** Object Property
- **Metadata Type:** strings = "a, b, c"
- **Restriction Type:** UObject*
- **Commonliness:** ★★

Hides the selection list of the AssetPicker on Object type pins. This is particularly useful when we want to pass an Object reference directly without allowing the user to select other assets within the engine. Since the Asset type is a subclass of Object, the parameter for an Object reference type is referred to as HideAssetPicker.

There is no usage found in the source code, but this feature is functional.

## Test Code:

```cpp
	UFUNCTION(BlueprintCallable)
	static void MyFunc_NoHideAssetPicker(UObject* ObjectClass) {}

	UFUNCTION(BlueprintCallable, meta = (HideAssetPicker = "ObjectClass"))
	static void MyFunc_HideAssetPicker(UObject* ObjectClass) {}
```

## Blueprint Effect:

In the default scenario, MyFunc_NoHideAssetPicker can pop up a selection list. However, MyFunc_HideAssetPicker remains hidden.

![Untitled](Untitled.png)

## Principle:

The logic for determining whether a function pin can open the AssetPicker is as follows:

- It must be an object type
- If it is a UActorComponent, it will not be displayed
- If it is an Actor type, it must be within a level blueprint and the Actor must be marked as placeable to be displayed.
- If the parameter is explicitly specified with HideAssetPicker, it will also not be displayed.

```cpp
bool UEdGraphSchema_K2::ShouldShowAssetPickerForPin(UEdGraphPin* Pin) const
{
	bool bShow = true;
	if (Pin->PinType.PinCategory == PC_Object)
	{
		UClass* ObjectClass = Cast<UClass>(Pin->PinType.PinSubCategoryObject.Get());
		if (ObjectClass)
		{
			// Don't show literal buttons for component type objects
			bShow = !ObjectClass->IsChildOf(UActorComponent::StaticClass());

			if (bShow && ObjectClass->IsChildOf(AActor::StaticClass()))
			{
				// Only show the picker for Actor classes if the class is placeable and we are in the level script
				bShow = !ObjectClass->HasAllClassFlags(CLASS_NotPlaceable)
							&& FBlueprintEditorUtils::IsLevelScriptBlueprint(FBlueprintEditorUtils::FindBlueprintForNode(Pin->GetOwningNode()));
			}

			if (bShow)
			{
				if (UK2Node_CallFunction* CallFunctionNode = Cast<UK2Node_CallFunction>(Pin->GetOwningNode()))
				{
					if (UFunction* FunctionRef = CallFunctionNode->GetTargetFunction())
					{
						const UEdGraphPin* WorldContextPin = CallFunctionNode->FindPin(FunctionRef->GetMetaData(FBlueprintMetadata::MD_WorldContext));
						bShow = ( WorldContextPin != Pin );

						// Check if we have explictly marked this pin as hiding the asset picker
						const FString& HideAssetPickerMetaData = FunctionRef->GetMetaData(FBlueprintMetadata::MD_HideAssetPicker);
						if(!HideAssetPickerMetaData.IsEmpty())
						{
							TArray<FString> PinNames;
							HideAssetPickerMetaData.ParseIntoArray(PinNames, TEXT(","), true);
							const FString PinName = Pin->GetName();
							for(FString& ParamNameToHide : PinNames)
							{
								ParamNameToHide.TrimStartAndEndInline();
								if(ParamNameToHide == PinName)
								{
									bShow = false;
									break;
								}
							}
						}
					}
				}
				else if (Cast<UK2Node_CreateDelegate>( Pin->GetOwningNode()))
				{
					bShow = false;
				}
			}
		}
	}
	return bShow;
}

```