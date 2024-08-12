# BlueprintAuthorityOnly

Type: bool
Feature: Blueprint, Network
LimitedType: Multicast Delegates
Description: 只能绑定为BlueprintAuthorityOnly的事件，让该多播委托只接受在服务端运行的事件
EPropertyFlagsOperation: |=
EPropertyFlags: CPF_BlueprintAuthorityOnly (../../Flags/EPropertyFlags/CPF_BlueprintAuthorityOnly.md)
Status: Done

测试代码：

```cpp
UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, BlueprintCallable)
		FMyDynamicMulticastDelegate_One MyMulticastDelegateAssignAndCall;

UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, BlueprintCallable, BlueprintAuthorityOnly)
		FMyDynamicMulticastDelegate_One MyMulticastDelegateAuthorityOnly;
```

蓝图中表现

![Untitled](BlueprintAuthorityOnly/Untitled.png)