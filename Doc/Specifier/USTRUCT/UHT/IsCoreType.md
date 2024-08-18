# IsCoreType

功能描述: 指定该结构是核心类，UHT在用它的时候不需要前向声明。
元数据类型: bool
引擎模块: UHT
限制类型: 只在NoExportTypes.h供UHT使用
Status: Done
常用程度: 0

指定该结构是核心类，UHT在用它的时候不需要前向声明。

原理：

看UHT源码是把struct用在参数或属性等被引用的时候。

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