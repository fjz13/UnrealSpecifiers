# DataTablePin

Description: 指定一个函数参数为DataTable或CurveTable类型，以便为FName的其他参数提供RowNameList的选择。
Usage: UFUNCTION
Feature: Blueprint
Group: PIn
Type: string="abc"
LimitedType: DataTable，CurveTable
Status: Done

指定一个函数参数为UDataTable类型，这样就可以加载根据DataTable里的数据，为RowName提供一个List来选择，而不是手填。支持的类型是DataTable和CurveTable

如果是DataTablePin，则会采用UK2Node_CallDataTableFunction来生成蓝图节点，以便在DataTable Pin连接参数改变的时候，触发RowNameList的刷新。

UK2Node_GetDataTableRow也是一个单独的蓝图节点。

但是发现RowName并没有用meta指定？但是有判断函数的参数如果类型是FName，就会把它当作RowName来看待。（这么简单粗糙的判断，也是因为其并不打算把这个Meta给用户使用）。因此实际上函数里可以有多个FName的参数，都会被自动的赋予RowNameList

在源码中用的地方只有UDataTableFunctionLibrary

```cpp
UFUNCTION(BlueprintCallable, Category = "DataTable", meta = (ExpandEnumAsExecs="OutResult", DataTablePin="CurveTable"))
static ENGINE_API void EvaluateCurveTableRow(UCurveTable* CurveTable, FName RowName, float InXY, TEnumAsByte<EEvaluateCurveTableResult::Type>& OutResult, float& OutXY,const FString& ContextString);
```

测试代码：

```cpp
	UFUNCTION(BlueprintCallable, meta = (DataTablePin="CurveTable"))
	static void GetMyCurveTableRow(UCurveTable* CurveTable, FName MyRowName, float InXY, float& OutXY,const FString& ContextString){}
	
	UFUNCTION(BlueprintCallable, meta = (DataTablePin="TargetTable"))
	static bool HasMyDataTableRow(UDataTable* TargetTable, FName MyRowName,FName OtherRowName){return false;}
```

蓝图效果：

左侧为自己定义的函数节点，可以看见左侧的蓝图节点上的Name都变成了CurveTable和DataTable里的RowNameList，即使这些FName参数并没有什么特殊指定，但是蓝图系统里自动识别到FName类型并改变了实际的Pin Widget.

![Untitled](DataTablePin/Untitled.png)

原理：

如果发现FName节点，会去尝试找DataTablePin，然后根据DataTablePin的类型来改变FName类型的Pin类型。

```cpp
TSharedPtr<class SGraphPin> FBlueprintGraphPanelPinFactory::CreatePin(class UEdGraphPin* InPin) const
{
	if (InPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Name)
	{
		UObject* Outer = InPin->GetOuter();

		// Create drop down combo boxes for DataTable and CurveTable RowName pins
		const UEdGraphPin* DataTablePin = nullptr;
		if (Outer->IsA(UK2Node_CallFunction::StaticClass()))
		{
			const UK2Node_CallFunction* CallFunctionNode = CastChecked<UK2Node_CallFunction>(Outer);
			if (CallFunctionNode)
			{
				const UFunction* FunctionToCall = CallFunctionNode->GetTargetFunction();
				if (FunctionToCall)
				{
					const FString& DataTablePinName = FunctionToCall->GetMetaData(FBlueprintMetadata::MD_DataTablePin);
					DataTablePin = CallFunctionNode->FindPin(DataTablePinName);
				}
			}
		}
		else if (Outer->IsA(UK2Node_GetDataTableRow::StaticClass()))
		{
			const UK2Node_GetDataTableRow* GetDataTableRowNode = CastChecked<UK2Node_GetDataTableRow>(Outer);
			DataTablePin = GetDataTableRowNode->GetDataTablePin();
		}

		if (DataTablePin)
		{
			if (DataTablePin->DefaultObject != nullptr && DataTablePin->LinkedTo.Num() == 0)
			{
				if (auto DataTable = Cast<UDataTable>(DataTablePin->DefaultObject))
				{
					return SNew(SGraphPinDataTableRowName, InPin, DataTable);
				}
				if (DataTablePin->DefaultObject->IsA(UCurveTable::StaticClass()))
				{
					UCurveTable* CurveTable = (UCurveTable*)DataTablePin->DefaultObject;
					if (CurveTable)
					{
						TArray<TSharedPtr<FName>> RowNames;
						/** Extract all the row names from the RowMap */
						for (TMap<FName, FRealCurve*>::TConstIterator Iterator(CurveTable->GetRowMap()); Iterator; ++Iterator)
						{
							/** Create a simple array of the row names */
							TSharedPtr<FName> RowNameItem = MakeShareable(new FName(Iterator.Key()));
							RowNames.Add(RowNameItem);
						}
						return SNew(SGraphPinNameList, InPin, RowNames);
					}
				}
			}
		}
	}

	return nullptr;
}

```