# CallableWithoutWorldContext

Description: 让函数也可以脱离WorldContextObject而使用
Usage: UFUNCTION
Feature: Blueprint
Type: bool
Example: meta=(WorldContext="WorldContextObject", CallableWithoutWorldContext ) 
Status: Done
Parent item: WorldContext (WorldContext.md)

让函数也可以脱离WorldContextObject而使用。

CallableWithoutWorldContext 是配合WorldContext或DefaultToSelf来使用，这二者会使得一个函数会要求外部传入一个WorldContext对象才能调用。因此这种函数在没有实现GetWorld的Object子类里就不能调用。但有时某些函数又不一定必须得有WorldContextObject才能工作，比如PrintString或VisualLogger里的函数。

测试代码：

```cpp
UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
static FString MyFunc_HasWorldContextMeta(const UObject* WorldContextObject, FString name, FString value);

UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject",CallableWithoutWorldContext))
static FString MyFunc_CallableWithoutWorldContext(const UObject* WorldContextObject, FString name, FString value);

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyObject_NoGetWorld :public UObject
{
	GENERATED_BODY()
};
```

蓝图测试效果：

在UMyObject_NoGetWorld 的子类内，MyFunc_HasWorldContextMeta不能调用，因为其外部类必须提供WorldContextObject。而MyFunc_CallableWithoutWorldContext可以调用，可以接受不提供WorldContextObject。

![Untitled](CallableWithoutWorldContext/Untitled.png)

源码里典型的应用是：

```cpp
UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject", CallableWithoutWorldContext, Keywords = "log print", AdvancedDisplay = "2", DevelopmentOnly), Category="Development")
static ENGINE_API void PrintString(const UObject* WorldContextObject, const FString& InString = FString(TEXT("Hello")), bool bPrintToScreen = true, bool bPrintToLog = true, FLinearColor TextColor = FLinearColor(0.0f, 0.66f, 1.0f), float Duration = 2.f, const FName Key = NAME_None);
```