# BlueprintGetter

Type: string="abc"
Feature: Blueprint
Description: 采用一个自定义的get函数来读取。
如果没有设置BlueprintSetter或BlueprintReadWrite, 则会默认设置BlueprintReadOnly.
Example: BlueprintGetter=GetterFunctionName
EPropertyFlagsOperation: |=
EPropertyFlags: CPF_BlueprintReadOnly (../../Flags/EPropertyFlags/CPF_BlueprintReadOnly.md), CPF_BlueprintVisible (../../Flags/EPropertyFlags/CPF_BlueprintVisible.md)
MetaOperation: =XXX
Meta: BlueprintGetter (../../Meta/Meta/BlueprintGetter.md)
Status: Done

测试代码：

```cpp
public:
	//(BlueprintGetter = , Category = Blueprint, ModuleRelativePath = Property/MyProperty_Test.h)
	UFUNCTION(BlueprintGetter, Category = Blueprint)	//or BlueprintPure
		int32 MyInt_Getter()const { return MyInt_WithGetter * 2; }

	//(BlueprintSetter = , Category = Blueprint, ModuleRelativePath = Property/MyProperty_Test.h)
	UFUNCTION(BlueprintSetter, Category = Blueprint)	//or BlueprintCallable
		void MyInt_Setter(int NewValue) { MyInt_WithSetter = NewValue / 4; }
private:
	//(BlueprintGetter = MyInt_Getter, Category = Blueprint, ModuleRelativePath = Property/MyProperty_Test.h)
	//PropertyFlags:	CPF_BlueprintVisible | CPF_BlueprintReadOnly | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPrivate 
	UPROPERTY(BlueprintGetter = MyInt_Getter, Category = Blueprint)
		int32 MyInt_WithGetter = 123;

	//(BlueprintSetter = MyInt_Setter, Category = Blueprint, ModuleRelativePath = Property/MyProperty_Test.h)
	//PropertyFlags:	CPF_BlueprintVisible | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPrivate 
	UPROPERTY(BlueprintSetter = MyInt_Setter, Category = Blueprint)
		int32 MyInt_WithSetter = 123;
```

蓝图表现：

![Untitled](BlueprintGetter/Untitled.png)