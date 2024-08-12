# ShowFunctions

Type: strings=(abc，"d|e"，"x|y|z")
Feature: DetailsPanel
Description: 在属性查看器中显示列出的类别中的所有函数。
Example: ShowFunctions=(FuncName1, FuncName1, ...)
MetaOperation: -=
Meta: HideFunctions (../../Meta/Meta/HideFunctions.md)
Status: Not started
Parent item: HideFunctions (HideFunctions.md)

```cpp
case EClassMetadataSpecifier::ShowFunctions:
	FHeaderParser::RequireSpecifierValue(PropSpecifier);
	for (const FString& Value : PropSpecifier.Values)
	{
		HideFunctions.RemoveSwap(Value);
		//FJZ: fix this
		ShowFunctions.AddUnique(Value);
		//FJZ: fix this
	}
	break;
```