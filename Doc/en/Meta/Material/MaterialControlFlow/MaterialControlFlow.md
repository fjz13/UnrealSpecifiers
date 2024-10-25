# MaterialControlFlow

- **Function Description:** Identifies this UMaterialExpression as a control flow node, currently concealed in the material blueprint's right-click menu.
- **Usage Location:** UCLASS
- **Engine Module:** Material
- **Metadata Type:** bool
- **Restriction Type:** Subclass of UMaterialExpression
- **Commonality:** ★

Identifies this UMaterialExpression as a control flow node, which is currently hidden in the material blueprint's right-click menu.

Usually found in nodes like IfThenElse and ForLoop; however, the current engine implementation is incomplete, rendering this feature disabled.

## Source Code Example:

```cpp
UCLASS(collapsecategories, hidecategories=Object, MinimalAPI)
class UMaterialExpressionIf : public UMaterialExpression
{}

UCLASS(collapsecategories, hidecategories = Object, MinimalAPI, meta=(MaterialControlFlow))
class UMaterialExpressionIfThenElse : public UMaterialExpression
{}
```

## Test Results:

The If node can be located, but calling the IfThenElse node is not possible.

![Untitled](Untitled.png)

## Principle:

During the traversal of all available FMaterialExpression objects, any with MaterialControlFlow are skipped. Currently, under the engine, AllowMaterialControlFlow is always false and remains unimplemented.

```cpp

// r.MaterialEnableControlFlow is removed and the feature is forced disabled as how control flow should be
// implemented in the material editor is still under discussion.
inline bool AllowMaterialControlFlow()
{
	return false;
}

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