# ToolTip

- **功能描述：** 在Meta里提供一个提示文本，覆盖代码注释里的文本
- **使用位置：** Any
- **引擎模块：** Development
- **元数据类型：** string="abc"
- **关联项：** [ShortTooltip](../ShortTooltip.md)
- **常用程度：** ★★★

## 测试代码：

```cpp
// This is a ToolTip out of Class.There're so so so so so so so many words I want to say, but here's too narrow.
UCLASS(BlueprintType, Blueprintable, meta = (ToolTip = "This is a ToolTip within Class. There're so so so so so so so many words I want to say, but here's too narrow."))
class INSIDER_API UMyClass_ToolTip :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ToolTip = "This is a ToolTip within Property.There're so so so so so so so many words I want to say, but here's too narrow."))
	float MyFloat_WithToolTip;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString MyString;

	UFUNCTION(BlueprintCallable, meta = (ToolTip = "This is a ToolTip within Function.There're so so so so so so so many words I want to say, but here's too narrow."))
	void MyFunc_WithToolTip() {}

	UFUNCTION(BlueprintCallable)
	void MyFunc() {}
};

// This is a ToolTip out of Class.There're so so so so so so so many words I want to say, but here's too narrow.
UCLASS(BlueprintType, Blueprintable, meta = (ToolTip = "This is a ToolTip within Class. There're so so so so so so so many words I want to say, but here's too narrow.", ShortToolTip = "This is a ShortToolTip within Class."))
class INSIDER_API UMyClass_WithAllToolTip :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ToolTip = "This is a ToolTip within Property."))
	float MyFloat_WithToolTip;

UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ToolTip = "This is a ToolTip within Property. There're so so so so so so so many words I want to say, but here's too narrow.\nThis is a new line.",ShortToolTip = "This is a ShortToolTip within Property."))
	float MyFloat_WithAllToolTip;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString MyString;

	UFUNCTION(BlueprintCallable, meta = (ToolTip = "This is a ToolTip within Function. There're so so so so so so so many words I want to say, but here's too narrow.",ShortToolTip = "This is a ShortToolTip within Function."))
	void MyFunc_WithAllToolTip() {}

	UFUNCTION(BlueprintCallable, meta = (ToolTip = "This is a ToolTip within Function."))
	void MyFunc_WithToolTip() {}
};

// This is a ToolTip out of Class.There're so so so so so so so many words I want to say, but here's too narrow.
UCLASS(BlueprintType, Blueprintable)
class INSIDER_API UMyClass_ToolTip_TypeA :public UObject
{
	GENERATED_BODY()
};

/**
*	This is a ToolTip out of Class.
*	There're so so so so so so so many words I want to say, but here's too narrow.
*	Please read this tooltip before you use this class. 
*/
UCLASS(BlueprintType, Blueprintable)
class INSIDER_API UMyClass_ToolTip_TypeB :public UObject
{
	GENERATED_BODY()
};
```

## 测试效果：

在选取父类时候的提示：

可以发现，如果提供了ToolTip，就会覆盖掉代码注释里的注释。同时也可以发现在下图中，提示的文本过长超过了选项框。这时如果提供了ShortToolTip，则会在父类选取器中显示ShortToolTip中的文本，从而简洁一点显示。在很多别的地方也同样应用这个规则，比如（该类型）变量上的提示，或者在选择变量类型的时候。

![1234](/1234.png)

## 原理代码：

在源码里有FField和UField，普通的属性是FField，而像UClass是继承于UField，因此要注意FField::GetToolTipText的bShortTooltip一直是false，而UField::GetToolTipText则会传true。

```cpp
FText FField::GetToolTipText(bool bShortTooltip) const
{
	bool bFoundShortTooltip = false;
	static const FName NAME_Tooltip(TEXT("Tooltip"));
	static const FName NAME_ShortTooltip(TEXT("ShortTooltip"));
	FText LocalizedToolTip;
	FString NativeToolTip;

	if (bShortTooltip)
	{
		NativeToolTip = GetMetaData(NAME_ShortTooltip);
		if (NativeToolTip.IsEmpty())
		{
			NativeToolTip = GetMetaData(NAME_Tooltip);
		}
		else
		{
			bFoundShortTooltip = true;
		}
	}
	else
	{
		NativeToolTip = GetMetaData(NAME_Tooltip);
	}

	const FString Namespace = bFoundShortTooltip ? TEXT("UObjectShortTooltips") : TEXT("UObjectToolTips");
	const FString Key = GetFullGroupName(false);
	if (!FText::FindText(Namespace, Key, /*OUT*/LocalizedToolTip, &NativeToolTip))
	{
		if (!NativeToolTip.IsEmpty())
		{
			static const FString DoxygenSee(TEXT("@see"));
			static const FString TooltipSee(TEXT("See:"));
			if (NativeToolTip.ReplaceInline(*DoxygenSee, *TooltipSee) > 0)
			{
				NativeToolTip.TrimEndInline();
			}
		}
		LocalizedToolTip = FText::FromString(NativeToolTip);
	}

	return LocalizedToolTip;
}

FText UField::GetToolTipText(bool bShortTooltip) const
{
	bool bFoundShortTooltip = false;
	static const FName NAME_Tooltip(TEXT("Tooltip"));
	static const FName NAME_ShortTooltip(TEXT("ShortTooltip"));
	FText LocalizedToolTip;
	FString NativeToolTip;
	
	if (bShortTooltip)
	{
		NativeToolTip = GetMetaData(NAME_ShortTooltip);
		if (NativeToolTip.IsEmpty())
		{
			NativeToolTip = GetMetaData(NAME_Tooltip);
		}
		else
		{
			bFoundShortTooltip = true;
		}
	}
	else
	{
		NativeToolTip = GetMetaData(NAME_Tooltip);
	}

	const FString Namespace = bFoundShortTooltip ? TEXT("UObjectShortTooltips") : TEXT("UObjectToolTips");
	const FString Key = GetFullGroupName(false);
	if ( !FText::FindText( Namespace, Key, /*OUT*/LocalizedToolTip, &NativeToolTip ) )
	{
		if (NativeToolTip.IsEmpty())
		{
			NativeToolTip = FName::NameToDisplayString(FDisplayNameHelper::Get(*this), false);
		}
		else if (!bShortTooltip && IsNative())
		{
			FormatNativeToolTip(NativeToolTip, true);
		}
		LocalizedToolTip = FText::FromString(NativeToolTip);
	}

	return LocalizedToolTip;
}

//在类型选择器中优先选择ShortTooltip
FText FClassPickerDefaults::GetDescription() const
{
	FText Result = LOCTEXT("NullClass", "(null class)");

	if (UClass* ItemClass = LoadClass<UObject>(NULL, *ClassName, NULL, LOAD_None, NULL))
	{
		Result = ItemClass->GetToolTipText(/*bShortTooltip=*/ true);
	}

	return Result;
}
```

但对于Property和Function，在显示的时候，都只会显示ToolTip，并不会应用ShortToolTip

变量和函数：

![55](/55.png)

![77](77.png)

其他需要注意的是，代码里注释的文本也会当作ToolTip。支持//和/**/这两种格式。如果在ToolTip中想换行，可以直接加/n就可以。

```cpp
/*
(BlueprintType = true, Comment = // This is a ToolTip out of Class.There're so so so so so so so many words I want to say, but here's too narrow.
, IncludePath = Any/ToolTip_Test.h, IsBlueprintBase = true, ModuleRelativePath = Any/ToolTip_Test.h, ToolTip = This is a ToolTip out of Class.There're so so so so so so so many words I want to say, but here's too narrow.)
*/

// This is a ToolTip out of Class.There're so so so so so so so many words I want to say, but here's too narrow.
UCLASS(BlueprintType, Blueprintable)
class INSIDER_API UMyClass_ToolTip_TypeA :public UObject
{
	GENERATED_BODY()
};

//[MyClass_ToolTip_TypeB	Class->Struct->Field->Object	/Script/Insider.MyClass_ToolTip_TypeB]
//(BlueprintType = true, Comment = /**
//*	This is a ToolTip out of Class.
//*	There're so so so so so so so many words I want to say, but here's too narrow.
//*	Please read this tooltip before you use this class. 
//*/, IncludePath = Any/ToolTip_Test.h, IsBlueprintBase = true, ModuleRelativePath = Any/ToolTip_Test.h, ToolTip = This is a ToolTip out of Class.
//There're so so so so so so so many words I want to say, but here's too narrow.
//Please read this tooltip before you use this class.)

/**
*	This is a ToolTip out of Class.
*	There're so so so so so so so many words I want to say, but here's too narrow.
*	Please read this tooltip before you use this class. 
*/
UCLASS(BlueprintType, Blueprintable)
class INSIDER_API UMyClass_ToolTip_TypeB :public UObject
{
	GENERATED_BODY()
};

UCLASS(BlueprintType, Blueprintable, meta = (ToolTip = "This is a ToolTip within Class. There're so so so so so so so many words I want to say, but here's too narrow.\nThis is a new line.", ShortToolTip = "This is a ShortToolTip within Class."))
```
