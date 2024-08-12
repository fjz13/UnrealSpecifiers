# IsCoreType

Type: bool
Feature: UHT
LimitedType: 只在NoExportTypes.h供UHT使用
Description: 指定该结构是核心类，UHT在用它的时候不需要前向声明。
Status: Done

"The 'IsCoreType' struct specifier is only valid in the NoExportTypes.h file”

指定该结构是核心类，UHT在用它的时候不需要前向声明。看代码是把struct用在参数或属性等被引用的时候。

```cpp
public override string? UhtStructProperty::GetForwardDeclarations()
		{
			if (ScriptStruct.IsCoreType)
			{
				return null;
			}

			if (TemplateWrapper != null)
			{
				StringBuilder builder = new();
				TemplateWrapper.AppendForwardDeclarations(builder);
				return builder.ToString();
			}

			return $"struct {ScriptStruct.SourceName};";
		}
```