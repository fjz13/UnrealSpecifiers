# BlueprintNativeEvent

Type: bool
Feature: Blueprint
Description: 可以在蓝图总重载实现，当时也在C++中提供一个默认实现。
Status: Done
+=EFunctionFlags: FUNC_Event (../../Flags/EFunctionFlags/FUNC_Event.md), FUNC_BlueprintEvent (../../Flags/EFunctionFlags/FUNC_BlueprintEvent.md)

此函数旨在被 蓝图 覆盖掉，但是也具有默认原生实现。用于声明名称与主函数相同的附加函数，但是末尾添加了_Implementation，是写入代码的位置。如果未找到任何蓝图覆盖，该自动生成的代码将调用“_Implementation”方法。定义一个原生事件以供蓝图，但是也在C++中提供 [FunctionName]_Implementation的函数实现。一般用在OnXXX之类的函数上，在C++提供实现，但是万一蓝图需要重载自定义，也可以支持。
这样如果蓝图中没有重载的时候，就可以默认调用C++中默认实现版本。
没加BlueprintCallable的话就只能在CPP里调用

测试代码：

```cpp
//			FunctionFlags:	FUNC_Native | FUNC_Event | FUNC_Public | FUNC_BlueprintEvent 
	UFUNCTION(BlueprintNativeEvent)
	void MyFunc_NativeEvent();

void AMyFunction_Default::MyFunc_NativeEvent_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, "MyFunc_NativeEvent_Implementation");
}
```

效果展示：

![Untitled](BlueprintNativeEvent/Untitled.png)

原理：在调用MyFunc_NativeEvent的时候，内部FindFunctionChecked会根据名字查找，如果在蓝图中有定义，则会找到蓝图中的实现版本。否则的话，则会找到execMyFunc_NativeEvent这个实现版本，从而调用MyFunc_NativeEvent_Implementation。

```cpp
DEFINE_FUNCTION(AMyFunction_Default::execMyFunc_NativeEvent)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->MyFunc_NativeEvent_Implementation();
	P_NATIVE_END;
}

void AMyFunction_Default::MyFunc_NativeEvent()
{
	ProcessEvent(FindFunctionChecked(NAME_AMyFunction_Default_MyFunc_NativeEvent),NULL);
}
```