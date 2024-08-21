# DisallowedStructs

- **功能描述：** 只在SmartObject模块中应用，用以在类选择器中排除掉某个类以及子类。
- **使用位置：** UPROPERTY
- **引擎模块：** TypePicker
- **元数据类型：** string="abc"
- **常用程度：** ★

只在SmartObject模块中应用，用以在类选择器中排除掉某个类以及子类。

## 源码：

```cpp
UPROPERTY(EditDefaultsOnly, Category = "SmartObject", meta=(DisallowedStructs="/Script/SmartObjectsModule.SmartObjectSlotAnnotation"))
TArray<FSmartObjectDefinitionDataProxy> DefinitionData;
```
