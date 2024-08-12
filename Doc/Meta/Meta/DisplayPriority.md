# DisplayPriority

Usage: UPROPERTY
Feature: Editor
Type: int32
Description: 指定本属性在细节面板的显示顺序优先级，越小的优先级越高。
Example: DisplayPriority="N”
Status: Done
Group: DetailsPanel

指定本属性在细节面板的显示顺序优先级，越小的优先级越高。

- 如果有DisplayAfter的设置，则DisplayAfter的优先级更高。
- 同样的限制得是在同Category里。

测试代码：

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

测试结果：

P4即使优先级比较低，但因为DisplayAfter也仍然排在了P1之后。

![Untitled](DisplayPriority/Untitled.png)

原理：

排序的逻辑在这个函数内，自行查看就好。一个简单的插入排序算法。

```cpp
void PropertyEditorHelpers::OrderPropertiesFromMetadata(TArray<FProperty*>& Properties)
{}
```