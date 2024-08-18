# Blueprintable

功能描述: 可以在蓝图里被继承，隐含的作用也可当变量类型
引擎模块: Blueprint
元数据类型: bool
Example: UCLASS(Blueprintable)
class INSIDER_API UMyClass_Blueprintable :public UObject
{
GENERATED_BODY()
};
MetaOperation: |=true
Meta: IsBlueprintBase (../../Meta/Meta/IsBlueprintBase.md), BlueprintType (../../Meta/Meta/BlueprintType.md)
Status: Done
Sub-item: NotBlueprintable (NotBlueprintable.md)
常用程度: 5

可以在蓝图里被继承，隐含的作用也可当变量类型。

当设置Blueprintable标记的时候，会隐含的设置上BlueprintType = true的metadata。去除的时候，也会相应的去除掉BlueprintType = true。

示例代码：

```cpp
/*
(BlueprintType = true, IncludePath = Class/MyClass_Blueprintable.h, IsBlueprintBase = true, ModuleRelativePath = Class/MyClass_Blueprintable.h)
*/
UCLASS(Blueprintable)
class INSIDER_API UMyClass_Blueprintable :public UObject
{
	GENERATED_BODY()
};

/*
(IncludePath = Class/MyClass_Blueprintable.h, IsBlueprintBase = false, ModuleRelativePath = Class/MyClass_Blueprintable.h)
*/
UCLASS(NotBlueprintable)
class INSIDER_API UMyClass_NotBlueprintable :public UObject
{
	GENERATED_BODY()
};

/*
(BlueprintType = true, IncludePath = Class/MyClass_Blueprintable.h, IsBlueprintBase = true, ModuleRelativePath = Class/MyClass_Blueprintable.h)
*/
UCLASS(Blueprintable)
class INSIDER_API UMyClass_NotBlueprintable_To_Blueprintable :public UMyClass_NotBlueprintable
{
	GENERATED_BODY()
};

/*
(IncludePath = Class/MyClass_Blueprintable.h, IsBlueprintBase = false, ModuleRelativePath = Class/MyClass_Blueprintable.h)
*/
UCLASS(NotBlueprintable)
class INSIDER_API UMyClass_Blueprintable_To_NotBlueprintable :public UMyClass_Blueprintable
{
	GENERATED_BODY()
};
```

示例效果：

只有带有Blueprintable才可以被选做基类。

![Untitled](Blueprintable/Untitled.png)

不过是否能够当做变量的规则，还是会依赖父类的Blueprint标记。因此以下这3个都是可以当做变量的。

其中UMyClass_Blueprintable_To_NotBlueprintable可以当做变量是因为父类UMyClass_Blueprintable可以当做变量，因此就继承了下来。

![Untitled](Blueprintable/Untitled%201.png)

原理：

可见MD_IsBlueprintBase的判断用来决定是否能创建子类

```cpp
bool FKismetEditorUtilities::CanCreateBlueprintOfClass(const UClass* Class)
{
	bool bCanCreateBlueprint = false;
	
	if (Class)
	{
		bool bAllowDerivedBlueprints = false;
		GConfig->GetBool(TEXT("Kismet"), TEXT("AllowDerivedBlueprints"), /*out*/ bAllowDerivedBlueprints, GEngineIni);

		bCanCreateBlueprint = !Class->HasAnyClassFlags(CLASS_Deprecated)
			&& !Class->HasAnyClassFlags(CLASS_NewerVersionExists)
			&& (!Class->ClassGeneratedBy || (bAllowDerivedBlueprints && !IsClassABlueprintSkeleton(Class)));

		const bool bIsBPGC = (Cast<UBlueprintGeneratedClass>(Class) != nullptr);

		const bool bIsValidClass = Class->GetBoolMetaDataHierarchical(FBlueprintMetadata::MD_IsBlueprintBase)
			|| (Class == UObject::StaticClass())
			|| (Class == USceneComponent::StaticClass() || Class == UActorComponent::StaticClass())
			|| bIsBPGC;  // BPs are always considered inheritable
			
		bCanCreateBlueprint &= bIsValidClass;
	}
	
	return bCanCreateBlueprint;
}
```