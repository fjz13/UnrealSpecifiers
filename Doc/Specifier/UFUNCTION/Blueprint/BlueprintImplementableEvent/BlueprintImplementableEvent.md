# BlueprintImplementableEvent

功能描述: 指定一个函数调用点，可以在蓝图中重载实现。
元数据类型: bool
引擎模块: Blueprint
Status: Done
+=EFunctionFlags: FUNC_Event (../../Flags/EFunctionFlags/FUNC_Event.md), FUNC_Native (../../Flags/EFunctionFlags/FUNC_Native.md), FUNC_BlueprintEvent (../../Flags/EFunctionFlags/FUNC_BlueprintEvent.md)
常用程度: 5

指定一个函数调用点，可以在蓝图中重载实现。是一种方便的用来实现C++来调用蓝图函数的方式。

蓝图中如果没提供实现，调用的话相当于调用空函数。

BlueprintImplementableEvent也要配合BlueprintCallable使用，如果没加BlueprintCallable的话就只能在CPP里调用，在蓝图会发现找不到Call Function的节点。

测试代码：

```cpp
//FunctionFlags:	FUNC_Event | FUNC_Public | FUNC_BlueprintCallable | FUNC_BlueprintEvent 
UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
void MyFunc_ImplementableEvent();
```

效果展示：右键可添加自定义实现

![Untitled](BlueprintImplementableEvent/Untitled.png)

原理：

在C++里调用的时候，里面会FindFunctionChecked根据名字寻找。如果蓝图中有找到的话，则会调用。如果在蓝图中直接调用，则其实是会直接FindFunctionChecked查找，蓝图中有定义的话则会被直接找到。

```cpp
void AMyFunction_Default::MyFunc_ImplementableEvent()
{
		ProcessEvent(FindFunctionChecked(NAME_AMyFunction_Default_MyFunc_ImplementableEvent),NULL);
}
```