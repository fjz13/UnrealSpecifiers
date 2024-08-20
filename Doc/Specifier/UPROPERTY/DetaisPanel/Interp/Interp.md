# Interp

- **功能描述：**指定该属性值可暴露到时间轴里编辑，在平常的Timeline或UMG的动画里使用。

- **元数据类型：**bool
- **引擎模块：**Sequencer
- **作用机制：**在PropertyFlags中加入[CPF_Edit](../../../../Flags/EPropertyFlags/CPF_Edit.md), [CPF_BlueprintVisible](../../../../Flags/EPropertyFlags/CPF_BlueprintVisible.md), [CPF_Interp](../../../../Flags/EPropertyFlags/CPF_Interp.md)
- **常用程度：**★★★

该属性可以暴露到时间轴里，一般用来编辑动画。

## 示例代码：

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyProperty_Interp :public AActor
{
public:
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = Animation)
		FVector MyInterpVector;
};
```

## 示例效果：

影响的是属性上的该标志

![Untitled](Untitled.png)

从而可以在Sequencer里对该属性添加Track

![Untitled](Untitled%201.png)