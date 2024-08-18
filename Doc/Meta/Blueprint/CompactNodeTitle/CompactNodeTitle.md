# CompactNodeTitle

功能描述: 使得函数的展示形式变成精简压缩模式，同时指定一个新的精简的名字
使用位置: UFUNCTION
Feature: Editor
引擎模块: Blueprint
元数据类型: string="abc"
Example: CompactNodeTitle="Name”
Status: Done
常用程度: 3

使得函数的展示形式变成精简压缩模式，同时指定一个新的精简的名字。注意到该模式下就会忽略DisplayName的数据。

测试代码：

```cpp
	UFUNCTION(BlueprintCallable, meta = (CompactNodeTitle = "MyCompact",DisplayName="AnotherName"))
	static int32 MyFunc_HasCompactNodeTitle(FString Name) {return 0;}

	UFUNCTION(BlueprintCallable, meta = ())
	static int32 MyFunc_NoCompactNodeTitle(FString Name) {return 0;}

	UFUNCTION(BlueprintPure, meta = (CompactNodeTitle = "MyPure",DisplayName="AnotherName"))
	static int32 MyPure_HasCompactNodeTitle(FString Name) {return 0;}

	UFUNCTION(BlueprintPure, meta = ())
	static int32 MyPure_NoCompactNodeTitle(FString Name) {return 0;}
```

蓝图效果：

显示效果明显发生了变化。同时我们在蓝图里定义的函数也可以通过这个细节面板上的设置变成压缩模式展示。

![Untitled](CompactNodeTitle/Untitled.png)

原理：

```cpp
bool UK2Node_CallFunction::ShouldDrawCompact(const UFunction* Function)
{
	return (Function != NULL) && Function->HasMetaData(FBlueprintMetadata::MD_CompactNodeTitle);
}

FString UK2Node_CallFunction::GetCompactNodeTitle(const UFunction* Function)
{
	static const FString ProgrammerMultiplicationSymbol = TEXT("*");
	static const FString CommonMultiplicationSymbol = TEXT("\xD7");

	static const FString ProgrammerDivisionSymbol = TEXT("/");
	static const FString CommonDivisionSymbol = TEXT("\xF7");

	static const FString ProgrammerConversionSymbol = TEXT("->");
	static const FString CommonConversionSymbol = TEXT("\x2022");

	const FString& OperatorTitle = Function->GetMetaData(FBlueprintMetadata::MD_CompactNodeTitle);
	if (!OperatorTitle.IsEmpty())
	{
		if (OperatorTitle == ProgrammerMultiplicationSymbol)
		{
			return CommonMultiplicationSymbol;
		}
		else if (OperatorTitle == ProgrammerDivisionSymbol)
		{
			return CommonDivisionSymbol;
		}
		else if (OperatorTitle == ProgrammerConversionSymbol)
		{
			return CommonConversionSymbol;
		}
		else
		{
			return OperatorTitle;
		}
	}
	
	return Function->GetName();
}
```