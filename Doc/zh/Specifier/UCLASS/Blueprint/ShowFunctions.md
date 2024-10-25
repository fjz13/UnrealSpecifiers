# ShowFunctions

- **功能描述：**  在子类的函数覆盖列表里重新打开某些函数。
- **引擎模块：** Blueprint
- **元数据类型：** strings=(abc，"d|e"，"x|y|z")
- **作用机制：** 在Meta中去除[HideFunctions](../../../Meta/Blueprint/HideFunctions.md)
- **关联项：** [HideFunctions](HideFunctions/HideFunctions.md)
- **常用程度：★★**

在子类的函数覆盖列表里重新打开某些函数。

测试代码和效果图见HideFunctions。

## 原理：

UHT中的代码，可见ShowFunctions的作用就是去除掉之前设置的HideFunctions。

```cpp
private void MergeCategories()
{
	MergeShowCategories();

	// Merge ShowFunctions and HideFunctions
	AppendStringListMetaData(SuperClass, UhtNames.HideFunctions, HideFunctions);
	foreach (string value in ShowFunctions)
	{
		HideFunctions.RemoveSwap(value);
	}
	ShowFunctions.Clear();
}
```