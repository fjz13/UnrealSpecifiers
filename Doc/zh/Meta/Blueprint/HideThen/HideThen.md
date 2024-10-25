# HideThen

- **功能描述：** 隐藏异步蓝图节点的Then引脚
- **使用位置：** UCLASS
- **元数据类型：** bool
- **限制类型：** 蓝图异步节点
- **关联项：** [ExposedAsyncProxy](../ExposedAsyncProxy/ExposedAsyncProxy.md)

在源码中HideThen只在UK2Node_BaseAsyncTask中判断，因此这个标签只作用于蓝图异步节点。

## 测试代码：

```cpp
UCLASS(Blueprintable, BlueprintType,meta = (ExposedAsyncProxy = MyAsyncObject))
class INSIDER_API UMyFunction_Async :public UCancellableAsyncAction
{}

UCLASS(Blueprintable, BlueprintType,meta = (ExposedAsyncProxy = MyAsyncObject,HideThen))
class INSIDER_API UMyFunction_Async :public UCancellableAsyncAction
{}
```

## 使用HideThen前后对比：

![Untitled](Untitled.png)

## 源码位置：

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