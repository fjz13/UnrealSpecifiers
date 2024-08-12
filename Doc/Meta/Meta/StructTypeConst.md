# StructTypeConst

Usage: UPROPERTY
Feature: Blueprint
Type: bool
Description: 在使用BaseStruct的FInstancedStruct属性上忽略BaseStruct指向的结构基类。
LimitedType: FInstancedStruct
Status: Linked
Group: TypePicker
Parent item: BaseStruct (BaseStruct.md)

指定FInstancedStruct属性的类型不能被选择。

用处往往是在之后交给用户在代码里初始化。

原理：

如果有该标记，就禁用编辑的控件。

```cpp
void FInstancedStructDetails::CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
		static const FName NAME_StructTypeConst = "StructTypeConst";
		const bool bEnableStructSelection = !StructProperty->HasMetaData(NAME_StructTypeConst);
			
			
			.IsEnabled(bEnableStructSelection)

}
```