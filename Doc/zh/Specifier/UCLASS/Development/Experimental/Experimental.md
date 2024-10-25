# Experimental

- **功能描述：**  标明该类是试验性版本，当前没有文档描述，之后有可能废弃掉。
- **引擎模块：** Development
- **元数据类型：** bool
- **作用机制：** 在Meta中添加[DevelopmentStatus](../../../../Meta/Development/DevelopmentStatus.md)，将类标记为Experimental
- **常用程度：★★★**

标明该类是试验性版本，当前没有文档描述，之后有可能废弃掉。

源码里的例子是Paper2D的类。这个标记会在类的元数据上加上{ "DevelopmentStatus", "Experimental" }。

## 示例代码：

```cpp
/*
(BlueprintType = true, DevelopmentStatus = Experimental, IncludePath = Class/Display/MyClass_Deprecated.h, IsBlueprintBase = true, ModuleRelativePath = Class/Display/MyClass_Deprecated.h)
*/
UCLASS(Blueprintable, Experimental)
class INSIDER_API UMyClass_Experimental :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyProperty;
	UFUNCTION(BlueprintCallable)
		void MyFunc() {}
};
```

## 示例效果：

![Untitled](Untitled.png)