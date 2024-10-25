# Private

- **Function Description:** Indicates that this UMaterialExpression is a private node, currently hidden in the right-click menu of the material blueprint.
- **Usage Location:** UCLASS
- **Engine Module:** Material
- **Metadata Type:** bool
- **Restriction Type:** Subclass of UMaterialExpression
- **Commonly Used:** ★

Identifies this UMaterialExpression as a private node, currently concealed in the right-click menu of the material blueprint.

Used within the MaterialX module, currently temporarily hiding all the Expressions inside.

## Source Code Example:

```cpp
UCLASS()
class UMyMaterialExpression_NotPrivate : public UMaterialExpression
{}；

UCLASS(meta=(Private))
class UMyMaterialExpression_Private : public UMaterialExpression
{}；
```

## Test Results:

Only UMyMaterialExpression_NotPrivate can be invoked within the material blueprint.

![Untitled](Untitled.png)

## Principle:

When iterating through all available FMaterialExpressions, any that are marked as Private will be omitted.

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