# StructTypeConst

- **功能描述：** 指定FInstancedStruct属性的类型不能在编辑器被选择。
- **使用位置：** UPROPERTY
- **引擎模块：** TypePicker
- **元数据类型：** bool
- **限制类型：** FInstancedStruct
- **关联项：** [BaseStruct](BaseStruct/BaseStruct.md)
- **常用程度：** ★

指定FInstancedStruct属性的类型不能在编辑器被选择。

用处往往是在之后交给用户在代码里初始化。

## 原理：

如果有该标记，就禁用编辑的控件。

```cpp
void FInstancedStructDetails::CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
		static const FName NAME_StructTypeConst = "StructTypeConst";
		const bool bEnableStructSelection = !StructProperty->HasMetaData(NAME_StructTypeConst);


			.IsEnabled(bEnableStructSelection)

}
```