# Obsolete

- **Function Description:** Indicates that this FRigUnit is deprecated and will not be displayed in the blueprint's right-click menu.
- **Usage Location:** USTRUCT
- **Engine Module:** RigVMStruct
- **Metadata Type:** bool
- **Type Constraint:** Applicable to FRigUnit type
- **Commonality:** ★★

Indicates that this FRigUnit is deprecated and will not be shown in the blueprint's right-click menu.

However, if it has already been used in a blueprint, it can continue to be used.

Attention should be given to implementing GetUpgradeInfo() accordingly, otherwise an error will occur.

## Test Code:

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

## Test Outcomes:

![Untitled](Untitled.png)

## Principle:

Deprecated nodes are skipped when constructing menu items.

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