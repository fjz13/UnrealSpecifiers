# NoEditInline

Usage: UPROPERTY
Feature: Editor
Type: bool
Description: Object properties pointing to an UObject instance whos class is marked editinline will not show their properties inline in property windows. Useful for getting actor components to appear in the component tree but not inline in the root actor details panel.
LimitedType: UObject*
Status: NotWorked
Parent item: EditInline (EditInline.md)

对象引用默认就不能EditInline，因此也不需要额外再加上这个。除非Instanced之后？

结构属性默认就可以EditInline，加上这个后也没有作用，因此也不需要加上这个。

在源码中只找到：

```cpp
	UPROPERTY(VisibleAnywhere, Category = "Connection Point", meta = (NoEditInline))
	FLinearColor Color = FLinearColor::Black;
```