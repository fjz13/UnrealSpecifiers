# EditAnywhere

功能描述: 在默认值和实例的细节面板上均可编辑
元数据类型: bool
引擎模块: DetailsPanel, Editor
EPropertyFlagsOperation: |=
EPropertyFlags: CPF_Edit (../../Flags/EPropertyFlags/CPF_Edit.md)
Status: Done
常用程度: 5

在默认值和实例的细节面板上均可编辑。

示例代码：

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyProperty_Test :public UObject
{
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

	//PropertyFlags:	CPF_Edit | CPF_ZeroConstructor | CPF_DisableEditOnTemplate | CPF_EditConst | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic 
	UPROPERTY(VisibleInstanceOnly, Category = Edit)
		int32 MyInt_VisibleInstanceOnly = 123;
}
```

示例效果：

![Untitled](EditAnywhere/Untitled.png)

原理：

CPF_Edit在源码里有非常多的使用，决定了很多地方属性是否可以显示和编辑。有兴趣可以自己去搜搜CPF_Edit的使用。