# HideSelfPin

Usage: UFUNCTION
Feature: Blueprint
Type: bool
Description: 用在函数调用上，隐藏默认的SelfPin，也就是Target，导致该函数只能在OwnerClass内调用。
Example: HideSelfPin="true”
Status: Done
Group: PIn

用在函数调用上，隐藏默认的SelfPin，也就是Target，导致该函数只能在OwnerClass内调用。

注释里说通常与 DefaultToSelf 说明符共用。但是实际上在源码里没找到例子。

和HidePin以及InternalUseParam比较类似，不过后者可以隐藏其他参数，HideSelfPin只能隐藏SelfPin

逻辑代码：

可以看出SelfPin的bHidden 与否，受到一些情况的影响：

1. 如果是Static 函数（蓝图函数库里的函数，或者C++里的静态函数），因为默认不需要Target来调用，则默认就隐藏起SelfPin.
2. 如果函数上带有HideSelfPin标记，则默认也隐藏且不可在外部连接，导致该函数只能在本类内调用。
3. 如果函数是BlueprintPure函数，且当前是在OwnerClass内调用，则不需要显示SelfPin。
4. 在源码里只找到这一个地方的判断和应用。因此可以认为HidleSelfPin只隐藏Self，意思是只隐藏类成员函数被调用时候的This指针（就是Self，也就是Target)，但不会隐藏Static函数被调用时候的参数，哪怕这个参数被DefaultToSelf标识。被DefaultToSelf标志只意味着这个参数的默认值为外部调用环境的Self值，并不是指这个函数节点上的SelfPin，静态函数的SelfPin总是隐藏的。被DefaultToSelf标识的那个参数虽然值等于Self，但并不是SelfPin.

```cpp
bool UK2Node_CallFunction::CreatePinsForFunctionCall(const UFunction* Function)
{
//...
		if (bIsStaticFunc)
		{
			// For static methods, wire up the self to the CDO of the class if it's not us
			if (!bIsFunctionCompatibleWithSelf)
			{
				UClass* AuthoritativeClass = FunctionOwnerClass->GetAuthoritativeClass();
				SelfPin->DefaultObject = AuthoritativeClass->GetDefaultObject();
			}
		
			// Purity doesn't matter with a static function, we can always hide the self pin since we know how to call the method
			SelfPin->bHidden = true;
		}
		else
		{
			if (Function->GetBoolMetaData(FBlueprintMetadata::MD_HideSelfPin))
			{
				SelfPin->bHidden = true;
				SelfPin->bNotConnectable = true;
			}
			else
			{
				// Hide the self pin if the function is compatible with the blueprint class and pure (the !bIsConstFunc portion should be going away soon too hopefully)
				SelfPin->bHidden = (bIsFunctionCompatibleWithSelf && bIsPureFunc && !bIsConstFunc);
			}
		}
}
```

C++测试代码：

```cpp
UCLASS()
class INSIDER_API UMyFunctionLibrary_SelfPinTest :public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintPure,meta=(DefaultToSelf="myOwner",hidePin="myOwner"))
	static FString PrintProperty_HasDefaultToSelf_ButHide(UObject* myOwner,FName propertyName);

	UFUNCTION(BlueprintPure,meta=(DefaultToSelf="myOwner",HideSelfPin="true"))
	static FString PrintProperty_HasDefaultToSelf_AndHideSelf(UObject* myOwner,FName propertyName);

	UFUNCTION(BlueprintPure,meta=(DefaultToSelf="myOwner",InternalUseParam="myOwner"))
	static FString PrintProperty_HasDefaultToSelf_ButInternal(UObject* myOwner,FName propertyName);
};

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyFunction_HideSelfTest :public AActor
{
public:
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void MyFunc_Default(int value){}

	UFUNCTION(BlueprintCallable,meta=(HideSelfPin="true"))
	void MyFunc_HideSelfPin(int value){}
};
```

蓝图里测试效果：

从第一个图可以看到，HideSelfPin用在Static函数并无效果。而InternalUseParam

![Untitled](HideSelfPin/Untitled.png)

而对于类成员函数的测试结果可以看出：

- 在类内部调用的时候，self可以被隐藏起来，但都可以调用。二者的区别是，MyFunc_Default这个默认的版本，也可以接受同类型的AMyFunction_HideSelfTest 不同对象实例来调用。而MyFunc_HideSelfPin只能被当前的对象来调用。
- 而在左侧关卡蓝图中，通过一个AMyFunction_HideSelfTest 对象尝试调用这两个函数，可以发现MyFunc_Default可以调用，而MyFunc_HideSelfPin这个函数节点就无法被创建出来。就算用复制粘贴的方法硬创造出来，也因为失去了Self这个Target Pin而无法连接，从而无法调用。

![Untitled](HideSelfPin/Untitled%201.png)