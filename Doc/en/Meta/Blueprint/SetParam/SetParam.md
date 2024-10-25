# SetParam

- **Function Description:** Specifies a function to utilize Set<TItem> with a wildcard generic element type.
- **Usage Location:** UFUNCTION
- **Engine Module:** Blueprint
- **Metadata Type:** string = "A" | B | C"
- **Restriction Type:** TSet
- **Commonliness:** ★★★

The source code is located in UBlueprintSetLibrary.

SetParam supports multiple Set and element parameters, separated by ‘,’, and then the Pin pin can be passed ‘|2	Test Code: | ItemA, SetB | 3	The effect in the blueprint:

## 4	Principle:

```cpp
	UFUNCTION(BlueprintCallable, CustomThunk, meta = (SetParam = "SetA|ItemA,SetB|ItemB"))
	static void MySet_Add2(const TSet<int32>& SetA, const int32& ItemA, const TSet<int32>& SetB, const int32& ItemB);
	static void GenericMySet_Add2(const void* TargetSet, const FSetProperty* SetA, const void* ItemA, const FSetProperty* SetB, const void* ItemB);
	DECLARE_FUNCTION(execMySet_Add2);
```

## Effect in the Blueprint:

![Untitled](Untitled.png)

## Principle:

Groups are separated by ‘,’, and ‘ is used within the group|All parameters Pin separated by '...' within a group are of the same type.

```cpp
void UK2Node_CallFunction::ConformContainerPins()
{
		// find any pins marked as SetParam
		const FString& SetPinMetaData = TargetFunction->GetMetaData(FBlueprintMetadata::MD_SetParam);

		// useless copies/allocates in this code, could be an optimization target...
		TArray<FString> SetParamPinGroups;
		{
			SetPinMetaData.ParseIntoArray(SetParamPinGroups, TEXT(","), true);
		}

		for (FString& Entry : SetParamPinGroups)
		{
			// split the group:
			TArray<FString> GroupEntries;
			Entry.ParseIntoArray(GroupEntries, TEXT("|"), true);
			// resolve pins
			TArray<UEdGraphPin*> ResolvedPins;
			for(UEdGraphPin* Pin : Pins)
			{
				if (GroupEntries.Contains(Pin->GetName()))
				{
					ResolvedPins.Add(Pin);
				}
			}

			// if nothing is connected (or non-default), reset to wildcard
			// else, find the first type and propagate to everyone else::
			bool bReadyToPropagatSetType = false;
			FEdGraphTerminalType TypeToPropagate;
			for (UEdGraphPin* Pin : ResolvedPins)
			{
				TryReadTypeToPropagate(Pin, bReadyToPropagatSetType, TypeToPropagate);
				if(bReadyToPropagatSetType)
				{
					break;
				}
			}

			for (UEdGraphPin* Pin : ResolvedPins)
			{
				TryPropagateType( Pin, TypeToPropagate, bReadyToPropagatSetType );
			}
		}
	}
```