# NonTransactional

Type: bool
Feature: Editor
Description: 对该属性的改变操作，不会被包含进编辑器的Undo/redo命令中。
EPropertyFlags: CPF_NonTransactional (../../Flags/EPropertyFlags/CPF_NonTransactional.md)
Status: Done

指定该属性的改变，不能在编辑器中通过Ctrl+Z来撤销或Ctrl+Y来重做。在Actor或在BP的Class Defautls都可以生效。

测试代码：

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

蓝图表现：

![Untitled](NonTransactional/Untitled.png)