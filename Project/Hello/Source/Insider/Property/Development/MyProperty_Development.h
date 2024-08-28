// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProperty_Development.generated.h"

//(BlueprintType = true, Comment = //This is a comment on class, IncludePath = Property/Development/MyProperty_Development.h, ModuleRelativePath = Property/Development/MyProperty_Development.h, ToolTip = This is a comment on class)

//This is a comment on class
UCLASS(BlueprintType)
class INSIDER_API UMyProperty_Development :public UObject
{
	GENERATED_BODY()
public:
	//(Comment = //This is a comment on function, ModuleRelativePath = Property/Development/MyProperty_Development.h, ToolTip = This is a comment on function)
	
	//This is a comment on function
	UFUNCTION(BlueprintCallable)
	int32 MyFunc(FString str){return 0;}

	//	(Category = MyProperty_Development, Comment = //This is a comment on property, ModuleRelativePath = Property/Development/MyProperty_Development.h, ToolTip = This is a comment on property)
	 
	//This is a comment on property
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MyProperty = 123;

	//(Category = MyProperty_Development, Comment = This is my other property., ModuleRelativePath = Property/Development/MyProperty_Development.h)

	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta=(Comment="This is my other property."))
	int32 MyProperty_WithComment = 123;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta=(Deprecated="5.1"))
	int32 MyInt_OnlyWithDeprecated = 123;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta=(DeprecatedProperty, DeprecationMessage="This is deprecated",Deprecated="5.1"))
	int32 MyInt_WithDeprecatedProperty = 123;

};

