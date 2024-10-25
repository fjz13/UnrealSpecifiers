# SetParam

- **功能描述：** 指定一个函数为使用Set<TItem>的函数，元素类型为通配符的泛型。
- **使用位置：** UFUNCTION
- **引擎模块：** Blueprint
- **元数据类型：** string="A | B | C"
- **限制类型：** TSet
- **常用程度：** ★★★

源码在UBlueprintSetLibrary。

SetParam支持多个Set和元素参数，以‘,’分隔开，然后Pin的引脚可以通过‘|’继续分隔，形成”SetA | ItemA, SetB | ItemB”的多组数据。

## 测试代码：

```cpp
	UFUNCTION(BlueprintCallable, CustomThunk, meta = (SetParam = "SetA|ItemA,SetB|ItemB"))
	static void MySet_Add2(const TSet<int32>& SetA, const int32& ItemA, const TSet<int32>& SetB, const int32& ItemB);
	static void GenericMySet_Add2(const void* TargetSet, const FSetProperty* SetA, const void* ItemA, const FSetProperty* SetB, const void* ItemB);
	DECLARE_FUNCTION(execMySet_Add2);
```

## 蓝图里效果：

![Untitled](Untitled.png)

## 原理：

用‘,’分隔的是组，组内用’|’分隔的参数Pin都是同一种类型的。

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