# AdvancedClassDisplay

- **功能描述：**  把该类下的所有属性都默认显示在高级目录下
- **引擎模块：** Category
- **元数据类型：** bool
- **作用机制：** 在Meta增加[AdvancedClassDisplay](../../../../Meta/DetailsPanel/AdvancedClassDisplay.md)
- **常用程度：★★★★**

让这个类的所有属性显示在本身类的Detail面板的“高级”栏目下显示。

但是可以通过在单个属性上使用SimpleDisplay来重载掉。在搜索了一番源码后，发现使用AdvancedClassDisplay的只有3个Actor，且这3个Actor里都没有再定义属性。

## 示例代码：

```cpp
UCLASS(Blueprintable,AdvancedClassDisplay)
class INSIDER_API UMyClass_AdvancedClassDisplay :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyProperty;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,SimpleDisplay)
		int32 MyProperty_Simple;
};

UCLASS(Blueprintable)
class INSIDER_API UMyClass_NoAdvancedClassDisplay :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyProperty;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay)
		int32 MyProperty_Simple;
};
```

## 示例效果：

MyProperty_Simple即使在AdvancedClassDisplay的类中也依然是简单的显示。

![Untitled](Untitled.png)

## 原理：

```cpp
// Property is advanced if it is marked advanced or the entire class is advanced and the property not marked as simple
static const FName Name_AdvancedClassDisplay("AdvancedClassDisplay");
bool bAdvanced = Property.IsValid() ? ( Property->HasAnyPropertyFlags(CPF_AdvancedDisplay) || ( !Property->HasAnyPropertyFlags( CPF_SimpleDisplay ) && Property->GetOwnerClass() && Property->GetOwnerClass()->GetBoolMetaData(Name_AdvancedClassDisplay) ) ) : false;
```