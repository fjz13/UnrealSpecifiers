# NonTransactional

- **功能描述：**对该属性的改变操作，不会被包含进编辑器的Undo/Redo命令中。

- **元数据类型：**bool
- **引擎模块：**Editor
- **作用机制：**在PropertyFlags中加入[CPF_NonTransactional](../../../../Flags/EPropertyFlags/CPF_NonTransactional.md)
- **常用程度：**★★

指定该属性的改变，不能在编辑器中通过Ctrl+Z来撤销或Ctrl+Y来重做。在Actor或在BP的Class Defautls都可以生效。

## 测试代码：

```jsx
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyProperty_Transaction :public AActor
{
public:
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,NonTransactional,Category = Transaction)
		int32 MyInt_NonTransactional= 123;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = Transaction)
		int32 MyInt_Transactional = 123;
};
```

## 蓝图表现：

在MyInt_Transactional 上可以撤销之前的输入，而MyInt_NonTransactional上的输入无法用Ctrl+Z撤销。

![Untitled](Untitled.png)