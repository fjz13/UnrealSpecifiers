# DisplayPriority

- **功能描述：** 指定本属性在细节面板的显示顺序优先级，越小的优先级越高。
- **使用位置：** UPROPERTY
- **引擎模块：** DetailsPanel
- **元数据类型：** int32
- **常用程度：** ★★★

指定本属性在细节面板的显示顺序优先级，越小的优先级越高。

- 如果有DisplayAfter的设置，则DisplayAfter的优先级更高。
- 同样的限制得是在同Category里。

## 测试代码：

```cpp
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PriorityTest, meta = (DisplayPriority = 3))
	int32 MyInt_P3 = 123;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PriorityTest, meta = (DisplayPriority = 1))
	int32 MyInt_P1 = 123;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PriorityTest, meta = (DisplayPriority = 2))
	int32 MyInt_P2 = 123;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PriorityTest, meta = (DisplayPriority = 4,DisplayAfter="MyInt_P1"))
	int32 MyInt_P4 = 123;
```

## 测试结果：

P4即使优先级比较低，但因为DisplayAfter也仍然排在了P1之后。

![Untitled](Untitled.png)

## 原理：

排序的逻辑在这个函数内，自行查看就好。一个简单的插入排序算法。

```cpp
void PropertyEditorHelpers::OrderPropertiesFromMetadata(TArray<FProperty*>& Properties)
{}
```
