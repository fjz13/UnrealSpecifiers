# HideThen

- **Function Description:** Hide the 'Then' pin of asynchronous blueprint nodes
- **Usage Location:** UCLASS
- **Metadata Type:** boolean
- **Restriction Type:** Blueprint Asynchronous Node
- **Associated Items:** [ExposedAsyncProxy](../ExposedAsyncProxy/ExposedAsyncProxy.md)

In the source code HideThen is only judged in UK2Node_BaseAsyncTask , so this label only acts on blueprint asynchronous nodes.

## Test Code:

```cpp
UCLASS(Blueprintable, BlueprintType,meta = (ExposedAsyncProxy = MyAsyncObject))
class INSIDER_API UMyFunction_Async :public UCancellableAsyncAction
{}

UCLASS(Blueprintable, BlueprintType,meta = (ExposedAsyncProxy = MyAsyncObject,HideThen))
class INSIDER_API UMyFunction_Async :public UCancellableAsyncAction
{}
```

## Comparison Before and After Using HideThen:

![Untitled](Untitled.png)

## Source Code Position:

```cpp
void UK2Node_BaseAsyncTask::AllocateDefaultPins()
{
	bool bExposeProxy = false;
	bool bHideThen = false;
	FText ExposeProxyDisplayName;
	for (const UStruct* TestStruct = ProxyClass; TestStruct; TestStruct = TestStruct->GetSuperStruct())
	{
		bExposeProxy |= TestStruct->HasMetaData(TEXT("ExposedAsyncProxy"));
		bHideThen |= TestStruct->HasMetaData(TEXT("HideThen"));
		if (ExposeProxyDisplayName.IsEmpty())
		{
			ExposeProxyDisplayName = TestStruct->GetMetaDataText(TEXT("ExposedAsyncProxy"));
		}
	}

	if (!bHideThen)
	{
		CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then);
	}

}
```