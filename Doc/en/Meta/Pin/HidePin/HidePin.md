# HidePin

- **Function Description:** Used in function calls to specify parameter names to be hidden, as well as to hide return values. Multiple parameters can be hidden
- **Usage Location:** UFUNCTION
- **Engine Module:** Pin
- **Metadata Type:** strings="a, b, c"
- **Associated Items:** [InternalUseParam](../InternalUseParam/InternalUseParam.md)
- **Commonality:** ★★

In the source code, it is often found to be in a contract comparison with DefaultToSelf. It is both hidden and has a default value. The combined effect is to restrict a static function call to an external calling environment object directly as a parameter.

The value of HidePin is frequently WorldContextObject

meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject")

## C++ Test Code:

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyFunction_HidePinfTest :public AActor
{
public:
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	int MyFunc_Default(FName name, float value, FString options) { return 0; }

	UFUNCTION(BlueprintCallable, meta = (HidePin = "options"))
	int MyFunc_HidePin(FName name, float value, FString options) { return 0; }

	UFUNCTION(BlueprintCallable, meta = (InternalUseParam = "options,comment"))
	int MyFunc_HidePin2(FName name, float value, FString options,FString comment) { return 0; }

	UFUNCTION(BlueprintCallable, meta = (InternalUseParam = "options"))
	int MyFunc_InternalUseParam(FName name, float value, FString options) { return 0; }

	UFUNCTION(BlueprintCallable, meta = (HidePin = "ReturnValue"))
	int MyFunc_HideReturn(FName name, float value, FString options, FString& otherReturn) { return 0; }

public:
	UFUNCTION(BlueprintPure)
	int MyPure_Default(FName name, float value, FString options) { return 0; }

	UFUNCTION(BlueprintPure, meta = (HidePin = "options"))
	int MyPure_HidePin(FName name, float value, FString options) { return 0; }

	UFUNCTION(BlueprintPure, meta = (InternalUseParam = "options"))
	int MyPure_InternalUseParam(FName name, float value, FString options) { return 0; }

	UFUNCTION(BlueprintPure, meta = (HidePin = "ReturnValue"))
	int MyPure_HideReturn(FName name, float value, FString options, FString& otherReturn) { return 0; }

public:
	UFUNCTION(BlueprintCallable, meta = (InternalUseParam = "options,comment"))
	int MyFunc_InternalUseParams2(FName name, float value, FString options,FString comment) { return 0; }

	UFUNCTION(BlueprintCallable, meta = (InternalUseParam = "options,comment,ReturnValue"))
	int MyFunc_InternalUseParams3(FName name, float value, FString options,FString comment) { return 0; }

};
```

## Blueprint Test Results:

![Untitled](Untitled.png)

It can be observed that both BlueprintCallable and BlueprintPure are actually applicable. Additionally, ReturnValue is the default name for the return value, which can also be hidden using this feature.

## Principle:

When searching through the source code, the only usage found is:

The following types of Pins are automatically hidden:

- LatentInfo="ParameterName"
- HidePin="ParameterName"
- InternalUseParam="ParameterName1, ParameterName2", multiple entries are allowed
- PinNames specified in ExpandEnumAsExecs or ExpandBoolAsExecs
- WorldContext="ParameterName", when a member function is called and the C++ base class has an implementation of GetWorld, the WorldContext can be automatically assigned the correct World value without the need for display.

This function is invoked by CreatePinsForFunctionCall to filter the internal properties of a Function, which include Params and ReturnValue. Therefore, HidePin cannot be used to hide Pins such as Target; this requirement should be addressed by HideSelfPin.

```cpp
// Gets a list of pins that should hidden for a given function
void FBlueprintEditorUtils::GetHiddenPinsForFunction(UEdGraph const* Graph, UFunction const* Function, TSet<FName>& HiddenPins, TSet<FName>* OutInternalPins)
{
	check(Function != nullptr);
	TMap<FName, FString>* MetaData = UMetaData::GetMapForObject(Function);
	if (MetaData != nullptr)
	{
		for (TMap<FName, FString>::TConstIterator It(*MetaData); It; ++It)
		{
			const FName& Key = It.Key();

			if (Key == FBlueprintMetadata::MD_LatentInfo)
			{
				HiddenPins.Add(*It.Value());
			}
			else if (Key == FBlueprintMetadata::MD_HidePin)
			{
				TArray<FString> HiddenPinNames;
				It.Value().ParseIntoArray(HiddenPinNames, TEXT(","));
				for (FString& HiddenPinName : HiddenPinNames)
				{
					HiddenPinName.TrimStartAndEndInline();
					HiddenPins.Add(*HiddenPinName);
				}
			}
			else if (Key == FBlueprintMetadata::MD_ExpandEnumAsExecs ||
					Key == FBlueprintMetadata::MD_ExpandBoolAsExecs)
			{
				TArray<FName> EnumPinNames;
				UK2Node_CallFunction::GetExpandEnumPinNames(Function, EnumPinNames);

				for (const FName& EnumName : EnumPinNames)
				{
					HiddenPins.Add(EnumName);
				}
			}
			else if (Key == FBlueprintMetadata::MD_InternalUseParam)
			{
				TArray<FString> HiddenPinNames;
				It.Value().ParseIntoArray(HiddenPinNames, TEXT(","));
				for (FString& HiddenPinName : HiddenPinNames)
				{
					HiddenPinName.TrimStartAndEndInline();

					FName HiddenPinFName(*HiddenPinName);
					HiddenPins.Add(HiddenPinFName);

					if (OutInternalPins)
					{
						OutInternalPins->Add(HiddenPinFName);
					}
				}
			}
			else if (Key == FBlueprintMetadata::MD_WorldContext)
			{
				const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
				if(!K2Schema->IsStaticFunctionGraph(Graph))
				{
					bool bHasIntrinsicWorldContext = false;

					UBlueprint const* CallingContext = FindBlueprintForGraph(Graph);
					if (CallingContext && CallingContext->ParentClass)
					{
						UClass* NativeOwner = CallingContext->ParentClass;
						while(NativeOwner && !NativeOwner->IsNative())
						{
							NativeOwner = NativeOwner->GetSuperClass();
						}

						if(NativeOwner)
						{
							bHasIntrinsicWorldContext = NativeOwner->GetDefaultObject()->ImplementsGetWorld();
						}
					}

					// if the blueprint has world context that we can lookup with "self",
					// then we can hide this pin (and default it to self)
					if (bHasIntrinsicWorldContext)
					{
						HiddenPins.Add(*It.Value());
					}
				}
			}
		}
	}
}
```