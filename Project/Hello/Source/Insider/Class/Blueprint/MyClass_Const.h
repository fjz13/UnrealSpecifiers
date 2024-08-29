// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyClass_Const.generated.h"

/*
[MyClass_Const	Class->Struct->Field->Object	/Script/Insider.MyClass_Const]
(BlueprintType = true, IncludePath = Class/MyClass_Const.h, IsBlueprintBase = true, ModuleRelativePath = Class/MyClass_Const.h)
	ObjectFlags:	RF_Public | RF_Standalone | RF_Transient
	Outer:	Package /Script/Insider
	ClassHierarchy:	MyClass_Const:Object
	ClassFlags:	CLASS_MatchedSerializers | CLASS_Native | CLASS_Const | CLASS_RequiredAPI | CLASS_TokenStreamAssembled | CLASS_Intrinsic | CLASS_Constructed
	Size:	56
	{
		(Category = MyClass_Const, ModuleRelativePath = Class/MyClass_Const.h)
			48-[4] int32 MyProperty;
			PropertyFlags:	CPF_Edit | CPF_BlueprintVisible | CPF_BlueprintReadOnly | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
			ObjectFlags:	RF_Public | RF_MarkAsNative | RF_Transient
			Outer:	Class /Script/Insider.MyClass_Const
			Path:	IntProperty /Script/Insider.MyClass_Const:MyProperty
		[MyFunc	Function->Struct->Field->Object	/Script/Insider.MyClass_Const:MyFunc]
		(ModuleRelativePath = Class/MyClass_Const.h)
			ObjectFlags:	RF_Public | RF_Transient
			Outer:	Class /Script/Insider.MyClass_Const
			public void MyFunc()const final;
		[ExecuteUbergraph	Function->Struct->Field->Object	/Script/CoreUObject.Object:ExecuteUbergraph]
		(BlueprintInternalUseOnly = true, ModuleRelativePath = Public/UObject/NoExportTypes.h)
			ObjectFlags:	RF_Public | RF_Transient
			Outer:	Class /Script/CoreUObject.Object
			public void ExecuteUbergraph(int32 EntryPoint);
	};
*/
UCLASS(Blueprintable,Const)
class INSIDER_API UMyClass_Const :public UObject
{
	GENERATED_BODY()
	public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 MyProperty=123;
	UFUNCTION(BlueprintCallable)
    void MyFunc(){++MyProperty;}
};

