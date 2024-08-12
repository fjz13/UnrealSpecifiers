# MinimalAPI

Type: bool
Feature: DllExport
Description: 指定该UInterface对象不导出到别的模块
Status: Done

可以参照UCLASS里的MinimalAPI的解释。简单来说UInterface对象，只是作为接口的辅助对象，因此本身并没有什么可值得暴露出来的函数。因此源码里的大部分UInterface对象都被标记成了MinimalAPI，以加快编译同时隔绝别的模块使用。

```cpp
UINTERFACE(MinimalAPI, BlueprintType)
class USoundLibraryProviderInterface : public UInterface
{
	GENERATED_BODY()
};
```