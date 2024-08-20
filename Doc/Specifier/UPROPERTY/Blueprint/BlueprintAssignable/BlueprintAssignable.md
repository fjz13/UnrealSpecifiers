# BlueprintAssignable

- **功能描述：**在蓝图中可以为这个多播委托绑定事件

- **元数据类型：**bool
- **引擎模块：**Blueprint
- **限制类型：**Multicast Delegates
- **作用机制：**在PropertyFlags中加入[CPF_BlueprintAssignable](../../../../Flags/EPropertyFlags/CPF_BlueprintAssignable.md)
- **常用程度：**★★★

## C++的测试代码：

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

## 蓝图中的表现：

![Untitled](Untitled.png)

因此一般建议二者标记都加上：

![Untitled](Untitled%201.png)