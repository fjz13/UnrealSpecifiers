# Private

Usage: UCLASS
Feature: Editor
Type: bool
Description: 标识该UMaterialExpression为私有节点，当前在材质蓝图右键菜单中隐藏。
LimitedType: UMaterialExpression子类
Status: Done
Group: Material

标识该UMaterialExpression为私有节点，当前在材质蓝图右键菜单中隐藏。

在MaterialX模块中使用，目前是把里面的Expression暂时先都隐藏起来。

源码例子：

```cpp
UCLASS()
class UMyMaterialExpression_NotPrivate : public UMaterialExpression
{}；

UCLASS(meta=(Private))
class UMyMaterialExpression_Private : public UMaterialExpression
{}；
```

测试效果：

材质蓝图里只能调用UMyMaterialExpression_NotPrivate 。

![Untitled](Private/Untitled.png)

原理：

在遍历所有可用FMaterialExpression的时候，如果有Private则略过。

```cpp
static TAutoConsoleVariable<int32> CVarMaterialEnableNewHLSLGenerator(
	TEXT("r.MaterialEnableNewHLSLGenerator"),
	0,
	TEXT("Enables the new (WIP) material HLSL generator.\n")
	TEXT("0 - Don't allow\n")
	TEXT("1 - Allow if enabled by material\n")
	TEXT("2 - Force all materials to use new generator\n"),
	ECVF_RenderThreadSafe | ECVF_ReadOnly);

void MaterialExpressionClasses::InitMaterialExpressionClasses()
{
		static const auto CVarMaterialEnableNewHLSLGenerator = IConsoleManager::Get().FindTConsoleVariableDataInt(TEXT("r.MaterialEnableNewHLSLGenerator"));
		const bool bEnableControlFlow = AllowMaterialControlFlow();
		const bool bEnableNewHLSLGenerator = CVarMaterialEnableNewHLSLGenerator->GetValueOnAnyThread() != 0;
	
		for( TObjectIterator<UClass> It ; It ; ++It )
		{
			if( Class->IsChildOf(UMaterialExpression::StaticClass()) )
			{
					// Hide node types related to control flow, unless it's enabled
					if (!bEnableControlFlow && Class->HasMetaData("MaterialControlFlow"))
					{
									continue;
					}
					
					if (!bEnableNewHLSLGenerator && Class->HasMetaData("MaterialNewHLSLGenerator"))
					{
									continue;
					}
					
					// Hide node types that are tagged private
					if(Class->HasMetaData(TEXT("Private")))
					{
									continue;
					}
				AllExpressionClasses.Add(MaterialExpression);
			}
		}
}
```