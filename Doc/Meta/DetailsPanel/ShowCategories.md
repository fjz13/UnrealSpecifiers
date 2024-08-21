# ShowCategories

- **功能描述：** 显示类别
- **使用位置：** UCLASS
- **元数据类型：** strings="a，b，c"
- **关联项：** [HideCategories](HideCategories.md)

在类上面标记的ShowCategories，并不会保存到meta中去，只是用来抹除基类HideCategories的设置。因此meta里的ShowCategories是没有用到的。

```cpp
//(BlueprintType = true, IncludePath = Class/Display/MyClass_HideCategories.h, IsBlueprintBase = true, ModuleRelativePath = Class/Display/MyClass_HideCategories.h)
UCLASS(Blueprintable, ShowCategories = MyGroup1)
class INSIDER_API UMyClass_ShowCategories :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Property_NotInGroup;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyGroup1)
		int Property_Group1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyGroup2 | MyGroup22")
		int Property_Group222;
};
```
