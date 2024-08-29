// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyClass_CollapseCategories.generated.h"


/*
ClassFlags: CLASS_MatchedSerializers | CLASS_Native | CLASS_CollapseCategories | CLASS_RequiredAPI | CLASS_TokenStreamAssembled | CLASS_Intrinsic | CLASS_Constructed
*/
UCLASS(Blueprintable, CollapseCategories)
class INSIDER_API UMyClass_CollapseCategories :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Property_NotInGroup;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyGroup1")
		int Property_Group1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyGroup2|MyGroup22")
		int Property_Group22;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyGroup3|MyGroup33|MyGroup333")
		int Property_Group333;
};

/*
ClassFlags: CLASS_MatchedSerializers | CLASS_Native | CLASS_RequiredAPI | CLASS_TokenStreamAssembled | CLASS_Intrinsic | CLASS_Constructed 
*/
UCLASS(Blueprintable, dontCollapseCategories)
class INSIDER_API UMyClass_DontCollapseCategories :public UMyClass_CollapseCategories
{
	GENERATED_BODY()
public:
};




/*
(AutoExpandCategories = MyGroup2|MyGroup22 MyGroup4|MyGroup44 MyGroup4|MyGroup44|MyGroup444, BlueprintType = true, IncludePath = Class/Display/MyClass_CollapseCategories.h, IsBlueprintBase = true, ModuleRelativePath = Class/Display/MyClass_CollapseCategories.h)
*/
UCLASS(Blueprintable, AutoExpandCategories = ("MyGroup2|MyGroup22", "MyGroup4|MyGroup44","MyGroup4|MyGroup44|MyGroup444"))
class INSIDER_API UMyClass_AutoExpandCategories :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Property_NotInGroup;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyGroup1")
		int Property_Group1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyGroup2")
		int Property_Group2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyGroup2|MyGroup22")
		int Property_Group22;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyGroup3|MyGroup33")
		int Property_Group33;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyGroup4|MyGroup44|MyGroup444")
		int Property_Group444;
};

/*
(AutoCollapseCategories = MyGroup2|MyGroup22, AutoExpandCategories = MyGroup4|MyGroup44|MyGroup444 MyGroup4|MyGroup44, BlueprintType = true, IncludePath = Class/Display/MyClass_CollapseCategories.h, IsBlueprintBase = true, ModuleRelativePath = Class/Display/MyClass_CollapseCategories.h)
*/

UCLASS(Blueprintable, AutoCollapseCategories = ("MyGroup2|MyGroup22"))
class INSIDER_API UMyClass_AutoCollapseCategories :public UMyClass_AutoExpandCategories
{
	GENERATED_BODY()
public:
};

UCLASS(Blueprintable, DontAutoCollapseCategories = "MyGroup2|MyGroup22")
class INSIDER_API UMyClass_DontAutoCollapseCategories :public UMyClass_AutoCollapseCategories
{
	GENERATED_BODY()
public:
};



