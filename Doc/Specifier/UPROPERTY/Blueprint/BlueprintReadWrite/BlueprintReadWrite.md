# BlueprintReadWrite

- **功能描述：**可从蓝图读取或写入此属性。

- **元数据类型：**bool
- **引擎模块：**Blueprint
- **作用机制：**在PropertyFlags中加入[CPF_BlueprintVisible](../../../../Flags/EPropertyFlags/CPF_BlueprintVisible.md)
- **常用程度：**★★★★★

可从蓝图读取或写入此属性。

此说明符与 BlueprintReadOnly 说明符不兼容。

## 示例代码：

```cpp
public:
	//PropertyFlags:	CPF_BlueprintVisible | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic 
	UPROPERTY(BlueprintReadWrite, Category = Blueprint)
		int32 MyInt_ReadWrite = 123;
	//PropertyFlags:	CPF_BlueprintVisible | CPF_BlueprintReadOnly | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic 
	UPROPERTY(BlueprintReadOnly, Category = Blueprint)
		int32 MyInt_ReadOnly = 123;
```

## 示例效果：

蓝图中可读写：

![Untitled](Untitled.png)

## 原理：

如果有CPF_Edit | CPF_BlueprintVisible | CPF_BlueprintAssignable之一，则可以Get属性。

```cpp
EPropertyAccessResultFlags PropertyAccessUtil::CanGetPropertyValue(const FProperty* InProp)
{
	if (!InProp->HasAnyPropertyFlags(CPF_Edit | CPF_BlueprintVisible | CPF_BlueprintAssignable))
	{
		return EPropertyAccessResultFlags::PermissionDenied | EPropertyAccessResultFlags::AccessProtected;
	}

	return EPropertyAccessResultFlags::Success;
}

```