// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enum/MyEnum.h"
#include "Struct/MyVector.h"
#include "Class/MyItem.h"
#include "MyFunctionParameterActor.generated.h"

UCLASS(Blueprintable)
class LEARN_API AMyFunctionParameterActor :public AActor
{
	GENERATED_BODY()
public:
	AMyFunctionParameterActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	UFUNCTION(BlueprintCallable)
		void Func_Input(int32 val);

	UFUNCTION(BlueprintCallable)
		void Func_Input_Const(const int32& val);

	UFUNCTION(BlueprintCallable)
		void Func_Output(int32& val);

	//Inappropriate '*' on variable of type 'int32', cannot have an exposed pointer to this type.
	//UFUNCTION(BlueprintCallable)
	//	void Func_InputPointer(int32* val);

	UFUNCTION(BlueprintCallable)
		int32 Func_Return();

	UFUNCTION(BlueprintPure)
		int32 Func_Pure();

public:
	UFUNCTION(BlueprintCallable)
		void Func_InputRef(UPARAM(ref) int32& val);

	UFUNCTION(BlueprintCallable)
		void Func_InputOtherName(UPARAM(DisplayName = OtherName) int32 val);

public://enum
	UFUNCTION(BlueprintCallable)
		MyEnum Func_Enum_Input(MyEnum val);

	UFUNCTION(BlueprintCallable)
		void Func_Enum_Output(MyEnum& val);

	UFUNCTION(BlueprintCallable)
		void Func_Enum_Ref(UPARAM(ref) MyEnum& val);
public://struct
	UFUNCTION(BlueprintCallable)
	FMyVector Func_Struct_Input(FMyVector val);

	UFUNCTION(BlueprintCallable)
	void Func_Struct_Output(FMyVector& val);

	UFUNCTION(BlueprintCallable)
	void Func_Struct_Ref(UPARAM(ref) FMyVector& val);

public://string
	UFUNCTION(BlueprintCallable)
		void Func_Name_Input(FName name);

	UFUNCTION(BlueprintCallable)
		void Func_Name_Output(FName& name);

	UFUNCTION(BlueprintCallable)
		void Func_Name_Ref(UPARAM(ref) FName& name);

	UFUNCTION(BlueprintCallable)
		void Func_String_Input(FString str);

	UFUNCTION(BlueprintCallable)
		void Func_String_Input_Const(const FString& str);

	UFUNCTION(BlueprintCallable)
		void Func_String_Output(FString& str);

	UFUNCTION(BlueprintCallable)
		void Func_String_Ref(UPARAM(ref) FString& str);

	UFUNCTION(BlueprintCallable)
		void Func_Text_Input(FText text);

	UFUNCTION(BlueprintCallable)
		void Func_Text_Input_Const(const FText& text);

	UFUNCTION(BlueprintCallable)
		void Func_Text_Output(FText& text);

	UFUNCTION(BlueprintCallable)
		void Func_Text_Ref(UPARAM(ref) FText& text);
public://array
	UFUNCTION(BlueprintCallable)
		void Func_Array_Input(TArray<int32> items);

	UFUNCTION(BlueprintCallable)
		void Func_Array_Input_Const(const TArray<int32>& items);

	UFUNCTION(BlueprintCallable)
		void Func_Array_Output(TArray<int32>& items);

	UFUNCTION(BlueprintCallable)
		void Func_Array_Ref(UPARAM(ref) TArray<int32>& items);

	UFUNCTION(BlueprintCallable)
		TArray<int32> Func_Array_Return();
public://class
	UFUNCTION(BlueprintCallable)
		void Func_Class_Input(UMyItem* obj);

		UFUNCTION(BlueprintCallable)
		void Func_Class_Input_Ref(UPARAM(ref) UMyItem* obj){}

	UFUNCTION(BlueprintCallable)
		void Func_Class_Input_ConstPtr(const UMyItem* obj);

	//Error: Missing '*' in Expected a pointer type
	//UFUNCTION(BlueprintCallable)
	//	void Func_Class_Input_ConstRef(const UMyItem& obj);

	UFUNCTION(BlueprintCallable)
		UMyItem* Func_Class_Output();
};
