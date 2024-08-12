# BlueprintAssignable

Description: 在蓝图中可以为这个多播委托绑定事件
Type: bool
Feature: Blueprint
LimitedType: Multicast Delegates
EPropertyFlagsOperation: |=
EPropertyFlags: CPF_BlueprintAssignable (../../Flags/EPropertyFlags/CPF_BlueprintAssignable.md)
Status: Done

C++的测试代码：

```cpp
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMyDynamicMulticastDelegate_One, int32, Value);

UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, BlueprintCallable)
	FMyDynamicMulticastDelegate_One MyMulticastDelegateAssignAndCall;

UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintCallable)
	FMyDynamicMulticastDelegate_One MyMulticastDelegateCall;

UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable)
	FMyDynamicMulticastDelegate_One MyMulticastDelegateAssign;

UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FMyDynamicMulticastDelegate_One MyMulticastDelegate;

```

蓝图中的表现：

![Untitled](BlueprintAssignable/Untitled.png)

因此一般建议二者标记都加上：

![Untitled](BlueprintAssignable/Untitled%201.png)