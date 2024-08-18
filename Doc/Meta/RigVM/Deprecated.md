# Deprecated

功能描述: 标识该FRigUnit为弃用状态，不在蓝图右键菜单中显示。
使用位置: USTRUCT
Feature: RigVM
引擎模块: RigVMStruct
元数据类型: bool
限制类型: FRigUnit类型上
Status: Done
常用程度: 2

标识该FRigUnit为弃用状态，不在蓝图右键菜单中显示。

但如果之前已经在蓝图中使用了，则还是可以继续使用。

注意这个时候要相应的实现GetUpgradeInfo()，否则会报错。

测试代码：

```cpp
USTRUCT(meta = (DisplayName = "MyRigDeprecated",Deprecated))
struct INSIDER_API FRigUnit_MyRigDeprecated : public FRigUnit
{
	GENERATED_BODY()

	RIGVM_METHOD()
	virtual void Execute() override;

	RIGVM_METHOD()
	virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;
public:
	UPROPERTY(meta = (Input))
	float MyFloat_Input = 123.f;

	UPROPERTY(meta = (Output))
	float MyFloat_Output = 123.f;
};
```

测试效果：

![Untitled](Deprecated/Untitled.png)

原理：

在构建菜单项的时候略过Deprecated的节点。

```cpp
void FRigVMEditorModule::GetTypeActions(URigVMBlueprint* RigVMBlueprint, FBlueprintActionDatabaseRegistrar& ActionRegistrar)
{
		// Add all rig units
	for(const FRigVMFunction& Function : Registry.GetFunctions())
	{
			// skip deprecated units
		if(Function.Struct->HasMetaData(FRigVMStruct::DeprecatedMetaName))
		{
			continue;
		}
	}
}
```