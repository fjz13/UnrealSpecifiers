# HasDefaults

Description: 指定该结构的字段拥有默认值。这样如果作为函数参数或返回值时候，则可以提供默认值
Type: bool
Feature: UHT
LimitedType: 只在NoExportTypes.h供UHT使用
Status: Done
EFunctionFlags: FUNC_HasDefaults (../../Flags/EFunctionFlags/FUNC_HasDefaults.md)

"The 'HasDefaults' struct specifier is only valid in the NoExportTypes.h file”

如果是一个class中的函数且参数用到了结构，如果该结构拥有HasDefaults，则会造成EFunctionFlags.HasDefaults

```cpp
// The following code is only performed on functions in a class.
if (Outer is UhtClass)
{
	foreach (UhtType type in Children)
	{
		if (type is UhtProperty property)
		{
			if (property.PropertyFlags.HasExactFlags(EPropertyFlags.OutParm | EPropertyFlags.ReturnParm, EPropertyFlags.OutParm))
			{
				FunctionFlags |= EFunctionFlags.HasOutParms;
			}
			if (property is UhtStructProperty structProperty)
			{
				if (structProperty.ScriptStruct.HasDefaults)
				{
					FunctionFlags |= EFunctionFlags.HasDefaults;
				}
			}
		}
	}
}
```

NoExportTypes.h里的大部分结构都拥有该结构（88/135)，没有的是像FPackedXXX的，这些结构的属性在c++定义里没写默认值。