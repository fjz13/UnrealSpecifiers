# CallInEditor

Description: 可以在Actor的细节面板上作为一个按钮来调用该函数。
Type: bool
Feature: Editor
MetaOperation: =true
Meta: CallInEditor (../../Meta/Meta/CallInEditor.md)
Status: Done

可以在Actor的细节面板上作为一个按钮来调用该函数。注意这一般是处于Editor运行环境的。典型的例子是ASkyLight的Recapture按钮。

测试代码：

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyFunction_Default :public AActor
{
public:
	GENERATED_BODY()
public:
	UFUNCTION(CallInEditor)
	void MyFunc_CallInEditor(){}
};
```

蓝图展示：

![Untitled](CallInEditor/Untitled.png)