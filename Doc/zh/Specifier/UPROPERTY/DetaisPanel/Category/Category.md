# Category

- **功能描述：** 指定属性的类别，使用 | 运算符定义嵌套类目。
- **元数据类型：** strings=“a|b|c”
- **引擎模块：** DetailsPanel, Editor
- **作用机制：** 在Meta中加入[Category](../../../../Meta/DetailsPanel/Category.md)
- **常用程度：★★★★★**

指定属性的类别，使用 | 运算符定义嵌套类目。

## 示例代码：

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyProperty_Test :public UObject
{
	//PropertyFlags:	CPF_Edit | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_SimpleDisplay | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
	UPROPERTY(EditAnywhere, SimpleDisplay, Category = Display)
		int32 MyInt_SimpleDisplay = 123;

	//PropertyFlags:	CPF_Edit | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_AdvancedDisplay | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = Display)
		int32 MyInt_AdvancedDisplay = 123;
public:
	//PropertyFlags:	CPF_Edit | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
	UPROPERTY(EditAnywhere, Category = Edit)
		int32 MyInt_EditAnywhere = 123;

	//PropertyFlags:	CPF_Edit | CPF_ZeroConstructor | CPF_DisableEditOnInstance | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
	UPROPERTY(EditDefaultsOnly, Category = Edit)
		int32 MyInt_EditDefaultsOnly = 123;

	//PropertyFlags:	CPF_Edit | CPF_ZeroConstructor | CPF_DisableEditOnTemplate | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
	UPROPERTY(EditInstanceOnly, Category = Edit)
		int32 MyInt_EditInstanceOnly = 123;

	//PropertyFlags:	CPF_Edit | CPF_ZeroConstructor | CPF_EditConst | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
	UPROPERTY(VisibleAnywhere, Category = Edit)
		int32 MyInt_VisibleAnywhere = 123;

	//PropertyFlags:	CPF_Edit | CPF_ZeroConstructor | CPF_DisableEditOnInstance | CPF_EditConst | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
	UPROPERTY(VisibleDefaultsOnly, Category = Edit)
		int32 MyInt_VisibleDefaultsOnly = 123;
}
```

## 示例效果：

![Untitled](Untitled.png)

## 原理：

比较简单，把值设置到meta里的Category，之后读取出来使用。