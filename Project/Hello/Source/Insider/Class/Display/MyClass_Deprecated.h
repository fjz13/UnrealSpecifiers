// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyClass_Deprecated.generated.h"

/*
(BlueprintType = true, DevelopmentStatus = Experimental, IncludePath = Class/Display/MyClass_Deprecated.h, IsBlueprintBase = true, ModuleRelativePath = Class/Display/MyClass_Deprecated.h)
*/
UCLASS(Blueprintable, Experimental)
class INSIDER_API UMyClass_Experimental :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyProperty;
	UFUNCTION(BlueprintCallable)
		void MyFunc() {}
};

//(BlueprintType = true, DevelopmentStatus = EarlyAccess, IncludePath = Class/Display/MyClass_Deprecated.h, IsBlueprintBase = true, ModuleRelativePath = Class/Display/MyClass_Deprecated.h)
UCLASS(Blueprintable, EarlyAccessPreview)
class INSIDER_API UMyClass_EarlyAccessPreview :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyProperty;
	UFUNCTION(BlueprintCallable)
		void MyFunc() {}
};


/*
* (BlueprintType = true, Deprecated = Hello, IncludePath = Class/Display/MyClass_Deprecated.h, IsBlueprintBase = true, ModuleRelativePath = Class/Display/MyClass_Deprecated.h)
ClassFlags:	CLASS_MatchedSerializers | CLASS_Native | CLASS_NotPlaceable | CLASS_RequiredAPI | CLASS_TokenStreamAssembled | CLASS_Deprecated | CLASS_Intrinsic | CLASS_Constructed

*/
//	

UCLASS(Blueprintable, Deprecated, meta = (Deprecated = "Hello"))
class INSIDER_API UDEPRECATED_MyClass_Deprecated :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyProperty;
	UFUNCTION(BlueprintCallable)
		void MyFunc() {}
};


UCLASS(Blueprintable, Deprecated)
class INSIDER_API ADEPRECATED_MyActor_Deprecated :public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyProperty;
	UFUNCTION(BlueprintCallable)
		void MyFunc() {}
};




UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyClass_Deprecated_Test :public UObject
{
	GENERATED_BODY()
public:

		UE_DEPRECATED(5.2, "This is my msg for MyClass_Deprecated")
		UDEPRECATED_MyClass_Deprecated* MyProperty_Deprecated;

		//(Category = MyClass_Deprecated_Test, DeprecatedProperty = , DeprecationMessage = My Custom deprecation message for MyIntProperty, ModuleRelativePath = Class/Display/MyClass_Deprecated.h)
		UE_DEPRECATED(5.2, "This is my msg for MyIntProperty")
		UPROPERTY(EditAnywhere, BlueprintReadWrite,meta=(DeprecatedProperty, DeprecationMessage = "My Custom deprecation message for MyIntProperty"))
		int MyIntProperty;

		UPROPERTY()
			int MyInt2Property_DEPRECATED;


		UE_DEPRECATED(5.2, "This is my msg for MyNativeFunc")
		void MyNativeFunc(UDEPRECATED_MyClass_Deprecated* obj){}

		//(DeprecatedFunction = , DeprecationMessage = My Custom deprecation message for MyFunc, ModuleRelativePath = Class/Display/MyClass_Deprecated.h)
		UFUNCTION(BlueprintCallable, meta = (DeprecatedFunction, DeprecationMessage="My Custom deprecation message for MyFunc"))
		void MyFunc(){}
};

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyClass_Deprecated_Usage :public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void MyFunc()
	{
		UMyClass_Deprecated_Test* obj=NewObject<UMyClass_Deprecated_Test>();
		UDEPRECATED_MyClass_Deprecated* obj2 = NewObject<UDEPRECATED_MyClass_Deprecated>();
		//obj->MyProperty_Deprecated= obj2;
		//obj->MyProperty_Deprecated->MyFunc(); 

		//obj->MyIntProperty++;
		//obj->MyNativeFunc(obj2);
		obj->MyFunc();
	}
};
