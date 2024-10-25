# ShowFunctions

- **Function description:** Reopen certain functions within the subclass function override list.
- **Engine module:** Blueprint
- **Metadata type:** strings =( abc , "d|e", "x|y|z")
- **Mechanism of action:** Remove [HideFunctions](../../../Meta/Blueprint/HideFunctions.md) within the Meta class
- **Related items:** [HideFunctions](HideFunctions/HideFunctions.md)
- **Frequency:** ★★

Reopen certain functions within the subclass function override list.

Refer to HideFunctions for test code and visual results.

## Principle:

In the UHT code, it is evident that the purpose of ShowFunctions is to undo the effects of previously set HideFunctions.

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