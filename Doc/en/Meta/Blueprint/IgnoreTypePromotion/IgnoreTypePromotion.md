# IgnoreTypePromotion

- **Function Description:** Marks this function as excluded from the type promotion function library
- **Usage Location:** UFUNCTION
- **Engine Module:** Blueprint
- **Metadata Type:** bool
- **Restriction Type:** BlueprintPure functions within UBlueprintFunctionLibrary, formatted as OP_XXX
- **Commonality:** ★★

Mark this function as excluded from the type promotion function library.

## There are three key points to consider:

First, what type of function is this? Or, what is the nature of a type promotion function? According to the IsPromotableFunction source code definition, the function must be defined within UBlueprintFunctionLibrary, must be of type BlueprintPure, and must be named in the format of an operator "OP_XXX," where the OP name is visible within the OperatorNames namespace. Examples of such functions can be found in abundance within KismetMathLibrary.

Second, what is a type promotion function library? The source code contains a class named FTypePromotion, which includes an OperatorTable that records a map from operator names to lists of functions, such as multiple Add_Vector, Add_Float, etc., that support the Add (+) operation. When right-clicking on a + or Add node in a blueprint, a generic + node is initially presented. Then, upon connecting to a specific variable type, the blueprint system will search the FTypePromotion::OperatorTable for the most compatible function to call, or perform type promotion automatically within the system. For instance, the + in the figure below ultimately calls UKismetMathLibrary::Add_VectorFloat. This generic operator call facilitates a more convenient and unified approach to basic type operations in blueprint node creation, as well as direct Add Pin and Pin conversion to compatible types.

![Untitled](Untitled.png)

Third, why do some functions opt out of being included in FTypePromotion? Upon searching the source code, it is found that only FDateTime in KismetMathLibrary is marked with the IgnoreTypePromotion attribute. Although FDateTime defines a series of operator functions, such as Add, Subtract, and various comparison operators, FDateTime differs from other basic types in that FDateTime + float or FDateTime + vector hold no meaningful operation. FDateTime only allows operations with +FDateTime or +FTimeSpan. Therefore, for types like FDateTime that do not wish to participate in type promotion relationships with other types, and prefer to operate within their own limited scope, the IgnoreTypePromotion attribute can be added to opt out of the FTypePromotion system.

## Test Code:

Suppose we have a structure called FGameProp that defines combat attributes (HP, Attack, Defense) within the game. In the game, operations such as equipping and adding buffs typically calculate final attributes. For this FGameProp structure, we can define a series of basic operation functions and add the IgnoreTypePromotion attribute, as it is certainly not intended to participate in type promotion with other basic types (float, vector, etc.).

For comparison, the code also defines an identical structure, FGameProp2, with the same operation functions, the only difference being the absence of IgnoreTypePromotion. The purpose is to observe the differences in the resulting blueprint nodes.

```cpp
USTRUCT(BlueprintType)
struct FGameProp
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double HP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double Attack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double Defense;
};

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyFunction_IgnoreTypePromotion :public UBlueprintFunctionLibrary
{
public:
	GENERATED_BODY()
public:
	/** Makes a GameProp struct */
	UFUNCTION(BlueprintPure, Category = "Math|GameProp", meta = (IgnoreTypePromotion, NativeMakeFunc))
	static FGameProp MakeGameProp(double HP, double Attack, double Defense) { return FGameProp(); }

	/** Breaks a GameProp into its components */
	UFUNCTION(BlueprintPure, Category = "Math|GameProp", meta = (IgnoreTypePromotion, NativeBreakFunc))
	static void BreakGameProp(FGameProp InGameProp, double& HP, double& Attack, double& Defense) {}

	/** Addition (A + B) */
	UFUNCTION(BlueprintPure, meta = (IgnoreTypePromotion, DisplayName = "GameProp + GameProp", CompactNodeTitle = "+", Keywords = "+ add plus"), Category = "Math|GameProp")
	static FGameProp Add_GameProp(FGameProp A, FGameProp B);

	/** Subtraction (A - B) */
	UFUNCTION(BlueprintPure, meta = (IgnoreTypePromotion, DisplayName = "GameProp - GameProp", CompactNodeTitle = "-", Keywords = "- subtract minus"), Category = "Math|GameProp")
	static FGameProp Subtract_GameProp(FGameProp A, FGameProp B) { return FGameProp(); }

	/** Returns true if the values are equal (A == B) */
	UFUNCTION(BlueprintPure, meta = (IgnoreTypePromotion, DisplayName = "Equal (GameProp)", CompactNodeTitle = "==", Keywords = "== equal"), Category = "Math|GameProp")
	static bool EqualEqual_GameProp(FGameProp A, FGameProp B) { return true; }

	/** Returns true if the values are not equal (A != B) */
	UFUNCTION(BlueprintPure, meta = (IgnoreTypePromotion, DisplayName = "Not Equal (GameProp)", CompactNodeTitle = "!=", Keywords = "!= not equal"), Category = "Math|GameProp")
	static bool NotEqual_GameProp(FGameProp A, FGameProp B) { return true; }

	/** Returns true if A is greater than B (A > B) */
	UFUNCTION(BlueprintPure, meta = (IgnoreTypePromotion, DisplayName = "GameProp > GameProp", CompactNodeTitle = ">", Keywords = "> greater"), Category = "Math|GameProp")
	static bool Greater_GameProp(FGameProp A, FGameProp B) { return true; }

	/** Returns true if A is greater than or equal to B (A >= B) */
	UFUNCTION(BlueprintPure, meta = (IgnoreTypePromotion, DisplayName = "GameProp >= GameProp", CompactNodeTitle = ">=", Keywords = ">= greater"), Category = "Math|GameProp")
	static bool GreaterEqual_GameProp(FGameProp A, FGameProp B) { return true; }

	/** Returns true if A is less than B (A < B) */
	UFUNCTION(BlueprintPure, meta = (IgnoreTypePromotion, DisplayName = "GameProp < GameProp", CompactNodeTitle = "<", Keywords = "< less"), Category = "Math|GameProp")
	static bool Less_GameProp(FGameProp A, FGameProp B) { return true; }

	/** Returns true if A is less than or equal to B (A <= B) */
	UFUNCTION(BlueprintPure, meta = (IgnoreTypePromotion, DisplayName = "GameProp <= GameProp", CompactNodeTitle = "<=", Keywords = "<= less"), Category = "Math|GameProp")
	static bool LessEqual_GameProp(FGameProp A, FGameProp B) { return true; }
	};


```

## Blueprint Effect:

With IgnoreTypePromotion added, the FGameProp Add operation results in the direct use of the original Add_GameProp node. Without IgnoreTypePromotion, FGameProp2's Add operation generates a generic + node, which can be further used for Add Pin, and even attempts to find conversions to other types on the Pin (though no conversion is found here because we have not defined operation functions for FGameProp2 with other types).

![Untitled](Untitled%201.png)

Another observation is that right-clicking on an empty generic Add node reveals an option to convert to FGameProp2 (but not FGameProp), indicating that FGameProp2 is part of the TypePromotion system. However, we do not want FGameProp2 to appear here, as the combat attributes in this gameplay have their own set of operation rules and should not be mixed with basic type mathematical operations.

![Untitled](Untitled%202.png)

## Principle:

In the editor settings, there is an option called EnableTypePromotion. When activated, FTypePromotion begins to collect all functions defined within the engine and determines whether they qualify as type promotion functions.

![Untitled](Untitled%203.png)

If a function name includes an operator prefix (as defined in OperatorNames), such as Add_XXX, the operator is extracted. Functions that are registered and added to the FTypePromotion::OperatorTable mapping are those that will be found when right-clicking on operators (like +) in blueprints.

```cpp
namespace OperatorNames
{
	static const FName NoOp			= TEXT("NO_OP");

	static const FName Add			= TEXT("Add");
	static const FName Multiply		= TEXT("Multiply");
	static const FName Subtract		= TEXT("Subtract");
	static const FName Divide		= TEXT("Divide");

	static const FName Greater		= TEXT("Greater");
	static const FName GreaterEq	= TEXT("GreaterEqual");
	static const FName Less			= TEXT("Less");
	static const FName LessEq		= TEXT("LessEqual");
	static const FName NotEq		= TEXT("NotEqual");
	static const FName Equal		= TEXT("EqualEqual");
}

bool const bIsPromotableFunction = TypePromoDebug::IsTypePromoEnabled() && FTypePromotion::IsFunctionPromotionReady(Function);
if (bIsPromotableFunction)
{
	NodeClass = UK2Node_PromotableOperator::StaticClass();
}

bool FTypePromotion::IsPromotableFunction(const UFunction* Function)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(FTypePromotion::IsPromotableFunction);

	// Ensure that we don't have an invalid OpName as well for extra safety when this function
	// is called outside of this class, not during the OpTable creation process
	FName OpName = GetOpNameFromFunction(Function);
	return Function &&
		Function->HasAnyFunctionFlags(FUNC_BlueprintPure) &&
		Function->GetReturnProperty() &&
		OpName != OperatorNames::NoOp &&
		!IsPinTypeDeniedForTypePromotion(Function) &&
		// Users can deny specific functions from being considered for type promotion
		!Function->HasMetaData(FBlueprintMetadata::MD_IgnoreTypePromotion);
}
```

The contents of the OperatorTable collected by FTypePromotion:

![Untitled](Untitled%204.png)

If a function is identified as IsPromotableFunction, it will use UK2Node_PromotableOperator as the blueprint node (instead of the default UK2Node_CallFunction) when called. UK2Node_PromotableOperator is a typical binary operator used for wildcard generics. As shown in the figure below, Add (+) can trigger a type conversion menu from Wildcard to a specific type because the structure has defined Add_XXX functions and does not have IgnoreTypePromotion, thus being included in the TypePromotion mapping.

The Pin Conversion menu mentioned above is collected in UK2Node_PromotableOperator::CreateConversionMenu.