# EditFixedSize

Description: 只适用于动态数组。这能防止用户通过虚幻编辑器属性窗口修改数组长度。只用在Array上，不允许用户修改数组大小
Type: bool
Feature: DetailsPanel, Editor
LimitedType: TArray<T>
EPropertyFlags: CPF_EditFixedSize (../../Flags/EPropertyFlags/CPF_EditFixedSize.md)
Status: Done

测试代码：

```cpp
UPROPERTY(EditAnywhere, Category = Array)
		TArray<int32> MyIntArray_Normal{1,2,3};

	UPROPERTY(EditAnywhere, EditFixedSize,Category = Array)
		TArray<int32> MyIntArray_FixedSize{1,2,3};
```

蓝图中的表现，前者可以动态再添加元素。后者不可。

![Untitled](EditFixedSize/Untitled.png)