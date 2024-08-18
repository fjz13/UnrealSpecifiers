# RestrictedToClasses

功能描述: 限制蓝图函数库下的函数只能在RestrictedToClasses指定的类蓝图中右键创建出来
使用位置: UCLASS
Feature: Blueprint
引擎模块: Blueprint
元数据类型: strings="a，b，c"
限制类型: BlueprintFunctionLibrary
Example: RestrictedToClasses="Class1, Class2, ..”
Status: Done
常用程度: 3

在蓝图函数库上使用，指定该函数库中的函数只能用在RestrictedToClasses指定的类的蓝图中，不能在别的蓝图类中被右键出来。

测试代码：

```cpp
UCLASS(Blueprintable)
class INSIDER_API UMyClass_RestrictedToClasses :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float MyFloat;
};

UCLASS(meta=(RestrictedToClasses="MyClass_RestrictedToClasses"))
class INSIDER_API UMyClass_RestrictedToClassesLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	static float GetMyClassRestrictedFloat(UMyClass_RestrictedToClasses* myObject) {return myObject->MyFloat;}
};
```

在UMyClass_RestrictedToClasses 的子类蓝图中测试效果：

![Untitled](RestrictedToClasses/Untitled.png)

在别的地方，比如关卡蓝图中测试效果：

因此右键创建不出来，但是直接粘贴节点其实还是可以调用的。

![Untitled](RestrictedToClasses/Untitled%201.png)

源码中的例子：

指定UBTFunctionLibrary中的节点，只能在BTNode中使用，否则没有意义。

```cpp
UCLASS(meta=(RestrictedToClasses="BTNode"), MinimalAPI)
class UBTFunctionLibrary : public UBlueprintFunctionLibrary
{
UFUNCTION(BlueprintPure, Category="AI|BehaviorTree", Meta=(HidePin="NodeOwner", DefaultToSelf="NodeOwner"))
	static AIMODULE_API UBlackboardComponent* GetOwnersBlackboard(UBTNode* NodeOwner);
//....
}
```

原理：

```cpp
static bool BlueprintActionFilterImpl::IsRestrictedClassMember(FBlueprintActionFilter const& Filter, FBlueprintActionInfo& BlueprintAction)
{
	bool bIsFilteredOut = false;
	FBlueprintActionContext const& FilterContext = Filter.Context;
	
	if (UClass const* ActionClass = BlueprintAction.GetOwnerClass())
	{
		if (ActionClass->HasMetaData(FBlueprintMetadata::MD_RestrictedToClasses))
		{
			FString const& ClassRestrictions = ActionClass->GetMetaData(FBlueprintMetadata::MD_RestrictedToClasses);
			
			// Parse the the metadata into an array that is delimited by ',' and trim whitespace
			TArray<FString> ParsedClassRestrictions;
			ClassRestrictions.ParseIntoArray(ParsedClassRestrictions, TEXT(","));
			for (FString& ValidClassName : ParsedClassRestrictions)
			{
				ValidClassName = ValidClassName.TrimStartAndEnd();
			}

			for (UBlueprint const* TargetContext : FilterContext.Blueprints)
			{
				UClass* TargetClass = TargetContext->GeneratedClass;
				if(!TargetClass)
				{
					// Skip possible null classes (e.g. macros, etc)
					continue;
				}

				bool bIsClassListed = false;
				
				UClass const* QueryClass = TargetClass;
				// walk the class inheritance chain to see if this class is one
				// of the allowed
				while (!bIsClassListed && (QueryClass != nullptr))
				{
					FString const ClassName = QueryClass->GetName();
					// If this class is on the list of valid classes
					for (const FString& ValidClassName : ParsedClassRestrictions)
					{
						bIsClassListed = (ClassName == ValidClassName);
						if (bIsClassListed)
						{
							break;
						}
					}
					
					QueryClass = QueryClass->GetSuperClass();
				}
				
				// if the blueprint class wasn't listed as one of the few
				// classes that this can be accessed from, then filter it out
				if (!bIsClassListed)
				{
					bIsFilteredOut = true;
					break;
				}
			}
		}
	}
	
	return bIsFilteredOut;
}
```