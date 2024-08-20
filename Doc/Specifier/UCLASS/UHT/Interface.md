# Interface

- **功能描述：**标识这个Class是个Interface。
- **引擎模块：**UHT
- **元数据类型：**bool
- **作用机制：**在ClassFlags中添加[CLASS_Interface](../../../Flags/EClassFlags/CLASS_Interface.md)
- **常用程度：**0

标识这个Class是个Interface。

只用在NoExportTypes.h中，我们自己的UInterface不需要手动设置。

是UHT在为UInterface生成的时候，设置在.generated.h里的。

## 源码例子：

```cpp
UCLASS(abstract, noexport, intrinsic, interface, Config = Engine)
class UInterface : public UObject
{}
```

## 原理：

```cpp
bool FKismetEditorUtilities::IsClassABlueprintInterface(const UClass* Class)
{
	if (Class->HasAnyClassFlags(CLASS_Interface) && !Class->HasAnyClassFlags(CLASS_NewerVersionExists))
	{
		return true;
	}
	return false;
}
```