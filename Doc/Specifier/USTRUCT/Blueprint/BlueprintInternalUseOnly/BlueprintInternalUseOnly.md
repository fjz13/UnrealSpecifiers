# BlueprintInternalUseOnly

- **功能描述：** 不可定义新BP变量，但可作为别的类的成员变量暴露和变量传递
- **元数据类型：**bool
- **引擎模块：**Blueprint
- **作用机制：**在Meta中加入[BlueprintInternalUseOnly](../../../../Meta/Blueprint/BlueprintInternalUseOnly.md), [BlueprintType](../../../../Meta/Blueprint/BlueprintType.md)
- **常用程度：**★★

指明这个STRUCT会是个BlueprintType，但在蓝图编辑器中又不能声明新变量，但是可以作为别的类的成员变量暴露到蓝图中。

和不写BlueprintType的差别是什么？

不写BlueprintType则完全不能作为别的类的成员变量。BlueprintInternalUseOnly抑制了定义新变量的能力，但是可以作为变量传递。比如在C++中定义变量，然后在蓝图中传递。

如FTableRowBase本身并不能定义新变量，但是其子类（要加上BlueprintType）是可以定义新变量的，正常被使用。

## 示例代码：

```cpp
//(BlueprintInternalUseOnly = true, BlueprintType = true, ModuleRelativePath = Struct/MyStruct_BlueprintInternalUseOnly.h)
USTRUCT(BlueprintInternalUseOnly)
struct INSIDER_API FMyStruct_BlueprintInternalUseOnly
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float Score=0.f;
};

USTRUCT()
struct INSIDER_API FMyStruct_NoBlueprintInternalUseOnly
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float Score=0.f;
};

UCLASS(Blueprintable,BlueprintType)
class INSIDER_API UMyClass_BlueprintInternalUseOnlyTest :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FMyStruct_BlueprintInternalUseOnly MyInternalStruct;

	/*UPROPERTY(BlueprintReadWrite,EditAnywhere)	//no supported by BP
	FMyStruct_NoBlueprintInternalUseOnly MyStruct;*/
};

```

## 示例效果：

NewVar是UMyClass_BlueprintInternalUseOnlyTest 类型的，依然可以访问内部的MyInternalStruct变量。

![Untitled](Untitled.png)

源码里可以找到：

```cpp
USTRUCT(BlueprintInternalUseOnly)
struct FLatentActionInfo
{}

USTRUCT(BlueprintInternalUseOnly)
struct FTableRowBase
{}
```

## 原理：

```cpp
bool UEdGraphSchema_K2::IsAllowableBlueprintVariableType(const UScriptStruct* InStruct, const bool bForInternalUse)
{
	if (const UUserDefinedStruct* UDStruct = Cast<const UUserDefinedStruct>(InStruct))
	{
		if (EUserDefinedStructureStatus::UDSS_UpToDate != UDStruct->Status.GetValue())
		{
			return false;
		}

		// User-defined structs are always allowed as BP variable types.
		return true;
	}

	// struct needs to be marked as BP type
	if (InStruct && InStruct->GetBoolMetaDataHierarchical(FBlueprintMetadata::MD_AllowableBlueprintVariableType))
	{
		// for internal use, all BP types are allowed
		if (bForInternalUse)
		{
			return true;
		}

		// for user-facing use case, only allow structs that don't have the internal-use-only tag
		// struct itself should not be tagged
		if (!InStruct->GetBoolMetaData(FBlueprintMetadata::MD_BlueprintInternalUseOnly))
		{
			// struct's base structs should not be tagged
			if (!InStruct->GetBoolMetaDataHierarchical(FBlueprintMetadata::MD_BlueprintInternalUseOnlyHierarchical))
			{
				return true;
			}
		}
	}

	return false;
}

//Node->IsIntermediateNode()如果为true，则是作为中间节点使用，true会导致bForInternalUse为true
if (!UK2Node_MakeStruct::CanBeMade(Node->StructType, Node->IsIntermediateNode()))
```