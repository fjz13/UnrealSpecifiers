// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor_ComponentWrapperClass.generated.h"

/*
(BlueprintType = true, HideCategories = MyGroup3, IgnoreCategoryKeywordsInSubclasses = true, IncludePath = Class/Display/MyActor_ComponentWrapperClass.h, IsBlueprintBase = true, ModuleRelativePath = Class/Display/MyActor_ComponentWrapperClass.h)
*/
UCLASS(Blueprintable, BlueprintType, ComponentWrapperClass, hideCategories = MyGroup3)	//依然会显示出Property_Group3
class AMyActor_ComponentWrapperClass : public AActor
{
	GENERATED_UCLASS_BODY()
public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		class UPointLightComponent* PointLightComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyGroup3)
		int Property_Group3;
};

UCLASS(Blueprintable, BlueprintType, hideCategories = MyGroup3)
class AMyActor_NoComponentWrapperClass : public AActor //Property_Group3会被隐藏
{
	GENERATED_UCLASS_BODY()
public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		class UPointLightComponent* PointLightComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyGroup3)
		int Property_Group3;
};


//UCLASS(ClassGroup=(Utility, Common), BlueprintType, hideCategories=(Trigger, PhysicsVolume), meta=(BlueprintSpawnableComponent, IgnoreCategoryKeywordsInSubclasses, ShortTooltip="A Scene Component is a component that has a scene transform and can be attached to other scene components."))
//class ENGINE_API USceneComponent : public UActorComponent


/*
(BlueprintSpawnableComponent = , BlueprintType = true, HideCategories = MyGroup3 PhysicsVolume, IncludePath = Class/Display/MyActor_ComponentWrapperClass.h, IsBlueprintBase = true, ModuleRelativePath = Class/Display/MyActor_ComponentWrapperClass.h)
*/
UCLASS(Blueprintable, BlueprintType, hideCategories = MyGroup3,showCategories="Trigger", meta = (BlueprintSpawnableComponent))
class INSIDER_API USceneComponent_MyChild : public USceneComponent //用testprops会隐藏MyGroup3,因为ComponentWrapperClass只在双击蓝图时有效
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyGroup3)
		int Property_Group3;
};