# BlueprintGetter

- **功能描述：**指定该函数作为属性的自定义Get函数。

- **元数据类型：**bool
- **引擎模块：**Blueprint
- **作用机制：**在Meta中加入[BlueprintGetter](../../../Meta/Blueprint/BlueprintGetter.md)，在FunctionFlags加入[FUNC_BlueprintCallable](../../../Flags/EFunctionFlags/FUNC_BlueprintCallable.md)、[FUNC_BlueprintPure](../../../Flags/EFunctionFlags/FUNC_BlueprintPure.md)
- **常用程度：**★★

指定该函数作为属性的自定义Get函数。

此说明符隐含BlueprintPure和BlueprintCallable。

更多可以参考UPROPERTY的BlueprintGetter