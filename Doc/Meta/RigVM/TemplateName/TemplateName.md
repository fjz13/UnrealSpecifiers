# TemplateName

- **功能描述：** 指定该FRigUnit成为一个泛型模板节点。
- **使用位置：** USTRUCT
- **引擎模块：** RigVMStruct
- **元数据类型：** string="abc"
- **限制类型：** FRigUnit
- **常用程度：** ★★★

指定该FRigUnit成为一个泛型模板节点。

不同的FRigUnit在设置到同一个TemplateName 之后，会分析其Input和Output的属性的整个函数签名，最后分析出哪些属性是泛型引脚（即同名不同类型的属性）。在调用的时候，输入的是TemplateNode，即TemplateName 形成的节点。然后再手动连接引脚来确定最后的函数类型，从而最后再完全确定应该实际应用到哪一个FRigUnit节点。

这个功能在实现一些逻辑相同，但是参数类型稍微不同的时候，会比较便利。往往FRigUnit_MyTemplate_Float和FRigUnit_MyTemplate_Int会继承于一个基类（但不是强制），在里面实现公用的逻辑或属性。

## 测试代码：

```cpp
USTRUCT(meta = (DisplayName = "Set My float", TemplateName = "SetMyTemplate"))
struct INSIDER_API FRigUnit_MyTemplate_Float : public FRigUnit
{
	GENERATED_BODY()

	RIGVM_METHOD()
		virtual void Execute() override;
public:
	UPROPERTY(meta = (Input))
	float MyValue;

	UPROPERTY(meta = (Output))
	FString MyStringResult;
};

USTRUCT(meta = (DisplayName = "Set My int", TemplateName = "SetMyTemplate"))
struct INSIDER_API FRigUnit_MyTemplate_Int : public FRigUnit
{
	GENERATED_BODY()

	RIGVM_METHOD()
		virtual void Execute() override;
public:
	UPROPERTY(meta = (Input))
	int32 MyValue;

	UPROPERTY(meta = (Output))
	FString MyStringResult;
};
```

## 测试效果：

可见一开始的节点是SetMyTemplate，然后根据引脚类型的不同，再实际Resolve成FRigUnit_MyTemplate_Float 或者是FRigUnit_MyTemplate_Int 。因为我没有实现SetMyString，所以FString类型的是不能连接到引脚的。

![RigVM_Template](RigVM_Template.gif)

## 原理：

源码里涉及到这一块的代码比较多。大致逻辑是FRigUnit在初始化的时候注册到FRigVMRegistry里，如果有TempalteName则创建一个FRigTemplate，之后蓝图右键创建的时候实际创建的是URigTemplateNode，然后再由FRigDispatch来分发到实际的最终节点。

```cpp
void FRigVMRegistry::Register(const TCHAR* InName, FRigVMFunctionPtr InFunctionPtr, UScriptStruct* InStruct, const TArray<FRigVMFunctionArgument>& InArguments)
{
	FString TemplateMetadata;
	if (InStruct->GetStringMetaDataHierarchical(TemplateNameMetaName, &TemplateMetadata))
	{
	}
}
```
