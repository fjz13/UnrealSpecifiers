# InternalUseParam

Usage: UFUNCTION
Feature: Blueprint
Type: strings="a，b，c"
Description: 用在函数调用上，指定要隐藏的参数名称，也可以隐藏返回值。可以隐藏多个
Example: InternalUseParam="Parameter1, Parameter2”
Status: Done
Group: Blueprint

和HidePin类似，但区别是可以隐藏多个。

源码中的例子：

```cpp
UFUNCTION(BlueprintCallable, meta=(ScriptNoExport, BlueprintInternalUseOnly = "true", DefaultToSelf="ComponentTemplateContext", InternalUseParam="ComponentTemplateContext,bDeferredFinish"))
ENGINE_API UActorComponent* AddComponent(FName TemplateName, bool bManualAttachment, const FTransform& RelativeTransform, const UObject* ComponentTemplateContext, bool bDeferredFinish = false);
```

在源码中的逻辑：

```cpp
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
```

C++测试代码：

```cpp
UFUNCTION(BlueprintCallable, meta = (InternalUseParam = "options,comment"))
	int MyFunc_InternalUseParams2(FName name, float value, FString options,FString comment) { return 0; }

	UFUNCTION(BlueprintCallable, meta = (InternalUseParam = "options,comment,ReturnValue"))
	int MyFunc_InternalUseParams3(FName name, float value, FString options,FString comment) { return 0; }
```

蓝图效果：

![Untitled](InternalUseParam/Untitled.png)

同样支持ReturnValue的隐藏