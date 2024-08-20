# BlueprintReadOnly

- **功能描述：**此属性可由蓝图读取，但不能被修改。
- **元数据类型：**bool
- **引擎模块：**Blueprint
- **作用机制：**在PropertyFlags中加入[CPF_BlueprintVisible](../../../../Flags/EPropertyFlags/CPF_BlueprintVisible.md), [CPF_BlueprintReadOnly](../../../../Flags/EPropertyFlags/CPF_BlueprintReadOnly.md)
- **常用程度：**★★★★★

此属性可由蓝图读取，但不能被修改。此说明符与 BlueprintReadWrite 说明符不兼容。

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

指定蓝图中只读：

![Untitled](Untitled.png)

## 原理：

有CPF_BlueprintVisible 就可以Get

加上CPF_BlueprintReadOnly 后就不能修改。

```cpp
EPropertyAccessResultFlags PropertyAccessUtil::CanGetPropertyValue(const FProperty* InProp)
{
	if (!InProp->HasAnyPropertyFlags(CPF_Edit | CPF_BlueprintVisible | CPF_BlueprintAssignable))
	{
		return EPropertyAccessResultFlags::PermissionDenied | EPropertyAccessResultFlags::AccessProtected;
	}

	return EPropertyAccessResultFlags::Success;
}

FBlueprintEditorUtils::EPropertyWritableState FBlueprintEditorUtils::IsPropertyWritableInBlueprint(const UBlueprint* Blueprint, const FProperty* Property)
{
	if (Property)
	{
		if (!Property->HasAnyPropertyFlags(CPF_BlueprintVisible))
		{
			return EPropertyWritableState::NotBlueprintVisible;
		}
		if (Property->HasAnyPropertyFlags(CPF_BlueprintReadOnly))
		{
			return EPropertyWritableState::BlueprintReadOnly;
		}
		if (Property->GetBoolMetaData(FBlueprintMetadata::MD_Private))
		{
			const UClass* OwningClass = Property->GetOwnerChecked<UClass>();
			if (OwningClass->ClassGeneratedBy.Get() != Blueprint)
			{
				return EPropertyWritableState::Private;
			}
		}
	}
	return EPropertyWritableState::Writable;
}
```