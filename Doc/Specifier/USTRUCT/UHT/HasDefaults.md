# HasDefaults

- **功能描述：**指定该结构的字段拥有默认值。这样如果本结构作为函数参数或返回值时候，函数则可以为其提供默认值。
- **元数据类型：**bool
- **引擎模块：**UHT
- **限制类型：**只在NoExportTypes.h供UHT使用
- **作用机制：**在FunctionFlags中加入[FUNC_HasDefaults](../../../Flags/EFunctionFlags/FUNC_HasDefaults.md)
- **常用程度：**0

指定该结构的字段拥有默认值。

不是指的是NoExportTypes.h的声明上是否写有默认值，而是指其真正的声明之处，其内部的属性都有初始值。这样如果本结构作为函数参数或返回值时候，函数则可以为其提供默认值。

NoExportTypes.h里的大部分结构都拥有该结构（88/135)，没有的是像FPackedXXX的。

## 原理：

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