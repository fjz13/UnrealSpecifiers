# NonPIEDuplicateTransient

Type: bool
Feature: Serialization
Description: 属性将在复制中被重设为默认值，除非其被复制用于PIE会话。在PIE里复制的时候，不复制
EPropertyFlags: CPF_NonPIEDuplicateTransient (../../Flags/EPropertyFlags/CPF_NonPIEDuplicateTransient.md)
Status: Done

在文本导出的的时候，在不是PIE里的复制的时候，不序列化该属性。

```cpp
bool FProperty::ShouldPort( uint32 PortFlags/*=0*/ ) const
{
// if we're not copying for PIE and NonPIETransient is set, don't export
	if (!(PortFlags & PPF_DuplicateForPIE) && HasAnyPropertyFlags(CPF_NonPIEDuplicateTransient))
	{
		return false;
	}
}
```

在二进制序列化的时候：

只有在PPF_Duplicate生效的时候，（DuplicateObject?或者资产复制），才会跳过该属性。但是在PIE的时候，又要继续序列化。

```cpp
bool FProperty::ShouldSerializeValue(FArchive& Ar) const
{
// Skip properties marked NonPIEDuplicateTransient when duplicating, but not when we're duplicating for PIE
	if ((PropertyFlags & CPF_NonPIEDuplicateTransient) && !(Ar.GetPortFlags() & PPF_DuplicateForPIE) && (Ar.GetPortFlags() & PPF_Duplicate))
	{
		return false;
	}
}
```

在对资产进行Duplidate的时候，发生DuplicateAsset然后DuplicateObject，这个时候PortFlags=PPF_Duplicate，然后会触发ShouldSerializeValue进行判断。这个时候会跳过该属性

可以看到NonPIEDuplicateTransient并不会被复制

![Untitled](NonPIEDuplicateTransient/Untitled.png)

在点击PIE的时候，可以看到NonPIEDuplicateTransient这个时候却是会复制值过去了。这是因为这个时候PortFlags=PPF_DuplicateForPIE&PPF_Duplicate

![Untitled](NonPIEDuplicateTransient/Untitled%201.png)

结论是用于一些Cache数据，在复制的时候并不需要序列化复制，这样可以阻止两个不同的Actor采用同一份计算后的临时数据。但是又可以在PIE的时候，让Actor各自采用自己的一份数据，因为PIE的时候，本质就是把当前的编辑World里Actor复制一份到PIE的世界里，会触发Actor的复制。