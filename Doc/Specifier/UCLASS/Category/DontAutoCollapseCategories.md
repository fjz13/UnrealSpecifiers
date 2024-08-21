# DontAutoCollapseCategories

- **功能描述：**  使列出的类别的继承自父类的AutoCollapseCategories说明符无效。
- **引擎模块：** Category
- **元数据类型：** strings="a，b，c"
- **作用机制：** 在Meta中去除[AutoCollapseCategories](../../../Meta/DetailsPanel/AutoCollapseCategories.md)
- **关联项：** [AutoCollapseCategories](AutoCollapseCategories/AutoCollapseCategories.md)
- **常用程度：★**

根据代码，只是简单的移除AutoCollapseCategories，和AutoExpandCategories的区别就是不会自动加一个展开。在源码里搜了一下，并没有使用到。而且当前的源码实现有bug，做不到去除。

```cpp
case EClassMetadataSpecifier::AutoExpandCategories:

	FHeaderParser::RequireSpecifierValue(*this, PropSpecifier);

	for (FString& Value : PropSpecifier.Values)
	{
		AutoCollapseCategories.RemoveSwap(Value);
		AutoExpandCategories.AddUnique(MoveTemp(Value));
	}
	break;

case EClassMetadataSpecifier::AutoCollapseCategories:

	FHeaderParser::RequireSpecifierValue(*this, PropSpecifier);

	for (FString& Value : PropSpecifier.Values)
	{
		AutoExpandCategories.RemoveSwap(Value);
		AutoCollapseCategories.AddUnique(MoveTemp(Value));
	}
	break;
case EClassMetadataSpecifier::DontAutoCollapseCategories:

	FHeaderParser::RequireSpecifierValue(*this, PropSpecifier);

	for (const FString& Value : PropSpecifier.Values)
	{
			AutoCollapseCategories.RemoveSwap(Value);//当前AutoCollapseCategories的值还是空的。去除是没有用的
	}
	break;

改动：
FUnrealClassDefinitionInfo::MergeClassCategories()放最后：
// Merge DontAutoCollapseCategories and AutoCollapseCategories
	for (const FString& Value : DontAutoCollapseCategories)
	{
		AutoCollapseCategories.RemoveSwap(Value);
	}
	DontAutoCollapseCategories.Empty();

改为：
case EClassMetadataSpecifier::DontAutoCollapseCategories:

			FHeaderParser::RequireSpecifierValue(*this, PropSpecifier);

			for (FString& Value : PropSpecifier.Values)
			{
				DontAutoCollapseCategories.AddUnique(MoveTemp(Value));
				//AutoCollapseCategories.RemoveSwap(Value);
			}
			break;
```