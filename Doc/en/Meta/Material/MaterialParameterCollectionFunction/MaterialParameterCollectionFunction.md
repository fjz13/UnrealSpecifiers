# MaterialParameterCollectionFunction

- **Function Description:** Specifies that this function is designed to operate on UMaterialParameterCollection, thereby enabling the extraction and validation of ParameterName
- **Usage Location:** UFUNCTION
- **Engine Module:** Material
- **Metadata Type:** bool
- **Restriction Type:** Functions with a UMaterialParameterCollection parameter
- **Commonality:** ★★★

Indicates that this function is intended for operating on UMaterialParameterCollection, facilitating the extraction and validation of ParameterName.

## Test Code:

```cpp

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyFunction_Material :public UBlueprintFunctionLibrary
{
public:
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject", MaterialParameterCollectionFunction))
	static void MySetScalarParameterValue(UObject* WorldContextObject, UMaterialParameterCollection* Collection, FName ParameterName, float ParameterValue);

	UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
	static void MySetScalarParameterValue_NoError(UObject* WorldContextObject, UMaterialParameterCollection* Collection, FName ParameterName, float ParameterValue);
};
```

## Blueprint Effect:

The engine's built-in UKismetMaterialLibrary::SetScalarParameterValue and our custom MySetScalarParameterValue functions trigger the verification check for the material parameter collection in blueprints. If ParameterName is not specified, a compilation error will be generated. The MySetScalarParameterValue_NoError function, which lacks the MaterialParameterCollectionFunction tag, is treated as a regular function; it does not automatically select from the MPC's Parameters collection, nor does it perform error checking for an empty ParameterName.

![Untitled](Untitled.png)

## Principle:

```cpp
UBlueprintFunctionNodeSpawner* UBlueprintFunctionNodeSpawner::Create(UFunction const* const Function, UObject* Outer/* = nullptr*/)
{
	bool const bIsMaterialParamCollectionFunc = Function->HasMetaData(FBlueprintMetadata::MD_MaterialParameterCollectionFunction);
	if (bIsMaterialParamCollectionFunc)
	{
		NodeClass = UK2Node_CallMaterialParameterCollectionFunction::StaticClass();
	}
	else
	{
		NodeClass = UK2Node_CallFunction::StaticClass();
	}
}

TSharedPtr<SGraphNode> FNodeFactory::CreateNodeWidget(UEdGraphNode* InNode)
{
		if (UK2Node_CallMaterialParameterCollectionFunction* CallFunctionNode = Cast<UK2Node_CallMaterialParameterCollectionFunction>(InNode))
		{
			return SNew(SGraphNodeCallParameterCollectionFunction, CallFunctionNode);
		}
}
TSharedPtr<SGraphPin> SGraphNodeCallParameterCollectionFunction::CreatePinWidget(UEdGraphPin* Pin) const
{
	//Operations such as extracting the parameter list from MPC
		if (Collection)
		{
			// Populate the ParameterName pin combobox with valid options from the Collection
			const bool bVectorParameters = CallFunctionNode->FunctionReference.GetMemberName().ToString().Contains(TEXT("Vector"));
			Collection->GetParameterNames(NameList, bVectorParameters);
		}
}
```

The MaterialParameterCollectionFunction tag utilizes UK2Node_CallMaterialParameterCollectionFunction to validate the correct writing of material functions. Additionally, the UK2Node_CallMaterialParameterCollectionFunction blueprint node is recognized within the engine to further customize the ParameterName pin nodes.

Within the engine source code, the only functions marked with MaterialParameterCollectionFunction are those found in UKismetMaterialLibrary.